#include "edb.h"
#include <stdio.h>
#include <string.h>

// programa de teste de edb

int compara_chave_valor(chave_t c, valor_t v)
{
  return strcmp(c, v.nome);
}

int main()
{
  edb_t *cad;

  cad = edb_cria();

  for(;;) {
    char nome[16];
    printf("Digite um nome (ou fim) ");
    scanf("%s", nome);
    if (strcmp(nome, "fim") == 0) {
      break;
    }
    valor_t v;
    if (!edb_busca(cad,nome, &v)) {
      int n1, n2;
      printf("Digite as 2 notas ");
      scanf("%d%d", &n1, &n2);
      strcpy(v.nome, nome);
      v.nota1 = n1;
      v.nota2 = n2;
      edb_insere(cad, nome, v);
    } else {
      printf("A média é %.2f\n", v.nota1/2.0 + v.nota2/2.0);
    }
  }
  edb_destroi(cad);
}


