// edb - estrutura de dados de busca

// implementação simplória

#include "edb.h"
#include <stdlib.h>

struct edb {
  valor_t valores[10];
  int n_valores;
};

// operações do TAD (interface pública)

edb_t *edb_cria(void)
{
  edb_t *edb = malloc(sizeof(edb_t));
  if (edb != NULL) {
    edb->n_valores = 0;
  }
  return edb;
}

void edb_destroi(edb_t *edb)
{
  free(edb);
}

static int acha(edb_t *edb, chave_t chave)
{
  for (int i=0; i < edb->n_valores; i++) {
    if (compara_chave_valor(chave, edb->valores[i]) == 0) {
      return i;
    }
  }
  return -1;
}

void edb_insere(edb_t *edb, chave_t chave, valor_t valor)
{
  int i = acha(edb, chave);
  if (i != -1) {
    edb->valores[i] = valor;
    return;
  }
  if (edb->n_valores < 10) {
    edb->valores[edb->n_valores++] = valor;
  }
}

void edb_remove(edb_t *edb, chave_t chave)
{
  int i = acha(edb, chave);
  if (i == -1) {
    return;
  }
  edb->n_valores--;
  if (i != edb->n_valores) {
    edb->valores[i] = edb->valores[edb->n_valores];
  }
}

bool edb_busca(edb_t *edb, chave_t chave, valor_t *pvalor)
{
  int i = acha(edb, chave);
  if (i == -1) {
    return false;
  }
  *pvalor = edb->valores[i];
  return true;
}

