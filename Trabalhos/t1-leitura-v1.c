#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned char com_acento[10];
    char sem_acento[5];
    bool usada;
} palavra_t;

char tira_acento(unsigned char c)
{
    unsigned char ac[] = "áâãéêíóôõúç";
    char sem_acento[]  = "aaaeeiooouc";
    for (int i=0; ac[i] != '\0'; i++) {
        if (c == ac[i]) return sem_acento[i/2];
    }
    printf("Não sei converter o caractere %d (%c%c)\n", c, 195, c);
    return c;
}

bool le_palavra(FILE *arquivo, palavra_t *palavra)
{
    int c;
    int n = 0;
    int nsa = 0;
    palavra->usada = false;
    for (;;) {
        c = fgetc(arquivo);
        if (c == EOF) return false;
        if (c == '\n') {
            break;
        }
        if (c == '.') {
            palavra->usada = true;
            continue;
        }
        if (n >= 10) {
            return false;
        }
        palavra->com_acento[n] = c;
        n++;
        if (c >= 'a' && c <= 'z') {
            palavra->sem_acento[nsa++] = c;
        } else {
            if (c != 195) {
                palavra->sem_acento[nsa++] = tira_acento(c);
            }
        }
    }
    if (n < 10) {
        palavra->com_acento[n] = '\0';
    }
    return true;
}

void imprime_palavra(palavra_t *palavra)
{
    for (int i=0; i<10; i++) {
        if (palavra->com_acento[i] == '\0') break;
        putchar(palavra->com_acento[i]);
    }
    putchar('=');
    for (int i=0; i<5; i++) {
        putchar(palavra->sem_acento[i]);
    }
}

/*
... grava_palavras(...)
{
    
}
*/

int main()
{
    palavra_t palavras[7877];
    FILE *a;
    a = fopen("palavras-de-5-letras", "r");
    if (a == NULL) {
        printf("Não consegui abrir o arquivo\n");
        return 1;
    }
    int np=0;
    while (le_palavra(a, &palavras[np])) {
        np++;
    }
    if (np != 7877) {
        printf("problema na contagem das palavras\n");
        return 2;
    }
    for (int i = 0; i<np; i++) {
        imprime_palavra(&palavras[i]);
        putchar(' ');
    }
    
    // vetor de le_palavras
    // le o vetor
    // mostra algumas palavras lidas, para ver se está funcionando

    return 0;
}
