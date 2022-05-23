## Pilhas, filas, deques

Essas três estruturas são estruturas lineares de armazenamento de dados.
São listas, mantém um conjunto de dados e a ordem entre eles.
A diferença em relação às listas é que as operações de inserção e remoção são mais limitadas, somente são permitidas nas extremidades (início ou final) da lista. As operações que são permitidas em quais extremidades definem o tipo de estrutura.

Essas estruturas têm um uso bastante comum em computação. Veja exemplos nos livros da referência.

### Pilha

Permite inserção e remoção somente em uma extremidade, que é chamaa de topo da pilha.
Por vezes, a operação de inserção é chamada de "empilhar" (em inglês, é comum chamar de "push"), e a de remoção de "desempilhar" ("pop").
não é incomum ter-se a operação de consultar o dado que está no topo da pilha, sem removê-lo.
Geralmente tem uma operação que diz se a pilha está vazia (e cheia, se houver limite no número de elementos que ela pode conter).

Uma pilha as vezes é chamada de LIFO (*last in first out*), porque a primeira operação de remoção é sempre do último elemento a ser inserido.

Pode ser implementada com bom desempenho com qualquer tipo de implementação de lista, porque todas têm pelo menos uma extremidade em que a inserção e a remoção é o ponto de melhor desempenho. Em uma implementação contígua com vetor, o topo da pilha seria o final do vetor; em uma implementação com lista encadeada, o topo da pilha seria o início da lista.

### Fila

Permite a inserção em uma extremidade (o final da fila) e a remoção na outra (o início da fila). Os dados saem da fila na mesma ordem em que entram.

É por vezes chamada de FIFO (*first in first out*).

A implementação de uma fila com alocação contígua gralmente só é feita com organização circular, ou o desempenho de uma das operações terá um desempenho bem pior que a outra. No caso de implementação com lista simplesmente encadeada, em geral se usa uma em que se mantém um ponteiro para o último elemento da lista.

### Deque

O nome vem do inglês (*double ended queue*), e é uma fila dupla, que permite inserção e remoção em ambas extremidades.
Geralmente é implementada usando lista duplamente encadeada ou alocação contígua com alocação circular (principalmente nos casos em que se tem uma limitação forte no número máximo de elementos).

#### Exemplo

Uma função para inverter os elementos de uma pilha usando uma lista auxiliar:
```c
   void pilha_inverte(pilha_t *p)
   {
   }
```
