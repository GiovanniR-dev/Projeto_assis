# Atividade Avaliativa 02 — Criptografia Matemática em C

## Disciplina
Algoritmo e Pensamento Computacional

## Tema
Integração entre criptografia simples, matemática aplicada e conceitos computacionais.

## Objetivo

Desenvolver um programa em linguagem C que una:

- Cifra de César;
- Progressão Aritmética (PA);
- Progressão Geométrica (PG);
- Série de Fibonacci;
- Números primos;
- arrays/vetores;
- funções;
- ponteiros/parâmetros por referência conceitual;
- arquivos;
- menu de seleção;
- geração de log.

O programa utiliza duas camadas de criptografia:

**Camada 1:** deslocamento fixo definido pelo usuário (SHIFT).

**Camada 2:** deslocamento variável fornecido por uma sequência matemática.

A fórmula utilizada em cada posição é:

`deslocamento total = SHIFT + sequencia[i]`

Depois, o valor é aplicado ao alfabeto de 26 letras usando módulo 26.

---

## Taxonomia de Bloom aplicada

### Lembrar
O aluno revisa:
- alfabeto;
- valores/posições das letras;
- conceito de ASCII;
- progressões e sequências.

### Compreender
O aluno entende:
- como a Cifra de César desloca letras;
- como uma sequência pode gerar deslocamentos diferentes;
- como o módulo 26 mantém o resultado no alfabeto.

### Aplicar
O aluno implementa:
- funções;
- vetores;
- estruturas de decisão e repetição;
- criptografia;
- geração das sequências;
- gravação em arquivos.

### Analisar
O aluno compara:
- PA;
- PG;
- Fibonacci;
- números primos;
- diferentes valores de SHIFT.

### Avaliar
O aluno analisa se uma sequência produz um padrão mais previsível ou menos previsível.

> Observação: este programa é uma atividade didática. A cifra resultante não deve ser considerada criptografia segura para proteger dados reais.

### Criar
O aluno pode modificar:
- valores iniciais;
- razões;
- fórmulas;
- novas sequências;
- formato dos arquivos;
- novas camadas de criptografia.

---

## Como funciona

Exemplo:

Palavra: `coracao`

SHIFT: `3`

Sequência Fibonacci:

`1, 1, 2, 3, 5, 8, 13`

Para cada letra:

`deslocamento = SHIFT + sequencia[i]`

Assim:

- c + (3+1) = g
- o + (3+1) = s
- r + (3+2) = w
- a + (3+3) = g
- c + (3+5) = k
- a + (3+8) = l
- o + (3+13) = e

Resultado:

`gswgkle`

---

## Correção importante do exemplo fornecido na atividade

O enunciado apresenta:

`coracao + SHIFT 3 + Fibonacci -> fqvdjqb`

Porém, esse resultado **não corresponde à fórmula informada** (`SHIFT + sequência[i]`).

Aplicando corretamente:

`coracao`

com SHIFT `3` e Fibonacci `1, 1, 2, 3, 5, 8, 13`

o resultado é:

`gswgkle`

Portanto, para evitar erro matemático na entrega, o programa e esta documentação utilizam o resultado calculado pela fórmula do enunciado.

---

## Sequências implementadas

### 1. PA

Fórmula:

`a(n) = a1 + (n-1) * r`

Exemplo:

`5, 8, 11, 14...`

### 2. PG

Fórmula:

`a(n) = a1 * q^(n-1)`

Exemplo:

`2, 4, 8, 16...`

No programa, os termos são reduzidos módulo 26 antes de serem utilizados no deslocamento, evitando crescimento desnecessário dos valores.

### 3. Fibonacci

Fórmula:

`F(n) = F(n-1) + F(n-2)`

Com:

`F1 = 1` e `F2 = 1`

Exemplo:

`1, 1, 2, 3, 5, 8, 13...`

### 4. Números primos

São gerados os primeiros números primos:

`2, 3, 5, 7, 11, 13, 17...`

---

## Conceitos de C utilizados

O projeto utiliza:

- `if/else`;
- `switch`;
- `for`;
- `while`;
- funções;
- vetores;
- strings;
- ponteiros como parâmetros de funções;
- `enum`;
- arquivos com `FILE`;
- `fopen`;
- `fprintf`;
- `fclose`;
- `strlen`;
- `isalpha`;
- `time`;
- `struct tm`.

---

## Arquivos gerados

Ao executar o programa, são criados:

### resultado_criptografia.txt

Armazena o resultado da execução atual.

### log_criptografia.txt

Armazena um histórico das execuções, incluindo data e hora.

---

## Compilação

### GCC

No terminal:

```bash
gcc criptografia_matematica.c -o criptografia_matematica
```

Executar no Windows:

```bash
.\criptografia_matematica.exe
```

---

## Exemplo de execução

```text
===============================================
   SISTEMA DE CRIPTOGRAFIA MATEMATICA EM C
===============================================

Digite a palavra secreta (ate 15 letras, sem acentos): coracao
Digite o valor do SHIFT (pode ser positivo ou negativo): 3

Escolha a sequencia matematica:
1 - Progressao Aritmetica (PA)
2 - Progressao Geometrica (PG)
3 - Fibonacci
4 - Numeros Primos
Opcao: 3

RESULTADO DA CRIPTOGRAFIA
Palavra original: coracao
SHIFT fixo: 3
Tipo de sequencia: Fibonacci
Sequencia aplicada: 1, 1, 2, 3, 5, 8, 13
Palavra criptografada: gswgkle
```

---

## Estrutura sugerida para o GitHub

```text
atividade-criptografia-c/
├── criptografia_matematica.c
├── README.md
├── resultado_criptografia.txt
└── log_criptografia.txt
```

---

## Conclusão

O projeto demonstra como conceitos de algoritmos, matemática e programação podem ser integrados em uma aplicação única.

A Cifra de César fornece a primeira camada de deslocamento, enquanto uma sequência matemática modifica o deslocamento de cada letra. Dessa forma, o resultado depende simultaneamente do SHIFT escolhido e da sequência selecionada.

A atividade também permite analisar como diferentes padrões matemáticos influenciam o resultado da codificação, desenvolvendo raciocínio lógico, capacidade de análise e aplicação prática dos conceitos estudados.
