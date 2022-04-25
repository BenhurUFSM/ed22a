// Programa exemplo para ler o arquivo de palavras (para implementar algo semelhante ao wordle)
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// tipo de dados para armazenar uma palavra. 
// cada palavra tem 5 letras, e é colocada em 2 versões: com e sem acento.
// os acentos estão codificados em UTF-8, em que um letra acentuada do português é codificada em 2 bytes.
// É usado um vetor de 10 bytes para armazenar a palavra com acento, suportando até 5 letras acentuadas.
// O primeiro byte não usado (se houver) é preenchido com 0.
// Em todos os acentos usados no arquivo, o primeiro byte de uma letra acentuada tem o valor 195.
// Além das duas versões da palavra, tem um boolpara dizer se a palavra já foi escolhida ou ainda não.
typedef struct {
    unsigned char com_acento[10];
    char sem_acento[5];
    bool usada;
} palavra_t;

// o vetor de palavras.
// o onlineGDB não gosta de vetores tão grandes como variável local,
// por isso está sendo declarado como global
palavra_t palavras[7877]; // tem esse tanto de palavras no arquivo; alterar se o arquivo mudar.

// Converte o segundo byte de uma caractere acentuado em UTF-8 para o caractere não acentuado correspondente
// Função BEM meia boca, só funciona para os caracteres selecionados, que são os existentes no arquivo de palavras.
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

// lê a próxima palavra do arquivo; retorna true se sucesso
// No arquivo tem uma palavra acentuada (5 caracteres, codificados em até 10 bytes),
//   opcionalmente seguido por um ponto (para indicar que já foi usada),
//   obrigatoriamente seguido por um fim de linha.
bool le_palavra(FILE *arquivo, palavra_t *palavra)
{
    int c;
    int n = 0;
    int nsa = 0;
    palavra->usada = false;
    for (;;) {
        c = fgetc(arquivo);
	if (c == '\r') continue;
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

// sorteia uma palavra que ainda nao tenha sido usada
palavra_t *sorteia_palavra(int npal, palavra_t palavras[npal])
{
    palavra_t *sorteada;
    do {
	sorteada = &palavras[rand()%npal];
    } while (sorteada->usada);
    return sorteada;
}

// busca uma palavra no vetor de palavras.
// retorna um ponteiro para palavra_t que contém a palavra, ou NULL
palavra_t *busca_palavra(int npal, palavra_t palavras[npal], char buscada[5])
{
    return NULL;
}

int main()
{
    // palavra_t palavras[7877]; // foi declarado como global por uma limitacao do onlinegdm
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
	
    while (true) {
        char s[6];
        printf("digite uma palavra de 5 letras: ");
        scanf("%s", s);
        palavra_t *pal;
        pal = busca_palavra(np, palavras, s);
        if (pal == NULL) {
            printf("palavra '%s' não encontrada\n", s);
        } else {
            printf("Encontrei sua palavra: ");
            imprime_palavra(pal);
        }
    }


    return 0;
}
