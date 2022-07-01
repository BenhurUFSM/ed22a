#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

// os percursos visitam os nós, esta é a função chamada.
void visita(int no)
{
  printf("visita ao nó %d\n", no);
}

/// uma fila de inteiros (para percursos em largura)
typedef struct fila {
  int v[100];
  int n;
  int p;
  int u;
} *fila;

fila fila_cria(void)
{
  fila f = malloc(sizeof(*f));
  assert(f != NULL);
  f->n = f->p = f->u = 0;
  return f;
}

bool fila_vazia(fila f)
{
  assert(f != NULL);
  return f->n == 0;
}

void fila_destroi(fila f)
{
  assert(f != NULL);
  free(f);
}

void fila_insere(fila f, int d)
{
  assert(f != NULL);
  assert(f->n < 100);
  f->v[f->u] = d;
  f->u = (f->u + 1) % 100;
  f->n++;
}

int fila_remove(fila f)
{
  assert(!fila_vazia(f));
  int d = f->v[f->p];
  f->p = (f->p + 1) % 100;
  f->n--;
  return d;
}

void fila_esvazia(fila f)
{
  while (!fila_vazia(f)) {
    fila_remove(f);
  }
}

void fila_imprime(fila f)
{
  assert(f != NULL);
  int i = f->p;
  putchar('[');
  for (int ni=0; ni<f->n; ni++) {
    if (ni != 0) putchar(' ');
    printf("%d", f->v[i]);
    i = (i+1) % 100;
  }
  putchar(']');
}

  
// percurso em profundidade em um grafo implementado como matriz de adjacências
void percorre_prof_mat(int n_nos, bool grafo[n_nos][n_nos], bool visitado[n_nos], int no)
{
  if (visitado[no]) return;
  visitado[no] = true;
  visita(no);
  for (int adj=0; adj<n_nos; adj++) {
    if (grafo[no][adj]) {
      percorre_prof_mat(n_nos, grafo, visitado, adj);
    }
  }
}

void percurso_prof_mat(int n_nos, bool grafo[n_nos][n_nos])
{
  bool visitado[n_nos];
  for (int no = 0; no < n_nos; no++) visitado[no] = false;
  for (int no = 0; no < n_nos; no++) {
    if (!visitado[no]) {
      percorre_prof_mat(n_nos, grafo, visitado, no);
    }
  }
}

// percurso em largura em um grafo implementado como matriz de adjacências
void percorre_larg_mat(int n_nos, bool grafo[n_nos][n_nos], bool visitado[n_nos], int no)
{
  if (visitado[no]) return;
  fila f = fila_cria();
  fila_insere(f, no);
  while (!fila_vazia(f)) {
    no = fila_remove(f);
    if (visitado[no]) continue;
    visitado[no] = true;
    visita(no);
    for (int adj=0; adj<n_nos; adj++) {
      if (grafo[no][adj]) {
        if (!visitado[adj])
          fila_insere(f, adj);
      }
    }
  }
  fila_destroi(f);
}

void percurso_larg_mat(int n_nos, bool grafo[n_nos][n_nos])
{
  bool visitado[n_nos];
  for (int no = 0; no < n_nos; no++) visitado[no] = false;
  for (int no = 0; no < n_nos; no++) {
    if (!visitado[no]) {
      percorre_larg_mat(n_nos, grafo, visitado, no);
    }
  }
}

// para implementar grafos com listas de adjacências, precisa uma estrutura para os itens da lista
typedef struct item_t item_t;
struct item_t {
  int no;
  item_t *prox;
};

// percurso em profundidade em grafo implementado com lista de adjacências
void percorre_prof_lista(int n_nos, item_t *grafo[n_nos], bool visitado[n_nos], int no)
{
  if (visitado[no]) return;
  visitado[no] = true;
  visita(no);
  for (item_t *item=grafo[no]; item != NULL; item =  item->prox) {
    int adj = item->no;
    percorre_prof_lista(n_nos, grafo, visitado, adj);
  }
}

void percurso_prof_lista(int n_nos, item_t *grafo[n_nos])
{
  bool visitado[n_nos];
  for (int no = 0; no < n_nos; no++) visitado[no] = false;
  for (int no = 0; no < n_nos; no++) {
    if (!visitado[no]) {
      percorre_prof_lista(n_nos, grafo, visitado, no);
    }
  }
}


// percurso em largura em um grafo implementado como lista de adjacências
void percorre_larg_lista(int n_nos, item_t *grafo[n_nos], bool visitado[n_nos], int no)
{
  if (visitado[no]) return;
  fila f;
  f = fila_cria();
  fila_insere(f, no);
  while (!fila_vazia(f)) {
    no = fila_remove(f);
    if (!visitado[no]) {
      visitado[no] = true;
      visita(no);
      for (item_t *item=grafo[no]; item != NULL; item =  item->prox) {
        int adj = item->no;
        if (!visitado[adj]) {
          fila_insere(f, adj);
        }
      }
    }
  }
}

void percurso_larg_lista(int n_nos, item_t *grafo[n_nos])
{
  bool visitado[n_nos];
  for (int no = 0; no < n_nos; no++) visitado[no] = false;
  for (int no = 0; no < n_nos; no++) {
    if (!visitado[no]) {
      percorre_larg_lista(n_nos, grafo, visitado, no);
    }
  }
}



// busca de ciclos em um grafo implementado como matriz de adjacências

typedef enum { nao_visitado, em_visita, ja_visitado} marca_t;

bool acha_ciclo(int n_nos, bool grafo[n_nos][n_nos], 
                marca_t marca[n_nos], int no)
{
  if (marca[no] == em_visita) return true;
  if (marca[no] == ja_visitado) return false;
  marca[no] = em_visita;
  for (int adj = 0; adj < n_nos; adj++) {
    if (grafo[no][adj]) {
      if (acha_ciclo(n_nos, grafo, marca, adj)) return true;
    }
  }
  marca[no] = ja_visitado;
  return false;
}

bool aciclico(int n_nos, bool grafo[n_nos][n_nos])
{
  marca_t marca[n_nos];
  for (int no = 0; no < n_nos; no++) marca[no] = nao_visitado;  // todos marcados como não visitados
  for (int no = 0; no < n_nos; no++) {
    if (marca[no] == nao_visitado) {
      if (acha_ciclo(n_nos, grafo, marca, no)) return false;
    }
  }
  return true;
}

bool aciclico_grau_entrada(int n_nos, bool grafo[n_nos][n_nos])
{
  // inicializa um vetor com o grau de entrada dos nós
  int ge[n_nos];
  for (int no=0; no<n_nos; no++) {
    ge[no] = 0;
    // incrementa o GE do nó para cada aresta que chega nele
    for (int no2=0; no2<n_nos; no2++) {
      if (grafo[no2][no]) ge[no]++;
    }
  }
  // inicializa uma fila com todos os nós que têm GE 0
  fila f = fila_cria();
  for (int no=0; no<n_nos; no++) {
    if (ge[no] == 0) {
      fila_insere(f, no);
    }
  }
  int analisados = 0;  // conta o número de nós analisados (que têm GE 0)
  while (!fila_vazia(f)) {
    int no = fila_remove(f);
    // decrementa o GE de cada nó destino de uma aresta que parte do nó analisado
    // insere na fila se o GE ficou 0
    for (int no2=0; no2<n_nos; no2++) {
      if (grafo[no][no2]) {
        ge[no2]--;
        if (ge[no2] == 0) fila_insere(f, no2);
      }
    }
    analisados++;
  }
  fila_destroi(f);
  // se todos os nós foram analisados, o grafo é acíclico.
  return analisados == n_nos;
}

fila ordem_topologica(int n_nos, bool grafo[n_nos][n_nos])
{
  // inicializa um vetor com o grau de entrada dos nós
  int ge[n_nos];
  for (int no=0; no<n_nos; no++) {
    ge[no] = 0;
    // incrementa o GE do nó para cada aresta que chega nele
    for (int no2=0; no2<n_nos; no2++) {
      if (grafo[no2][no]) ge[no]++;
    }
  }
  // inicializa uma fila com todos os nós que têm GE 0
  fila f = fila_cria();
  for (int no=0; no<n_nos; no++) {
    if (ge[no] == 0) {
      fila_insere(f, no);
    }
  }
  // inicializa uma fila que conterá os nós em ordem topológica
  fila ordem = fila_cria();
  int ordenados = 0;  // conta o número de nós na fila ordem
  while (!fila_vazia(f)) {
    int no = fila_remove(f);
    // decrementa o GE de cada nó destino de uma aresta que parte do nó analisado
    // insere na fila se o GE ficou 0
    for (int no2=0; no2<n_nos; no2++) {
      if (grafo[no][no2]) {
        ge[no2]--;
        if (ge[no2] == 0) fila_insere(f, no2);
      }
    }
    fila_insere(ordem, no);
    ordenados++;
  }
  fila_destroi(f);
  if (ordenados != n_nos) fila_esvazia(ordem);
  return ordem;
}

// funções de teste

void testa_grafo_mat(void)
{
  bool grafo[5][5] = {
     ///*
     { 0, 1, 1, 0, 0 },
     { 0, 0, 0, 0, 1 },
     { 0, 1, 0, 0, 0 },
     { 0, 1, 1, 0, 0 },
     { 0, 0, 0, 0, 0 },
     //*/
     /*
     { 0, 1, 1, 0, 0 },
     { 1, 0, 0, 0, 1 },
     { 0, 1, 0, 0, 0 },
     { 0, 1, 1, 0, 0 },
     { 0, 1, 1, 1, 0 },
     */
  };
  printf("teste do grafo com matriz\n");
  printf("percurso em profundidade\n");
  percurso_prof_mat(5, grafo);
  printf("percurso em largura\n");
  percurso_larg_mat(5, grafo);
  if (aciclico(5, grafo)) {
    printf("o grafo é acíclico\n");
  } else {
    printf("o grafo contém ciclos\n");
  }
  fila topo = ordem_topologica(5, grafo);
  printf("ordem topológica: ");
  fila_imprime(topo);
  putchar('\n');
  fila_destroi(topo);
}

item_t *cria_item(int no, item_t *prox)
{
  item_t *it = malloc(sizeof(*it));
  assert(it != NULL);
  it->no = no;
  it->prox = prox;
  return it;
}

void testa_grafo_lista(void)
{
  item_t *grafo[5];
  grafo[0] = cria_item(1, cria_item(2, NULL));
  grafo[1] = cria_item(0, cria_item(4, NULL));
  grafo[2] = cria_item(1, NULL);
  grafo[3] = cria_item(1, cria_item(2, NULL));
  grafo[4] = cria_item(1, cria_item(2, cria_item(3, NULL)));
  printf("teste do grafo com listas\n");
  printf("percurso em profundidade\n");
  percurso_prof_lista(5, grafo);
  printf("percurso em largura\n");
  percurso_larg_lista(5, grafo);
}

void testa_fila(void)
{
  fila f = fila_cria();
  fila_insere(f, 1);
  fila_insere(f, 2);
  fila_insere(f, 3);
  printf("numeros em ordem:\n");
  while (!fila_vazia(f)) {
    printf("%d\n", fila_remove(f));
  }
  fila_destroi(f);
}

int main()
{
  testa_fila();
  testa_grafo_mat();
  testa_grafo_lista();
}
