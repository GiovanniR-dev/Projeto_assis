#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PALAVRA 15
#define MAX_CAMINHO 100

typedef enum {
    PA = 1,
    PG = 2,
    FIBONACCI = 3,
    PRIMOS = 4
} TipoSequencia;

/* Prototipos */
int validarPalavra(const char *palavra);
void removerEnter(char *texto);
void gerarSequencia(TipoSequencia tipo, int n, int sequencia[], int primeiro, int razao);
int ehPrimo(int numero);
void criptografar(const char *palavra, char *resultado, int shift,
                  const int sequencia[], int tamanho);
void salvarResultado(const char *palavra, const char *resultado, int shift,
                     TipoSequencia tipo, const int sequencia[], int tamanho);
void registrarLog(const char *palavra, const char *resultado, int shift,
                  TipoSequencia tipo, const int sequencia[], int tamanho);
const char *nomeSequencia(TipoSequencia tipo);
void exibirSequencia(const int sequencia[], int tamanho);
void exibirMenu(void);

int main(void) {
    char palavra[MAX_PALAVRA + 1];
    char resultado[MAX_PALAVRA + 1];
    int shift;
    int opcao;
    int primeiro = 1;
    int razao = 1;
    int sequencia[MAX_PALAVRA];
    TipoSequencia tipo;

    printf("===============================================\n");
    printf("   SISTEMA DE CRIPTOGRAFIA MATEMATICA EM C\n");
    printf("===============================================\n");

    printf("\nDigite a palavra secreta (ate %d letras, sem acentos): ", MAX_PALAVRA);
    fgets(palavra, sizeof(palavra), stdin);
    removerEnter(palavra);

    if (!validarPalavra(palavra)) {
        printf("\nErro: use somente letras de A-Z ou a-z e no maximo %d caracteres.\n",
               MAX_PALAVRA);
        return 1;
    }

    printf("Digite o valor do SHIFT (pode ser positivo ou negativo): ");
    if (scanf("%d", &shift) != 1) {
        printf("Erro: SHIFT invalido.\n");
        return 1;
    }

    exibirMenu();

    if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > 4) {
        printf("Erro: opcao de sequencia invalida.\n");
        return 1;
    }

    tipo = (TipoSequencia)opcao;

    /*
       Parametros:
       PA: primeiro termo e razao.
       PG: primeiro termo e razao.
       Fibonacci: os parametros sao ignorados.
       Primos: os parametros sao ignorados.
    */
    if (tipo == PA || tipo == PG) {
        printf("Digite o primeiro termo da sequencia: ");
        if (scanf("%d", &primeiro) != 1) {
            printf("Erro: primeiro termo invalido.\n");
            return 1;
        }

        printf("Digite a razao da sequencia: ");
        if (scanf("%d", &razao) != 1) {
            printf("Erro: razao invalida.\n");
            return 1;
        }

        if (tipo == PG && razao == 0) {
            printf("Erro: na PG, a razao nao pode ser zero.\n");
            return 1;
        }
    }

    gerarSequencia(tipo, (int)strlen(palavra), sequencia, primeiro, razao);

    criptografar(palavra, resultado, shift, sequencia, (int)strlen(palavra));

    printf("\n===============================================\n");
    printf("RESULTADO DA CRIPTOGRAFIA\n");
    printf("===============================================\n");
    printf("Palavra original: %s\n", palavra);
    printf("SHIFT fixo: %d\n", shift);
    printf("Tipo de sequencia: %s\n", nomeSequencia(tipo));
    printf("Sequencia aplicada: ");
    exibirSequencia(sequencia, (int)strlen(palavra));
    printf("Palavra criptografada: %s\n", resultado);

    salvarResultado(palavra, resultado, shift, tipo, sequencia,
                    (int)strlen(palavra));
    registrarLog(palavra, resultado, shift, tipo, sequencia,
                 (int)strlen(palavra));

    printf("\nArquivos gerados:\n");
    printf("- resultado_criptografia.txt\n");
    printf("- log_criptografia.txt\n");

    return 0;
}

void removerEnter(char *texto) {
    size_t tamanho = strlen(texto);

    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}

int validarPalavra(const char *palavra) {
    int tamanho = (int)strlen(palavra);

    if (tamanho == 0 || tamanho > MAX_PALAVRA) {
        return 0;
    }

    for (int i = 0; i < tamanho; i++) {
        if (!isalpha((unsigned char)palavra[i]) ||
            !((palavra[i] >= 'A' && palavra[i] <= 'Z') ||
              (palavra[i] >= 'a' && palavra[i] <= 'z'))) {
            return 0;
        }
    }

    return 1;
}

int ehPrimo(int numero) {
    if (numero < 2) {
        return 0;
    }

    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            return 0;
        }
    }

    return 1;
}

void gerarSequencia(TipoSequencia tipo, int n, int sequencia[],
                    int primeiro, int razao) {
    if (tipo == PA) {
        for (int i = 0; i < n; i++) {
            sequencia[i] = primeiro + i * razao;
        }
    }
    else if (tipo == PG) {
        /*
           Para evitar problemas de overflow desnecessario, a sequencia
           e calculada usando long long e reduzida modulo 26.
           O deslocamento de uma letra depende apenas do valor modulo 26.
        */
        long long termo = primeiro;

        for (int i = 0; i < n; i++) {
            sequencia[i] = (int)(termo % 26);
            if (sequencia[i] < 0) {
                sequencia[i] += 26;
            }
            termo *= razao;
        }
    }
    else if (tipo == FIBONACCI) {
        int a = 1;
        int b = 1;

        for (int i = 0; i < n; i++) {
            if (i == 0 || i == 1) {
                sequencia[i] = 1;
            } else {
                int proximo = a + b;
                a = b;
                b = proximo;
                sequencia[i] = proximo;
            }
        }
    }
    else if (tipo == PRIMOS) {
        int numero = 2;
        int encontrados = 0;

        while (encontrados < n) {
            if (ehPrimo(numero)) {
                sequencia[encontrados] = numero;
                encontrados++;
            }
            numero++;
        }
    }
}

void criptografar(const char *palavra, char *resultado, int shift,
                  const int sequencia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        int deslocamento;
        int valor;

        /*
           Camada 1: Cifra de Cesar -> SHIFT fixo.
           Camada 2: sequencia matematica -> deslocamento dinamico.
           Deslocamento total = SHIFT + sequencia[i].
        */
        deslocamento = shift + sequencia[i];

        if (palavra[i] >= 'a' && palavra[i] <= 'z') {
            valor = palavra[i] - 'a';
            valor = (valor + deslocamento) % 26;

            if (valor < 0) {
                valor += 26;
            }

            resultado[i] = (char)('a' + valor);
        }
        else {
            valor = palavra[i] - 'A';
            valor = (valor + deslocamento) % 26;

            if (valor < 0) {
                valor += 26;
            }

            resultado[i] = (char)('A' + valor);
        }
    }

    resultado[tamanho] = '\0';
}

const char *nomeSequencia(TipoSequencia tipo) {
    switch (tipo) {
        case PA:
            return "Progressao Aritmetica (PA)";
        case PG:
            return "Progressao Geometrica (PG)";
        case FIBONACCI:
            return "Fibonacci";
        case PRIMOS:
            return "Numeros Primos";
        default:
            return "Desconhecida";
    }
}

void exibirSequencia(const int sequencia[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d", sequencia[i]);

        if (i < tamanho - 1) {
            printf(", ");
        }
    }

    printf("\n");
}

void exibirMenu(void) {
    printf("\nEscolha a sequencia matematica:\n");
    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Fibonacci\n");
    printf("4 - Numeros Primos\n");
    printf("Opcao: ");
}

void salvarResultado(const char *palavra, const char *resultado, int shift,
                     TipoSequencia tipo, const int sequencia[], int tamanho) {
    FILE *arquivo = fopen("resultado_criptografia.txt", "w");

    if (arquivo == NULL) {
        printf("Aviso: nao foi possivel criar o arquivo de resultado.\n");
        return;
    }

    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "RESULTADO DA CRIPTOGRAFIA\n");
    fprintf(arquivo, "===============================================\n");
    fprintf(arquivo, "Palavra original: %s\n", palavra);
    fprintf(arquivo, "Palavra codificada: %s\n", resultado);
    fprintf(arquivo, "SHIFT: %d\n", shift);
    fprintf(arquivo, "Tipo: %d - %s\n", tipo, nomeSequencia(tipo));
    fprintf(arquivo, "Letras: %d\n", tamanho);
    fprintf(arquivo, "Sequencia: ");

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d", sequencia[i]);

        if (i < tamanho - 1) {
            fprintf(arquivo, ", ");
        }
    }

    fprintf(arquivo, "\n");
    fprintf(arquivo, "Formula do deslocamento: SHIFT + sequencia[i]\n");

    fclose(arquivo);
}

void registrarLog(const char *palavra, const char *resultado, int shift,
                  TipoSequencia tipo, const int sequencia[], int tamanho) {
    FILE *arquivo = fopen("log_criptografia.txt", "a");
    time_t agora;
    struct tm *tempoAtual;

    if (arquivo == NULL) {
        printf("Aviso: nao foi possivel criar o arquivo de log.\n");
        return;
    }

    agora = time(NULL);
    tempoAtual = localtime(&agora);

    fprintf(arquivo, "[%02d/%02d/%04d %02d:%02d:%02d] ",
            tempoAtual->tm_mday,
            tempoAtual->tm_mon + 1,
            tempoAtual->tm_year + 1900,
            tempoAtual->tm_hour,
            tempoAtual->tm_min,
            tempoAtual->tm_sec);

    fprintf(arquivo, "Palavra=%s | Criptografada=%s | SHIFT=%d | Tipo=%d (%s) | Letras=%d | Sequencia=",
            palavra, resultado, shift, tipo, nomeSequencia(tipo), tamanho);

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d", sequencia[i]);

        if (i < tamanho - 1) {
            fprintf(arquivo, ",");
        }
    }

    fprintf(arquivo, "\n");
    fclose(arquivo);
}
