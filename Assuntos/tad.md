## Tipos abstratos de dados (TADs)

Veja (e leia) a seção 2.2 do livro da Nina Edelweiss e da Renata Galante.

### Implementação de TAD em C

Um tipo abstrato de dados é constituído por:
- descrição do conjunto de valores que um dado desse tipo pode ter
- as operações que podem ser realizadas sobre dados desse tipo.

É importante ter uma separação entre a implementação de um TAD e seu uso.
Para que essa separação seja possível, se necessita de uma boa definição da interface entre essas partes.

Na disciplina, iremos implementar TADs de acordo com a descrição abaixo.

Deve ser escolhido um nome que identifique o TAD (aqui referenciado como *tad*).
Cada TAD será implementado em dois arquivos que só serão usados para esse fim.
A interface pública do TAD (a declaração do tipo, a declaração das funções que implementam as operações públicas sobre dados desse tipo, constantes necessárias para uso desse tipo etc) será colocada em um arquivo de cabeçalho chamado "*tad*.h".
A implementação do TAD será feita em um arquivo chamado *tad*.c. Esse arquivo deve incluir o arquivo *tad*.h no seu início.

Todos os nomes de funções que implementam as operações do tipo *tad*_t serão prefixadas com *tad_*.

Em um .c que seja cliente (que use) o TAD, deve haver a inclusão do arquivo *tad*.h, e o cliente só tem o direito de usar os tipos e funções ali declarados para operar sobre um dado desse tipo.

Para que o tipo de dados seja opaco aos clientes (eles não tenham acesso aos dados internos que constituem o TAD), nosso TAD será declarado no .h como
```c
   typedef struct tad tad_t;
```
Essa struct deve ser declarada no início do arquivo *tad*.c.

Como os clientes não terão acesso ao tipo *tad_t* completo, não poderão declarar uma variável desse tipo.
O acesso à variáveis desse tipo será sempre feito através de ponteiros.
Todos os TADs terão funções para a criação e destruição de uma variável do tipo, com os nomes *tad_cria()* e *tad_destroi()*.
A primeira recebe argumentos necessários à criação de uma variável, aloca memória para essa variável, inicializa essa memória e retorna um ponteiro para a variável criada.
A segunda recebe um ponteiro para a variável a ser destruída, realiza alguma operação de finalização do dado se for necessário, libera a memória ocupada pelo dado.

Todas as funções do .h exceto a função de criação reebem como primeiro argumento um ponteiro para o dado sobre o qual elas devem operar.

Caso se necessite de funções auxiliares na implementação do TAD, para que elas não sejam acessíveis pelos clientes, devem ser declaradas somente no .c, com o atributo *static*.

### Exemplo de implementação de um TAD

Para exemplificar, vamos ver como poderia ser a implementação de um TAD para representar datas, de acordo com essas considerações.
O nome escolhido para o TAD é *data*.
As operações a realizar sobre dados desse tipo (é só um exemplo, poderia-se ter escolhido outro conjunto de operações):
- criação de uma data, fornecendo dia, mês, ano
- destruição de uma data
- obtenção do dia da data
- obtenção do mês da data
- obtenção do ano da data
- cálculo do número de dias entre duas datas
- obtenção de uma data a tantos dias de distância da outra

O arquivo `data.h`:
```c
   #ifndef _DATA_H_    // para evitar a inclusão múltipla deste arquivo
   #define _DATA_H_
   
   // o tipo d dados data_t
   typedef struct data data_t;
   
   // criação de uma data
   data_t *data_cria(int dia, int mes, int ano);
   
   // destruição de uma data
   void data_destroi(data_t *d);
   
   // obtenção do dia da data
   int data_dia(data_t *d);
   
   // obtenção do mês da data
   int data_mes(data_t *d);
   
   // obtenção do ano da data
   int data_ano(data_t *d);
   
   // cálculo do número de dias entre duas datas
   int data_dias_ate(data_t *d1, data_t *d2);
   
   // obtenção de uma data a tantos dias de distância da outra
   data_t *data_apos_dias(data_t *d, int dias);
   
   #endif  // _DATA_H_
```
O arquivo `data.c`
```c
   #include "data.h"
   #include <stdbool.h>
   #include <stdlib.h>
   
   struct data {
     int dia;
     int mes;
     int ano;
   };
   
   // retorna true se for data válida
   static bool data_ok(int d, int m, int a)
   {
     // testes para ver se d/m/a constituem uma data válida
     // ...
     return true; // ou nao
   }
   
   data_t *data_cria(int dia, int mes, int ano)
   {
     if (!data_ok(dia, mes, ano)) return NULL;
     data_t *d = malloc(sizeof(data_t));
     if (d != NULL) {
       d->dia = dia;
       d->mes = mes;
       d->ano = ano;
     }
     return d;
   }
   
   // destruição de uma data
   void data_destroi(data_t *d)
   {
     free(d);
   }
   
   // obtenção do dia da data
   int data_dia(data_t *d)
   {
     return d->dia;
   }
   
   // obtenção do mês da data
   int data_mes(data_t *d)
   {
     return d->mes;
   }
   
   // obtenção do ano da data
   int data_ano(data_t *d)
   {
     return d->ano;
   }
   
   // cálculo do número de dias entre duas datas
   int data_dias_ate(data_t *d1, data_t *d2)
   {
     if (d1->mes == d2->mes && d1->ano == d2->ano) {
       return d2->dia - d1->dia;
     }
     // ...
   }
   
   // obtenção de uma data a tantos dias de distância da outra
   data_t *data_apos_dias(data_t *d, int dias)
   {
     return data_cria(d->dia + dias, d->mes, d->ano); // talvez necessite refinamentos
   }
```
Um possível cliente:
```c
   #include "data.h"
   #include <stdio.h>
   
   int main()
   {
     data_t *hoje, *amanha;
     
     hoje = data_cria(6, 5, 2022);
     amanha = data_apos_dias(hoje, 1);
     printf("Amanhã será %02d/%02d/%04d.\n", data_dia(amanha), data_mes(amanha), data_ano(amanha));
     
     data_destroi(hoje);
     data_destroi(amanha);
     
     return 0;
   }
```
