# ed22a - Estruturas de Dados

ELC1066 DLSC/CT/UFSM\
turmas SI2 e CC2, primeiro semestre 2022\
professor: Benhur Stein 
([benhur+ed22a@inf.ufsm.br](mailto:benhur%2bed22a@inf.ufsm.br))\
segundas e quartas, 10h30\
sala 334, prédio 7 (principal do CT)

## Desenvolvimento da disciplina

Os canais de comunicação entre o professor e os alunos são as aulas presenciais, esta página (<https://github.com/BenhurUFSM/ed22a>), e-mail (ver acima). Caso queira conversar fora desses canais, manda um mail que marcamos.

O e-mail pode ser usado para o envio de perguntas, exercícios, reclamações, sugestões, críticas e o que mais for, durante todo o período em que durar a disciplina.

Esta página concentrará os assuntos vistos em aula, a descrição de exercícios e trabalhos, avaliações, etc. Ela estará sendo aumentada/atualizada durante todo o semestre. Ela é o canal mais oficial de informações sobre a disciplina.

A disciplina será desenvolvida de uma forma bastante prática, os alunos devem desenvolver pequenos programas de computador, a serem enviados para o professor em datas definidas. 
Esses programas serão revisados e comentados pelo professor, individualmente ou de forma coletiva. 
Os programas podem ser corrigidos e reenviados quantas vezes o aluno quiser, para resolver dúvidas ou pedir sugestões.
A avaliação será feita no final do semestre, quando cada aluno deve entregar a versão final de um conjunto dos trabalhos desenvolvidos durante o semestre e uma auto-avaliação justificada. Esse material final será usado pelo professor para gerar a nota final de cada aluno.
Para quem precisar, o exame será uma prova escrita.

##  Aulas

Os assuntos vistos em aula serão listados aqui.

|    N |   data | assunto
| ---: | :----: | :--------
|    1 | 11abr  | introdução / revisão / pt1 do [primeiro trabalho de revisão](Trabalhos/t1.md)
|    2 | 13abr  | revisão, cont (vimos um pedaço da pt1)
|    3 | 18abr  | revisão, cont (vimos mais um pedaço da pt1 e 2; o programa feito em aula tá no github)
|    4 | 20abr  | revisão, cont (falamos sobre [ponteiros, em especial para structs](Assuntos/ponteiros-para-registros.md); função para sortear uma palavra do wordle)
|    5 | 25abr  | revisão, cont
|    6 | 27abr  | revisão, cont (falamos sobre [alocação dinâmica](Assuntos/alocacao-dinamica.md) de memória, e um pouco sobre [tipos abstratos de dados](Assuntos/tad.md))
|    7 | 2mai  | revisão, fim (falamos sobre a implementação do t1 -- ver t1-v2.c)
|    8 | 4mai  | [Implementação de TAD em C](Assuntos/tad.md)
|    9 | 9mai  | [Listas](Assuntos/listas.md)

<!--
|    1 |  19mai | introdução
|    2 |  24mai | revisão de C
|    3 |  26mai | [revisão de C (cont)](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/03.md)
|    4 |  31mai | resolução dos exercícios da 03 (a [página](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/03.md) foi alterada).
|    5 |   2jun | cont. da revisão dos exercícios; tipos abstratos de dados ([TAD](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/05.md))
|    6 |   7jun | exemplo de implementação em C do TAD [data](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/06.md)
|    - |   9jun | jacaré (mas fiz uma [pagininha](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/t1.md) sobre o t1)
|    7 |  14jun | [Introdução às estruturas de dados](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/07.md)
|    8 |  16jun | [lista encadeada](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/08.md)
|    9 |  21jun | [lista encadeada, cont](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/09.md)
|   10 |  23jun | [pilha, fila, deque](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/10.md)
|   11 |  28jun | [dicionário, tabela *hash*](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/11.md)
|   12 |  30jun | [matriz](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/12.md)
|   13 |   5jul | [árvore](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/13.md)
|   14 |   7jul | [árvore binária de busca](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/14.md)
|   15 |  12jul | [árvore AVL](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/15.md)
|   16 |  14jul | [árvore AVL, cont](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/15.md)
|   17 |  19jul | [grafos](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/17.md)
|   18 |  21jul | [grafos, cont](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/17.md)
|   19 |  26jul | [grafos, cont](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/17.md)
|   20 |  28jul | [grafos, cont; fila de prioridade](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/20.md)
-->

## Exercícios e trabalhos

|     N |    prazo | assunto
| ----: | -------: | :-----------
|   t1a | trazer dúvidas para a aula de 13abr | ler o arquivo de palavras
|   t1b | trazer dúvidas para a aula de 18abr | t1a+suporte a palavras usadas
|   t1c | trazer dúvidas para a aula de 20abr | sorteio de uma palavra
|   t1d |          | busca de uma palavra (para encontrar a palavra digitada pelo jogador)
|   t1  | 1mai     | [wordle](Trabalhos/t1.md)
|   t2  | 3mai     | Implemente o que falta em [wordle, v2](Trabalhos/t1-v2.c)

<!--
|    t1 |  9jun10h | ver [aula 3](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/03.md)
|    t2 | 17jun10h | ver [aula 6](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/06.md) - exemplo de implementação nos [complementos](https://github.com/BenhurUFSM/ed21a/blob/main/Complementos)
|    t3 | ~~4ago~~ 9ago | ver [aula 11](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/11.md) (agora com a pt3)
|    t4 |    31ago | [trabalho final](https://github.com/BenhurUFSM/ed21a/blob/main/Assuntos/t4.md)
-->

## Ementa

Ver [aqui](https://www.ufsm.br/ementario/disciplinas/elc1066/).

## Bibliografia

Os livros abaixo estão disponíveis no [minha biblioteca](https://www.ufsm.br/orgaos-suplementares/biblioteca/e-books-2/), acessível aos alunos da UFSM.

Estruturas de Dados e Seus Algoritmos - Jayme Szwarcfiter e Lilian Markenzon

Estruturas de Dados - Nina Edelweiss e Renata Galante

Estruturas de Dados em C, Uma Abordagem Didática - Sílvio Pereira


<!--
## Material Auxiliar
-->

## Avaliações etc

Veja a [planilha](https://docs.google.com/spreadsheets/d/1mR_EDFlGTIz5pMNLANQukv4nFyMJAL_hqspNuCAxSRQ/edit?usp=sharing)

