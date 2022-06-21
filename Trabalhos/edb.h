#ifndef _EDB_H_
#define _EDB_H_

// edb - estrutura de dados de busca

// permite a inclusão de dados associados a chaves, e a busca e remoção de
//   dados a partir da chave

#include <stdbool.h>

// definição de tipos auxiliares (altere para os tipos necessários)

typedef char *chave_t;
typedef struct valor valor_t;
struct valor {
  char nome[16];
  int nota1;
  int nota2;
};

// função para comparar uma chave e um valor -- retorna:
// =0 - se chave corresponde ao valor
// <0 - se chave corresponde a valor que deve estar antes do valor 
// >0 - se chave corresponde a valor que deve estar depois do valor 
int compara_chave_valor(chave_t chave, valor_t valor);

// tipo principal (opaco)
typedef struct edb edb_t;

// operações do TAD (interface pública)

edb_t *edb_cria(void);
void edb_destroi(edb_t *edb);

// insere o valor associado a chave
void edb_insere(edb_t *edb, chave_t chave, valor_t valor);
// remove o valor associado a chave
void edb_remove(edb_t *edb, chave_t chave);
// retorna (por ref) o valor associado a chave (e true) ou nao (e false)
bool edb_busca(edb_t *edb, chave_t chave, valor_t *pvalor);

#endif // _EDB_H_
