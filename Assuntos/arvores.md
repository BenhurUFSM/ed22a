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

Uma forma comum de implementação de uma árvore é como um ponteiro para um nó, e esse nó contém o valor associado ao nó e dois ponteiros para os nós raiz das árvores filhas. Uma árvore vazia é implementada como um ponteiro nulo.

```c
   typedef struct arv arv_t;
   struct arv {
     dado_t val;
     arv_t *esq;
     arv_t *dir;
   };
```

Grande parte dos algoritmos que operam sobre árvores são mais facilmente implementados em forma recursiva.
Por exemplo, para calcular quantos nós tem uma árvore, pode-se usar uma definição recursiva:
   - uma árvore vazia tem 0 nós
   - uma árvore não vazia tem um nó a mais que a soma dos nós de suas duas subárvores.
Em código:
```c
   int num_nos(arv_t *a)
   {
      if (a == NULL) return 0;
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
      if (a == NULL) return -1;
      return 1 + maior(altura(a->esq), altura(a->dir));
   }
```

#### Exercícios

1. Faça uma função que recebe uma árvore e retorna quantos nós folha ela tem
2. Faça uma função que recebe uma árvore e retorna quantos nós não folha ela tem
3. Faça uma função que recebe uma árvore e um valor e retorna um booleano que diz se a árvore contém ou não um nó com esse valor. Use a função auxiliar `bool valores_iguais(dado_t, dado_t)` para comparar dois valores.
4. Faça uma função que recebe uma árvore e um valor e retorna o nível nessa árvore que está o nó que contém esse valor, ou -1 se o valor não estiver em nenhum nó da árvore. A raiz de uma árvore está no nível 0, os filhos da raiz no nível 1 etc.
5. Faça uma função que recebe uma árvore e retorna o "fator de equilíbrio" do nó raiz dessa árvore. O "fator de equilíbrio" a ser considerado é a diferença entre a altura da subárvore esquerda e a da direita.

Para testar essas funções, pode fazer uma árvore que armazena dados inteiros, e uma função que aloca um nó e retorna um ponteiro para ele, recebendo como argumentos o valor do nó e os ponteiros para os dois filhos. Uma árvore com a raiz com valor 1, o filho esquerdo com valor 2 e o direito com o valor 3 poderia ser criada assim:
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



<!--
Percurso em uma árvore: forma de caminhamento entre os nós da árvore que visita todos os nós. Os principais tipos de percurso são:
- percurso em largura: visita os nós, a partir da raiz, um nível por vez (primeiro visita a raiz, depois todos seus filhos, depois todos seus netos etc);
- percurso em profundidade: visita os nós, percorrendo um ramo até seu final antes de seguir pelo ramo seguinte. Tem três percursos em profundidade principais:
   - percurso em pré-ordem: visita primeiro um nó, antes de realizar um percurso em pré-ordem iniciando em cada um de seus filhos;
   - percurso em pós-ordem: percorre em pós-ordem cada um dos filhos de um nó antes de visitar o nó;
   - percurso em-ordem (somente em árvores binárias, de grau dois): percorre em-ordem a subárvore esquerda, então visita o nó, e depois percorre em-ordem a subárvore direita.

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
O percurso em largura é tipicamente implementado com uma fila:
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
Implementação de árvores

Todo nó de uma árvore é um nó raiz da subárvore que tem esse nó como raiz, e pode ter um número qualquer de nós filhos. Uma forma de se implementar essa estrutura é tendo uma lista associada a cada nó, contendo os nós filhos desse nó.
Uma forma um pouco mais econômica de se implementar é mantendo dois ponteiros para cada nó, um que aponta para seu primeiro filho e outro que aponta para seu irmão.

Como o nó raiz de uma árvore se confunde com o conceito da árvore, geralmente se representa uma árvore como um ponteiro para o nó que contém a raiz dessa árvore, não sendo comum ter um outro tipo de dados para implementar um descritor da árvore.

No caso de árvores de grau conhecido e pequeno (em especial árvores binárias, de grau 2), é comum implementar um nó da árvore com os tantos ponteiros para os nós raizes das subárvores.
Para árvores binárias, um nó poderia ser uma `struct` em C, como abaixo:
```c
   typedef struct no no;
   struct no {
     dado_t dado;
     no *esq;  // ponteiro para a raiz da subárvore esquerda
     no *dir;  // ponteiro para a raiz da subárvore direita
   }
```

Tem duas formas comuns de se agrupar os nós para representar uma árvore, uma em que a árvore vazia é representada por um ponteiro nulo e outra em que uma árvore vazia é representada como um nó vazio (que não tem filhos). A vantagem do primeiro caso é a economia de memória (só são alocados nós que efetivamente contém dados. A segunda forma de implementar tem vantagem na implementação de diversos algoritmos, que tem menos casos especiais para tratar ponteiros nulos, mas usa mais memória (uma árvore binária com *n* nós não nulos contém *n+1* nós nulos). 

O percurso em pré-ordem de uma árvore binária com o nó definido como acima, em C, poderia ser:
```c
   void pre_ordem(no *a)
   {
      if (!arvore_vazia(a)) {
         visita(a->dado);
         pre_ordem(a->esq);
         pre_ordem(a->dir);
      }
   }
```
O teste de árvore vazia seria implementado como `a == NULL` no caso de uma árvore vazia ser implementada como ponteiro nulo.
Para o caso de uma árvore vazia ser implementada como um nó nulo, o teste de árvore vazia poderia ser implementada como `a->esq == NULL`   (um nó nulo não tem nenhum filho; os nós não nulos têm filhos, mesmo que sejam nós nulos; um nó folha tem dois nós nulos como filhos).
-->
