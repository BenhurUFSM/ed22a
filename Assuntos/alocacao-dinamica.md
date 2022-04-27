## Alocação dinâmica de memória

A forma principal de abstração para a memória da linguagem C são as variáveis.
A criação de uma variável é uma forma organizada de se dizer ao compilador que se quer um tanto de memória, que esse tanto vai ser usado para armazenar dados de um determinado tipo, que vai passar a ser referenciado por tal nome dentro do programa.
O compilador vai então verificar que todo o uso dessa memória é realizado de acordo com esse "contrato", e vai tentar otimizar a quantidade de memória necessária para esse uso (por exemplo, quando uma função começa sua execução, suas variáveis precisam de memória, mas quando uma função termina de executar, essas variáveis não são mais necessárias, e a memória que elas estão utilizando pode ser reutilizada para outra coisa -- isso é feito automaticamente pelo compilador).

Mas essa forma de usar memória por vezes tem limitações, e em algumas situações surge a necessidade de se ter um controle maior sobre o uso da memória.
Por exemplo, para poder usar memória além da pré-definida pelas variáveis presentes no programa (pense em um programa que só vai poder definir quanto de memória vai precisar depois que já está executando, porque lê dados de um arquivo, por exemplo), ou para organizar o uso da memória de uma forma diferente da imposta pela alocação e liberação ligada automaticamente à ordem de execução das funções (uma função que cria uma variável e gostaria que ela pudesse ser usada pela função que a chamou, por exemplo).

Para esses casos, tem-se a alocação explícita de memória (mais conhecida como alocação dinâmica, que é um nome pior, porque a alocação automática feita pelo mecanismo de execução das funções também é dinâmica).
Nessa forma de alocação de memória, é o programador quem realiza a alocação e a liberação da memória, no momento que considerar mais adequado.
Essa memória é por vezes chamada de anônima, porque não é vinculada a uma variável com nome pré-definido.

Como essa memória não é associada a variáveis, a forma que se tem para usar esse tipo de memória é através de ponteiros.

Existem duas operações principais de manipulação desse tipo de memória: a operação de alocação e a operação de liberação de memória.
Quando se aloca memória, se diz quanto de memória se quer (quantos bytes), e se recebe do sistema esse tanto de memória, na forma de um ponteiro para a primeira posição do bloco de memória alocado. As demais posições seguem essa primeira, de forma contígua, como em um vetor.
Para se liberar a memória, passa-se um ponteiro para essa mesma posição, o sistema sabe quanto de memória foi alocada e faz o necessário para disponibilizar essa memória para outros usos.
Depois de liberado, o bloco de memória não pode mais ser utilizado.

Essas operações estão disponibilizadas em C na forma de funções, acessíveis incluindo-se `stdlib.h`.
Essas funções são `malloc` e `free`.
A função `malloc` recebe um único argumento, que é a quantidade de bytes que se deseja, e retorna um ponteiro para a região alocada, que tem esse número de bytes disponíveis. Caso a alocação não seja possível, o ponteiro retornado tem um valor especial, chamado `NULL`. Sempre deve-se testar o valor retornado por `malloc` para verificar se a alocação de memória foi bem sucedida.

A função `free` recebe um único argumento, que é um ponteiro para a primeira posição de memória do bloco a ser liberado, obrigatoriamente o mesmo valor retornado por um pedido de alocação de memória anterior.

Não existe limitação no tamanho de um bloco a alocar, nem na quantidade de blocos alocados, a não ser a quantidade de memória disponível.

Para facilitar o cálculo da quantidade de memória, existe o operador `sizeof`, que dá o número de bytes usado por qualquer tipo de dados. Por exemplo, `sizeof(double)` diz quantos bytes de memória são necessário para se armazenar um valor do tipo `double`.

Como a memória alocada é contígua, uma forma usual de se usar a memória alocada é como um vetor. Como vimos anteriormente, o uso de um vetor através de um ponteiro é muito semelhante (pra não dizer igual) ao uso de um vetor diretamente. O fato de o ponteiro estar apontando para memória alocada explicitamente ou estar apontando para memória que pertence a um vetor de verdade não muda a forma de uso.

Por exemplo, para se alocar memória para se usar como um vetor de tamanho definido em tempo de execução pelo usuário, pode-se usar algo como:

```c
#include <stdio.h>
#include <stdlib.h>

float calcula(int n, float v[n])
{
  // faz um cálculo complicado sobre os elementos do vetor
  float t=0;
  for (int i=0; i<n; i++) {
    t += v[i];
  }
  return t/n;
}

int main()
{
  float *vet;
  int n;
  printf("Quantos dados? ");
  scanf("%d", &n);

  vet = malloc(n * sizeof(float));
  if (vet == NULL) {
    printf("Não tenho tanta memória disponível!\n");
    return 5;
  }

  // a partir daqui, vet pode ser usado como se fosse um vetor de tamanho n
  for (int i=0; i<n; i++) {
    printf("digite o dado %d ", i);
    scanf("%f", &vet[i]);  // poderia também ser scanf("%f", vet+i);
  }
  float resultado = calcula(n, vet);
  printf("O resultado do cálculo é: %f\n", resultado);
  free(vet);
  // a partir daqui, a região apontada por vet não pode mais ser usada.
  return 0;
}
```

Uma outra função comum de alocação de memória é `realloc`. Ela permite alterar o tamanho de uma região de memória alocada dinamicamente.
O novo tamanho pode ser maior ou menor que o anterior.
A função deve receber um ponteiro para uma região de memória previamente alocada e um inteiro com o número de bytes que ela deve passar a ter.
A função aloca uma nova região com o novo tamanho, copia o conteúdo da região original paa a nova (limitado ao menor tamanho entre elas), libera a memória original e retorna um ponteiro para a nova região. caso algo dê errado (não conseguir alocar a nova região), ela mantém a região original intocada e retorna NULL.

O operador sizeof pode ser usado com qualquer tipo de dados, inclusive definidos por typedef.
Por exemplo, a função abaixo poderia ser usada para alocar memória para um vetor de dados e inicializar o vetor com ddados lidos de um arquivo. O arquivo contém uma linha inicial dizendo quantos dados ele contém e para cada dado tem uma linha com nome e valor.

```c
    typedef struct {
      char nome[50];
      float valor;
    } dado_t;

    // lê para d o próximo dado em arq; retorna true se OK
    bool le_dado(FILE *arq, dado_t *d)
    {
      if (fscanf(arq, "%s %f", d->nome, &d->valor) == 2) {
        return true;
      } else {
        return false;
      }
    }

    // lê um cadastro de dados de um arquivo chamado nome
    // coloca em *num o número de dados lidos e retorna um ponteiro para uma região
    // de memória alocada dinamicamente contendo os dados lidos
    dado_t *le_cadastro(int *num, char nome[])
    {
      // abre o arquivo
      FILE *arq;
      arq = fopen(nome, "r");
      if (arq == NULL) {
        return 0;
      }
      // lê o número de dados
      int n;
      fscanf(arq, "%d", &n); // deveria verificar se a leitura deu certo...
      // aloca memória para os dados
      dado_t *v;
      v = malloc(n * sizeof(dado_t));
      if (v == NULL) {
        printf("erro de alocacao de memoria");
        exit(1);
      }
      // lê os dados do arquivo para a memória
      for (int i = 0; i < n; i++) {
        if (!le_dado(arq, &v[i])) {
          // erro na leitura, ignora o resto do arquivo
          n = i;
          // deveria realocar a memória, para ficar do tamanho dos dados
          break;
        }
      }
      // fecha o arquivo, retorna
      fclose(arq);
      *num = n;
      return v;
    }
```

#### Exercícios com alocação de memória

Considere o programa abaixo, em que uma função chama outra para que coloque um número aleatório em uma variável:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void aleat(int *num, int min, int max)
{
  // coloca em *num um número aleatório entre min e max, inclusive
  int r;
  r = rand(); // rand() dá um número aleatório entre 0 e RAND_MAX (que é grandão)
  r = r % (max-min+1); // o resto da divisao por n está sempre entre 0 e n-1 (entre 0 e max-min no caso)
  r = r + min; // r agora estará entre min e max
  *num = r; 
}

int main()
{
  int x;
  srand(time(NULL)); // inicializa o gerador de números aleatórios; time(NULL) dá um número diferente a cada segundo.
  aleat(&x, 20, 25);
  printf("numero sorteado: %d\n", x);
  return 0;
}
```
1. Altere o programa para que a variável `x` (de `main`) seja alocada dinamicamente. A função `aleat` deve ficar a mesma.
2. Altere novamente o programa original, mudando `x` para ser um vetor, criando uma nova função, chamada por `main`, para preencher todo o vetor com números aleatórios (essa nova função deve chamar a função `aleat` para preencher cada posição do vetor).
3. Altere o programa do exercício anterior, alterando `main` para que aloque dinamicamente o vetor, após perguntar ao usuário quantos números ele quer. As demais funções devem ficar iguais.


Considere o programa abaixo, em que o dado `x` foi alterado para ser um registro com 2 inteiros, criado a partir do novo tipo `par`.
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int a;
  int b;
} par;

void aleat(int *num, int min, int max)
{
  // coloca em *num um número aleatório entre min e max, inclusive
  *num = rand() % (max-min+1) + min;
}

int main()
{
  par x;
  srand(time(NULL));
  aleat(&x.a, 20, 25);
  aleat(&x.b, 20, 25);
  printf("numeros sorteados: <%d %d>\n", x.a, x.b);
  return 0;
}
```

4. Altere o programa acima para que o par contenha dois números entre 1 e 100, e o segundo número obrigatoriamente deve ser maior que o primeiro. Só pode chamar `aleat` duas vezes. Não pode alterar `aleat`.
5. Altere o programa novamente, para que o preenchimento do par seja feito por uma função, que recebe um ponteiro para `par`. Essa função deve ser declarada assim: `void preenche_par(par *p)`.
6. Altere novamente, para que x seja um vetor de `par`. `main` deve chamar uma nova função, para preencher o vetor (`void preenche_vetor(par vet[], int n);` ou `void preenche_vetor(par *vet, int n);`, `n` é o número de elementos a preencher). Essa nova função, por sua vez, deve chamar a função `preenche_par` do ex. anterior.
7. Altere mais uma vez, agora o vetor em `main` deve ser criado dinamicamente, com tamanho pedido ao usuário.


Em todos os programas anteriores, faltou liberar a memória alocada dinamicamente. Que tal alterá-los?

8. Os dados podem ser centralizados em uma estrutura única, que contém todo o necessário para manter um vetor de pares, diminuindo o espalhamento de informações inter-relacionadas. A função `main` poderia ser como mostrado abaixo.
```c
//...//
typedef struct {
  int n_pares;
  par *pares;
} vet_par;

int main()
{
  vet_par x;
  srand(time(NULL));
  printf("Digite o número de pares: ");
  scanf("%d", &x.n_pares);
  x.pares = malloc(x.n_pares*sizeof(par));
  preenche_vetor(x.pares, x.n_pares);
  for(int i = 0; i < x.n_pares; i++){
    printf("numeros sorteados: <%d %d>\n", x.pares[i].a, x.pares[i].b);
  }
  // faltou liberar a memória
  return 0;
}
```
Essa centralização permite a simplificação das interfaces das funções, porque concentra toda a informação sobre os pares em um único lugar. Fica mais claro ainda com uma interface usando ponteiros. Implemente (ou altere) as funções auxiliares para que `main` possa ser escrita assim:
```c
int main()
{
  vet_par *x;
  srand(time(NULL));
  x = le_pares();
  imprime_pares(x);
  libera_pares(x);
  return 0;
}
```

#### Sintaxe C para vetores, ponteiros, structs

Considere o trecho de código abaixo:
```c
typedef struct {
  int a;
  int b[5];
} reg;

reg r;
reg vr[10];
reg *p, *q;
p = &vr[5];
q = &vr[7];
```

a expressão | é equivalente a
:---------- | :--------------
`p`         | `&vr[5]`
`*p`        | `vr[5]`
`(*p).a`    | `vr[5].a`
`p->a`      | `vr[5].a`
`p->a`      | `(*p).a`
`*p.a`      | erro
`*r.b`      | `r.b[0]`
`*p->b`     | `vr[5].b[0]`
`p+2`       | `q`
`q-p`       | `2`

Se `p` é um ponteiro para o primeiro elemento de um vetor, os elementos desse vetor podem ser acessados com uma sintaxe de vetor assim:
```c
for (i=0; i<n; i++) {
  acessa(p[i]);
}
```
ou pode-se usar aritmética de ponteiros (alterando o valor de p a cada vez):
```c
for (i=0; i<n; i++) {
  acessa(*p);
  p++;
}
```
Como o incremento do ponteiro (++) só é feito depois de seu valor ser usado, poderia ser assim:
```c
for (i=0; i<n; i++) {
  acessa(*p++);
}
```
ou ainda, se a função de acesso receber um ponteiro para o dado em vez do dado:
```c
for (i=0; i<n; i++) {
  acessa(p++);
}
```
