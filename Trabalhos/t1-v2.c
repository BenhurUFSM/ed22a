// ED 2022 SI2/CC2
// Segunda versão do jogo wordle
// Visto em aula dia 2mai
//
// Implementado em abordagem descendente (top-down)
// Com um "dicionário" escondendo a implementação do conjunto de palavras
//
// Algumas funções não estão implementadas (exceto para que compile)
// Implemente o que falta para que o jogo funcione corretamente.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// -----------------------------------------------------------------------------------------
// tipo de dados para uma palavra
typedef struct {
    unsigned char com_acento[10];
    char sem_acento[5];
    bool usada;
} palavra_t;



// -----------------------------------------------------------------------------------------
// tipo de dados para o dicionário (está oculto e a implementação não funciona muito)
typedef struct dicionario dicionario_t;

dicionario_t *dicionario_cria(char *nome_arquivo)
{
  return NULL;
}
void dicionario_destroi(dicionario_t *dic)
{
}
char *dicionario_nome_arquivo(dicionario_t *dic)
{
  return "oi";
}
int dicionario_numero_de_palavras(dicionario_t *dic)
{
  return 1;
}
palavra_t p[] = {{ "teste", "teste", false }, { "terés", "teres" }};
palavra_t *dicionario_palavra_na_posicao(dicionario_t *dic, int pos)
{
  return &p[pos];
}



// -----------------------------------------------------------------------------------------
// tipo de dados para as dicas sobre uma letra
typedef enum {inexistente, trocado, certo} classe_letra_t;



// -----------------------------------------------------------------------------------------
// funções de E/S na tela

// sequencias ANSI para selecionar cor das letras
// ESC[ 38;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB foreground color
// ESC[ 48;2;⟨r⟩;⟨g⟩;⟨b⟩ m Select RGB background color
void cor_de_fundo(int vm, int vd, int az)
{
    printf("%c[48;2;%d;%d;%dm", 27, vm, vd, az);
}
void cor_da_letra(int vm, int vd, int az)
{
    printf("%c[38;2;%d;%d;%dm", 27, vm, vd, az);
}
void cor_default(void)
{
    printf("%c[m", 27);
}

void escreve_palavra(FILE *arq, palavra_t *p)
{
  for (int i = 0; i < 10; i++) {
    if (p->com_acento[i] == '\0') break;
    fprintf(arq, "%c", p->com_acento[i]);
  }
  if (p->usada) fprintf(arq, ".");
  fprintf(arq, "\n");
}


void desenha_palavra(palavra_t *chute, classe_letra_t cl[5])
{
  int jj = 0;
  for (int l=0; l<3; l++) {
    for (int j=0; j<5; j++) {
      if (cl[j] == inexistente)  cor_de_fundo(90,90,90);
      else if (cl[j] == trocado) cor_de_fundo(200,130,0);
      else                       cor_de_fundo(0,200,0);
      if (l==0 || l == 2) {
        printf("     ");
      } else {
        printf("  ");
        printf("%c", chute->com_acento[jj]);
        if (chute->com_acento[jj] == 195) {
          printf("%c", chute->com_acento[++jj]);
        }
        jj++;
        printf("  ");
      }
      if (j<4) {
        cor_de_fundo(30,30,30);
        printf(" ");
      }
    }
    cor_default();
    printf("\n");
  }
  printf("\n");
}


palavra_t *le_chute(dicionario_t *dic)
{
  return dicionario_palavra_na_posicao(dic, 1);
}

bool quer_jogar_de_novo(void)
{
  return false;
}



// -----------------------------------------------------------------------------------------
// esta função tá sobrando (deveria ter sido incluida na interface do dicionário!)

void atualiza_arquivo(dicionario_t *palavras)
{
  FILE *arq;
  char *nome_original = dicionario_nome_arquivo(palavras);
  char nome[strlen(nome_original)+5];
  strcpy(nome, nome_original);
  strcat(nome, ".tmp");
  arq = fopen(nome, "w");
  if (arq == NULL) {
    fprintf(stderr, "Nao consegui criar arquivo\n");
    exit(1);
  }
  for (int i = 0; i < dicionario_numero_de_palavras(palavras); i++) {
    palavra_t *palavra = dicionario_palavra_na_posicao(palavras, i);
    escreve_palavra(arq, palavra);
  }
  fclose(arq);
  remove(nome);
  rename(nome, nome_original);
}



// -----------------------------------------------------------------------------------------
// funções que implementam uma jogada

palavra_t *sorteio(dicionario_t *dic)
{
  return dicionario_palavra_na_posicao(dic, 0);
}

bool classifica_chute(palavra_t *sorteada, palavra_t *chute, 
                      classe_letra_t cl[5])
{
  int i;
  int certos = 0;
  for (i=0; i<5; i++) cl[i] = inexistente;
  for (i=0; i<5; i++) {
    if (sorteada->sem_acento[i] == chute->sem_acento[i]) {
      cl[i] = certo;
      certos++;
    }
  }
  for (i=0; i<5; i++) {
    if (cl[i] != certo) {
      for (int j=0; j<5; j++) {
        if (sorteada->sem_acento[i] == chute->sem_acento[j]) {
          if (cl[j] == inexistente) {
            cl[j] = trocado;
            break;
          }
        }
      }
    }
  }
  return certos == 5;
}


bool joga(dicionario_t *palavras)
{
  bool acertou = false;
  palavra_t *sorteada = sorteio(palavras);
  sorteada->usada = true;
  atualiza_arquivo(palavras);
  for (int jogada=0; jogada < 6; jogada++) {
    palavra_t *chute = le_chute(palavras);
    if (chute == NULL) break; // amarelou!
    classe_letra_t classificacao[5];
    acertou = classifica_chute(sorteada, chute, classificacao);
    desenha_palavra(chute, classificacao);
    if (acertou) break;
  }
  return acertou;
}



// -----------------------------------------------------------------------------------------
// função principal - implementam o laço principal do programa

int main()
{
  dicionario_t *palavras;
  palavras = dicionario_cria("palavras_de_5_letras");
  
  do {
    joga(palavras);
  } while (quer_jogar_de_novo());
  
  dicionario_destroi(palavras);
}
