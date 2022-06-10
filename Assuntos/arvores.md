## Árvores

Uma árvore é uma estrutura de dados que organiza os dados que guarda de uma forma hierárquica, muito semelhante a uma hierarquia de diretórios e arquivos.
Cada dado em uma árvore é armazenado em um "nó".
Uma árvore é um conjunto de nós, com as seguintes características:
- se o conjunto de nós está vazio, a árvore é vazia;
- senão, um dos nós do conjunto é chamado de "raiz" da árvore, e os demais são divididos em subconjuntos disjuntos, cada um deles uma árvore, chamadas de subárvores da raiz.

Existem várias formas de se representar graficamente uma árvore, a mais comum é representar os nós como círculos, dentro dos quais está o valor do nó, o círculo que corresponde à raiz acima dos que correspondem às raízes de suas subárvores, com setas ligando a raiz da árvore às raízes das subárvores.

Alguns conceitos de árvores:
- filhos de um nó: raízes das subárvores da árvore que tem esse nó como raiz;
- nó raiz: nó da árvore que não tem pai;
- nó folha ou nó externo: nó da árvore que não tem filho;
- nó interno: nó que tem filho;
- grau de um nó: número de filhos que o nó tem;
- grau de uma árvore: maior grau encontrado em um nó da árvore;
- caminho em uma árvore: sequência de nós (não repetidos) da árvore, onde dois nós adjacentes têm a relação pai-filho;
- comprimento de um caminho: número de arestas em um caminho, um a menos que o número de nós do caminho (alguns autores consideram que o comprimento de um caminho é o número de nós do caminho, mas aparentemente esses autores são minoritários);
- profundidade de um nó: comprimento do caminho entre a raiz da árvore e esse nó;
- nível de uma árvore: conjunto de nós que estão na mesma profundidade; a raiz está no nível 0, seus filhos no nível 1, os filhos dles on nível 2, etc;
- altura de uma árvore: comprimento do maior caminho entre a raiz e alguma folha da árvore ou profundidade do nó mais profundo da árvore; uma árvore somente com o nó raiz tem altura 0; uma árvore vazia tem altura -1.

Quando a ordem dos filhos de um nó é importante, diz-se que a árvore é **ordenada**. Nesse caso, a árvore que tem a raiz A e os filhos B e C é considerada diferente da árvore que tem raiz A e filhos C e B. Se as árvores forem não ordenadas, essas duas árvores são consideradas iguais.

Nesta disciplina, nos concentraremos em um tipo especial de árvores, as árvores de grau 2, ou *árvores binárias*.

### Árvores binárias

Em uma árvore binária, cada nó tem no máximo 2 filhos. Nos restringiremos ao estudo de árvores ordenadas, então a ordem entre esses dois filhos é uma informação importante. Como são só dois filhos, eles são comumente chamados de filho esquerdo e direito.

Árvores binárias são estruturas definidas de forma recursiva, uma árvore binária pode ser:
- vazia; ou
- um nó, chamado de raiz e dois filhos, que são árvores binárias.
e duas em que um deles é o nó raiz e os restantes são divididos em duas árvores filhas)

Uma forma comum de implementação de uma árvore é como um ponteiro para um nó, e esse nó contém o valor associado ao nó e dois ponteiros para os nós raiz das árvores filhas. Uma árvore vazia pode ser implementada como um ponteiro nulo ou como um nó cujo valor é ignorado e tem os dois ponteiros para nulo. Na primeira implementação, será alocado um nó para cada valor armazenado na árvore. Na segunda, será alocado, além desses, um nó a mais para cada filho vazio, duplicando o núemro de nós ocupados pela árvore, mas simplificando a interface de funções que alteram a árvore (veremos mais tarde na discussão sobre inserção e remoção).

```c
   typedef struct no no_t;
   struct no {
     dado_t val;
     no_t *esq;
     no_t *dir;
   };
   typedef no_t arv_t;  // um sinonimo, uma árvore é representada por um ponteiro para um nó
```

Grande parte dos algoritmos que operam sobre árvores são mais facilmente implementados em forma recursiva.
Por exemplo, para calcular quantos nós tem uma árvore, pode-se usar uma definição recursiva:
   - uma árvore vazia tem 0 nós
   - uma árvore não vazia tem um nó a mais que a soma dos nós de suas duas subárvores.
Em código:
```c
   int num_nos(arv_t *a)
   {
      if (vazia(a)) return 0;
      return 1 + num_nos(a->esq) + num_nos(a->dir);
   }
```
Para calcular a altura de uma árvore:
   - uma árvore vazia tem altura -1
   - uma árvore não vazia tem altura que é um além da maior altura entre as árvores filhas.
Em código:
```c
   int altura(arv_t *a)
   {
      if (vazia(a)) return -1;
      return 1 + maior(altura(a->esq), altura(a->dir));
   }
```

A função que testa se uma árvore é vazia testa se o ponteiro é NULL no caso de se implementar ávore vazia como ponteiro NULL ou testa se os ponteiros esq e dir são NULL, se for essa a implementação escolhida.

#### Exercícios

1. Faça uma função que recebe uma árvore e retorna quantos nós folha ela tem
2. Faça uma função que recebe uma árvore e retorna quantos nós não folha ela tem
3. Faça uma função que recebe uma árvore e um valor e retorna um booleano que diz se a árvore contém ou não um nó com esse valor. Use a função auxiliar `bool valores_iguais(dado_t, dado_t)` para comparar dois valores.
4. Faça uma função que recebe uma árvore e um valor e retorna o nível nessa árvore que está o nó que contém esse valor, ou -1 se o valor não estiver em nenhum nó da árvore. A raiz de uma árvore está no nível 0, os filhos da raiz no nível 1 etc.
5. Faça uma função que recebe uma árvore e retorna o "fator de equilíbrio" do nó raiz dessa árvore. O "fator de equilíbrio" a ser considerado é a diferença entre a altura da subárvore esquerda e a da direita.

Para testar essas funções, pode fazer uma árvore que armazena dados inteiros, e uma função que aloca um nó e retorna um ponteiro para ele, recebendo como argumentos o valor do nó e os ponteiros para os dois filhos. Uma árvore com a raiz com valor 1, o filho esquerdo com valor 2 e o direito com o valor 3 poderia ser criada assim (com árvore vazia sendo representada como NULL):
```c
   arv_t *no(dado_t d, arv_t *esq, arv_t *dir)
   {
      arv_t *n = malloc(sizeof(arv_t));
      assert(n != NULL);
      n->val = d;
      n->esq = esq;
      n->dir = dir;
      return n;
   }
   //...
   arv_t *a = no(1, no(2, NULL, NULL), no(3, NULL, NULL));
```
Ou por exempo assim, com a árvore vazia representada por um nó com ponteiros NULL:
```c
   no_t *cria_no_vazio(void)
   {
      no_t *n = malloc(sizeof(no_t));
      assert(n != NULL);
      // o valor nunca vai ser usado
      n->esq = NULL;
      n->dir = NULL;
      return n;
   }
   
   void troca_valor(no_t *a, dado_t d)
   {
      if (vazia(a)) {  // vai deixar de ser uma árvore vazia, coloca árvores vazias como filhos
        a->esq = cria_no_vazio();
        a->dir = cria_no_vazio();
      }
      a->val = d;
   }
   //...
   arv_t *a = cria_no_vazio(); // ou poderia ser arv_cria(), pra ficar como os TAD vistos antes
   troca_valor(a, 1);
   troca_valor(a->esq, 2);
   troca_valor(a->dir, 3);
```


### Percurso em uma árvore

Um percurso em uma árvore é uma forma de caminhamento entre os nós da árvore que visita todos os nós.
Dependendo da ordem em que os nós são visitados, tem-se percursos diferentes.
Os principais tipos de percurso em uma árvore são:
- percurso em largura: visita os nós, a partir da raiz, um nível por vez (primeiro visita a raiz, depois todos seus filhos, depois todos seus netos etc);
- percurso em profundidade: visita os nós, percorrendo um ramo até seu final antes de seguir pelo ramo seguinte. Tem três percursos em profundidade principais:
   - percurso em pré-ordem: visita primeiro um nó, antes de realizar um percurso em pré-ordem iniciando em cada um de seus filhos;
   - percurso em pós-ordem: percorre em pós-ordem cada um dos filhos de um nó antes de visitar o nó;
   - percurso em-ordem (somente em árvores binárias, de grau dois): percorre em-ordem a subárvore esquerda, então visita o nó, e depois percorre em-ordem a subárvore direita.

Esse percursos podem ainda ser subclassificados em "à esquerda" e "à direita", de acordo com a ordem que os filhos são percorridos.

Esses percursos são tipicamente implementados por funções recursivas (exceto o percurso em largura), como abaixo:
```
   pre_ordem(arvore a)
   {
      if !vazia(a):
         visita(a)
         para cada sa, subárvore de a:
            pre_ordem(sa)
   }
```
No caso de uma árvore binária implementada como acima, um percurso em-ordem à esquerda poderia ser, em C:
```c
   void em_ordem(arv_t *a)
   {
     if (vazia(a)) return;
     em_ordem(a->esq);
     visita(a);
     em_ordem(a->dir);
   }
```

Em vez de uma função recursiva, pode-se implementar o percurso em profundidade com uma função não recursiva e a ajuda de uma pilha. O percurso em pré-ordem é o mais simples de ser implementado dessa forma:
```c
   void pre_ordem(arv_t *a)
   {
     if (vazia(a)) return;
     pilha_t *p = pilha_cria();
     pilha_insere(p, a);
     while (!pilha_vazia(p)) {
       a = pilha_remove(p);
       visita(a);
       if (!vazia(a->dir)) pilha_insere(p, a->dir);
       if (!vazia(a->esq)) pilha_insere(p, a->esq);
     }
     pilha_destroi(p);
   }
```

O percurso em largura é tipicamente implementado com o auxílio de uma fila:
```
   largura(arvore a)
   {
      fila f
      se a não está vazia:
         insere(f, a)
      while !vazia(f):
         arvore b = remove(f)
         visita(b)
         para cada sa, subárvore de b:
            insere(f, sa)
   }
```

Considere a árvore descrita abaixo (quem não tá na coluna da esquerda é folha):
|  nó | esq | dir |
| :---: | :---: | :---: |
|  a  | b   | c   |
|  b  | d   | e   |
|  c  | /   | f   |
|  d  | g   | /   |
|  e  | i   | j   |
|  f  | h   | k   |

Em alguns dos percursos comuns, os nós seriam visitados na ordem abaixo:
| percurso | ordem da visita |
| :--- | :---:
| pré-ordem à esquerda | a b d g e i j c f h k |
| pré-ordem à direita  | a c f k h b e j i d g |
| em-ordem à esquerda  | g d b i e j a c h f k |
| em largura           | a b c d e f g i j h k |


### Árvores binárias de busca

Uma árvore binária de busca (ABB) é uma árvore binária, ordenada, com nós com valores comparáveis entre si.
Com "comparáveis entre si" quero dizer que eles têm uma ordem absoluta definida, ou seja, se A, B e C são valores que podem ser colocados na árvore, se A < B e B < C então A < C.
Todos os nós da subárvore esquerda do nó que contém o valor V contêm valores menores que V; todos os nós da subárvore direita do nó que contém V contêm valores maiores que V. Todas as subárvores de uma ABB são ABB.

A busca por um valor em uma ABB é rápida e simples: comparando-se o valor buscado com o valor de um nó, elimina-se da busca uma das subárvores desse nó (se o valor buscado é menor que o valor do nó, ele certamente não estará entre os valores da subárvore direita, que só contém valores superiores ao valor do nó. A busca só precisa percorrer um caminho na árvore para decidir se o valor procurado está ou não nessa árvore. No pior dos casos, percorre a altura da árvore. Se a árvore é equilibrada (as subárvores esquerda e direita de cada nó têm "pesos" semelhantes), a altura de uma árvore binária com *n* nós é próxima a *log<sub>2</sub>n*.

Um percurso em-ordem em uma ABB visitará os nós em ordem crescente. Pode-se usar uma ABB para ordenar um conjunto de dados: insere-se todos os dados em uma ABB inicialmente vazia, e depois percorre-se a árvore em-ordem.

#### Busca

A **busca** por um dado em uma ABB pode ser implementada por uma função como a abaixo, que retorna um ponteiro para o dado armazenado na árvore que compara como igual ao valor procurado, ou NULL:
```c
   dado_t *busca(no_t *a, dado_t valor)
   {
     if (vazia(a)) {
       return NULL;               // o valor certamente não está em uma árvore vazia!
     } else if (iguais(valor, a->dado)) {
       return &(a->dado);         // achei!
     } else if (menor(valor, a->dado)) {
       return busca(a->esq, val); // valor pequeno, continua a busca na subárvore esquerda
     } else {
       return busca(a->dir, val); // valor grande, continua pela direita
     }
   }
```
Uma versão não recursiva:
```c
   dado_t *busca(no_t *a, dado_t valor)
   {
     while (!vazia(a)) {
       if (iguais(valor, a->dado)) {
         return &a->dado;   // achei!
       } else if (menor(valor, a->dado)) {
         a = a->esq;        // valor pequeno, continua a busca na subárvore esquerda
       } else {
         a = a->dir;        // valor grande, continua pela direita
     }
     return NULL;           // o valor certamente não está em uma árvore vazia!
   }
```

#### Inserção

Em uma árvore binária, pode-se considerar que todos os seus nós têm dois filhos, que podem ser uma ABB normal ou uma árvore vazia. Uma árvore binária com *n* nós não vazios tem *n+1* nós vazios. Quando se faz uma **inserção** em uma ABB, o novo valor irá ocupar uma dessas *n+1* posições vazias, e a decisão de qual delas depende exclusivamente do valor a ser inserido: tem uma para valores inferiores ao menor valor já presente na árvore, outra para um valor entre o menor e o segundo menor valores da árvore e assim por diante.
O algoritmo para escolher a posição de inserção é muito semelhante ao de busca (afinal, se esse dado já estivesse na árvore e fosse buscado, o algoritmo de busca deveria encontrá-lo).

Em outras palavras, em uma inserção uma árvore vazia será transformada em uma árvore com um só nó. Essa transformação tem consequências em como implementar a inserção, dependendo da forma como uma árvore vazia é implementada.
Caso a árvore vazia seja implementada como um ponteiro nulo, a inserção de um valor nessa árvore deve alterar esse ponteiro.
Se uma função de inserção tem a interface ```void insere(no_t *a, dado_t valor)``` e `a` é uma árvore vazia, a função receberá em `a` um valor nulo, e não terá como alterar o valor do ponteiro que contém esse nulo, para que aponte para o novo nó. A função teria que ter uma interface alternativa, ou ela recebe um ponteiro para o ponteiro para poder alterá-lo (`void insere(no_t **a, dado_t valor)`), ou ela retorna o valor com o ponteiro para o novo nó (`no_t *insere(no_t *a, dado_t valor)`). 
Quando se implementa a árvore vazia com um nó vazio, esse problema não existe, porque o ponteiro que representa a árvore já está apontando para um nó; esse nó é transformado em um nó folha (e cria-se mais dois nós vazios para serem seus filhos), e o ponteiro que representa a árvore não precisa ser alterado, continua apontando para o mesmo nó de antes da inserção.

A figura abaixo mostra o estado de uma árvore vazia e da mesma árvore após a inserção de um valor, para o caso de implementação de árvore vazia com ponteiro nulo e com nó nulo.
![figura](https://github.com/BenhurUFSM/ed21a/blob/main/Complementos/ed21a-inser%C3%A7%C3%A3o%20em%20%C3%A1rvore.png)

As três implementações alternativas de inserção em uma ABB estão abaixo:
```c
    // inserção em uma ABB com árvore vazia sendo representada por um nó nulo
    void insere(no_t *a, dado_t valor)
    {
       if (vazia(a)) {  // a->esq e a->dir são NULL
          a->dado = valor;
          a->esq = cria_no_vazio();
          a->dir = cria_no_vazio();
       } else if (iguais(valor, a->dado)) {
          ; // ou reaje de outra forma para inserção de valor já existente
       } else if (menor(valor, a->dado) {
          insere(a->esq, valor);   // valor pequeno, insere na subárvore esquerda
       } else {
          insere(a->dir, valor);   // valor grande, insere na subárvore direita
       }
    }
```
```c
    // inserção em uma ABB com árvore vazia sendo representada por ponteiro nulo
    //   versão com retorno da árvore
    no_t *insere(no_t *a, dado_t valor)
    {
       if (vazia(a)) {  // a == NULL
          a = cria_no(valor, NULL, NULL);
       } else if (iguais(valor, a->dado)) {
          ; // ou reaje de outra forma para inserção de valor já existente
       } else if (menor(valor, a->dado)) {
          a->esq = insere(a->esq, valor);   // valor pequeno, insere na subárvore esquerda
       } else {
          a->dir = insere(a->dir, valor);   // valor grande, insere na subárvore direita
       }
       return a;
    }
```
```c
    // inserção em uma ABB com árvore vazia sendo representada por ponteiro nulo
    //   versão com ponteiro para ponteiro
    void insere(no_t **pa, dado_t valor)
    {
       if (vazia(*pa)) {  // *pa == NULL
          *pa = cria_no(valor, NULL, NULL);
       } else if (iguais(valor, (*pa)->dado)) {
          ; // ou reaje de outra forma para inserção de valor já existente
       } else if (menor(valor, (*pa)->dado)) {
          insere(&((*pa)->esq), valor);   // valor pequeno, insere na subárvore esquerda
       } else {
          insere(&((*pa)->dir), valor);   // valor grande, insere na subárvore direita
       }
    }
```
Dá para melhorar um pouco a sintaxe pesada usando variável auxiliar:
```c
    // inserção em uma ABB com árvore vazia sendo representada por ponteiro nulo
    //   versão com ponteiro para ponteiro
    void insere(no_t **pa, dado_t valor)
    {
       no_t *a;
       a = *pa;
       if (vazia(a)) {  // a == NULL
          a = cria_no(valor, NULL, NULL);
          *pa = a;
       } else if (iguais(valor, a->dado)) {
          ; // ou reaje de outra forma para inserção de valor já existente
       } else if (menor(valor, a->dado)) {
          insere(&(a->esq), valor);   // valor pequeno, insere na subárvore esquerda
       } else {
          insere(&(a->dir), valor);   // valor grande, insere na subárvore direita
       }
    }
```
Ou talvez com uma versão não recursiva:
```c
    // inserção em uma ABB com árvore vazia sendo representada por ponteiro nulo
    //   versão com ponteiro para ponteiro, não recursiva
    void insere(no_t **pa, dado_t valor)
    {
       no_t *a;
       a = *pa;
       while (!vazia(a)) {  // a == NULL
          if (iguais(valor, a->dado)) {
             return; // ou reaje de outra forma para inserção de valor já existente
          } else if (menor(valor, a->dado)) {
             pa = &(a->esq);   // valor pequeno, continua na subárvore esquerda
             a = *pa;
          } else {
             pa = &(a->dir);   // valor grande, continua na subárvore direita
             a = *pa;
             // por que não dá pra fazer   a = a->dir;  pa = &a;  ??
          }
       }
       a = cria_no(valor, NULL, NULL);
       *pa = a;
    }
```


#### Remoção

A **remoção** tem um problema semelhante à inserção, em que uma folha pode ser transformada em uma árvore vazia, exigindo a troca do ponteiro para nulo, no caso de implementação com ponteiros nulos. A solução é semelhante à da inserção.
Por ter um código mais limpo, vamor considerar a implementação com árvores vazias representadas como nó nulo. A implementação com ponteiro nulo fica com exercício.

A remoção tem três casos, um muito simples, um simples e um menos simples: 
- o caso muito simples é quando o dado a ser removido não está na árvore, não há nada a ser feito;
- o caso simples é quando o dado a ser removido está em um nó folha, basta transformá-lo em uma árvore vazia;
- o caso menos simples é quando o nó que contém o dado a ser removido é um nó interno da árvore, que contém filhos.

Vamos deixar o terceiro caso para mais tarde.

Nos demais casos, a remoção não é muito diferente da busca ou inserção:
```c
   void remove(arv_t *a, dado_t valor)
   {
      if (vazia(a)) {
         return;                     // arvore vazia não tem o dado, não faz nada
      } else if (iguais(valor, a->dado)) {
         if (folha(a)) {  // o caso fácil, transforma a em árvore vazia
            a->dado = NAO_TEM_DADO_AQUI;
            free(a->esq);  // libera o nó vazio
            free(a->dir);  // o outro também
            a->esq = a->dir = NULL; // para reconhecermos como nó vazio mais tarde
         } else {  // o caso menos fácil, o nó tem filho(s)!
            // TODO
         }
      } else if (menor(valor, a->dado)) {
         remove(a->esq, valor);      // valor pequeno, remove da esquerda
      } else {
         remove(a->dir, valor);      // valor grande, remove da direita
      }
   }
```

O problema da remoção de um nó interno é o que fazer com os filhos do nó removido, eles devem permanecer na árvore.
Para evitar o caos, o que normalmente se faz é escolher um valor mais abaixo na árvore que possa ocupar o lugar do valor removido, e depois remover esse valor da subárvore onde ele se encontra. Como esse valor está mais baixo na árvore, deve chegar uma hora em que o velor a ser removido está em uma folha, e voltamos ao caso simples.
Para garantir que não sejam necessárias maiores alterações na árvore, deve-se escolher um valor substituto que mantém o restante da árvore correta em relação às restrições de uma ABB (todos os valores na subárvore direita do nó alterado devem continuar maiores que o valor escolhido para esse nó, e os da esquerda devem ser menores). Dois valores na árvore são candidatos ideais: os dois vizinhos do valor removido, considerando a ordem dos valores dos nós.

Por exemplo, se uma árvore contém os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e o valor 5 está na raiz, os valores 1, 2, 3, 4 estão na subárvore esquerda e os valores 6, 7, 8, 9 na subárvore direita. Se o valor 5 for removido, colocando-se o valor 4 ou 6 na raiz garante que os valores remanescentes na subárvore esquerda são todos menores que a nova raiz e os da direita maiores. Para qualquer outro valor escolhido para ocupar o lugar do 5 não se tem essa garantia. O valor a ser escolhido é o maior valor da subárvore esquerda ou o menos valor na subárvore direita. Precisamos de uma função para encontrá-los.

Não é complicado. Por exemplo maior valor em uma ABB é o maior valor da subárvore direita, a não ser que ela não exista, em que é o valor da raiz:
```c
   dado_t maior_valor(arv_t *a)
   {
      if (vazia(a)) {
         // temos um problema, esta função não deve ser usada em árvores vazias!
         badabum();
      }
      if (vazia(a->dir)) {
         return a->dado;
      }
      return maior_valor(a->dir);
   }
```

Agora podemos completar a remoção:
```c
   void remove(arv_t *a, dado_t valor)
   {
      if (vazia(a)) {
         return;                     // arvore vazia não tem o dado, não faz nada
      } else if (iguais(valor, a->dado)) {
         if (folha(a)) {  // o caso fácil, transforma a em árvore vazia
            esvazia_no(a);
         } else {  // o caso menos fácil, o nó tem filho(s)!
            dado_t novo_valor;  // este é o novo valor a colocar no nó
            if (!vazio(a->esq)) { // preferência pela esquerda, poderia ser pela direita, ou aleatório
               novo_valor = maior_valor(a->esq);
               remove(a->esq, novo_valor);
            } else {
               novo_valor = menor_valor(a->dir);
               remove(a->dir, novo_valor);
            }
            a->dado = novo_valor;
         }
      } else if (menor(valor, a->dado)) {
         remove(a->esq, valor);      // valor pequeno, remove da esquerda
      } else {
         remove(a->dir, valor);      // valor grande, remove da direita
      }
   }
```

Caso a remoção do dado seja algo mais complicado (por exemplo, se o dado é um ponteiro para uma estrutura complicada, que tem que ser liberada com cuidado), pode-se trocar o dado (novo_valor) pelo dado a remover (colocando o dado a remover mais abaixo na árvore), e continuar com a remoção do mesmo valor de antes:
```c
    ...
    no_t *no_menor = no_com_o_maior_valor(a->esq);
    troca_valores(a, no_menor);
    remove(a->esq, valor); // ou curto-circuita, e chama remove(no_menor, valor)
    ... 
```

Os trechos de código acima estão um pouco diferentes do quefoi visto na aula do dia 8. O código da aula foi esse:
```c
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

typedef int dado_t;
typedef struct no no_t;
struct no {
  dado_t dado;
  no_t *esq;
  no_t *dir;
};

bool vazia(no_t *a) { return a == NULL; }
bool folha(no_t *a) { return a != NULL && a->esq == NULL && a->dir == NULL; }

int compara(dado_t a, dado_t b) { return a-b; }

int maior(int a, int b) {
	return a>b ? a : b;
}

no_t *cria_no(dado_t d, no_t *esq, no_t *dir)
{
  no_t *n = malloc(sizeof(no_t));
  assert(n != NULL);
  n->dado = d;
  n->esq = esq;
  n->dir = dir;
  return n;
}


void imprime(no_t *a, int tab)
{
  if (vazia(a)) return;
  printf("%*s%d\n", tab, "", a->dado);
  imprime(a->esq, tab+4);
  imprime(a->dir, tab+4);
}

dado_t *busca(no_t *a, dado_t d)
{
  if (vazia(a)) return NULL;
  int c = compara(d, a->dado);
  if (c == 0) return &a->dado;
  if (c < 0) return busca(a->esq, d);
  else return busca(a->dir, d);
}

bool arv_insere(no_t **pa, dado_t d)
{
  no_t *a = *pa;
  if (vazia(a)) {
    a = cria_no(d, NULL, NULL);
    *pa = a;
    return true;
  } else {
    int c = compara(d, a->dado);
    if (c == 0) return false;
    if (c < 0) return arv_insere(&(a->esq), d);
    else return arv_insere(&(a->dir), d);
  }
}

bool arv_remove(no_t **pa, dado_t d)
{
  no_t *a = *pa;
  if (vazia(a)) return false;
  else {
    int c = compara(d, a->dado);
    if (c == 0) {
      if (!folha(a)) { printf("compre a versao 2\n"); return false; }
      free(a);
      *pa = NULL;
      return true;
    } else if (c < 0) return arv_remove(&(a->esq), d);
    else return arv_remove(&(a->dir), d);
  }
}

int main()
{
  no_t *a = NULL;

  arv_insere(&a, 19);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 12);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 20);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 5);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 15);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 7);
  printf("\n"); imprime(a, 0);
  arv_insere(&a, 17);
  printf("\n"); imprime(a, 0);
  arv_remove(&a, 5);
  printf("\n"); imprime(a, 0);
  arv_remove(&a, 7);
  printf("\n"); imprime(a, 0);
  arv_remove(&a, 5);
  printf("\n"); imprime(a, 0);
  arv_remove(&a, 17);
  printf("\n"); imprime(a, 0);
}
```
