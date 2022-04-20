## Ponteiros para registros

A sintaxe para manipulação de registros em C, principalmente quando se usa ponteiros, pode não ser considerada muito óbvia.

Considere o tipo abaixo, um registro com 3 campos, e a declaração das variáveis:
```c
  typedef struct {
    int i;
    char *s;
  } reg_t;
  
  reg_t r1 = { 5, "teste" };
  reg_t r2;
  reg_t *p;
  reg_t *q;
  char n[] = "string";
```
Poderíamos ter as seguintes operações sobre essas variáveis:
```c
  p = &r1;  // p agora aponta para r1
  q = &r2;  // q aponta para r2
  r2 = r1;  // copia todo o conteúdo de r1 para r2
  r2 = *p;  // copia todo o conteúdo de r1 para r2
  *q = r1;  // copia todo o conteúdo de r1 para r2
  *q = *p;  // copia todo o conteúdo de r1 para r2

  r1.i = 10; // altera o campo i do registro r1
  (*p).i = 10; // altera o campo i do registro r1
  p->i = 10; // altera o campo i do registro r1
  
  q->s = n; // altera o campo s de r2 (faz ele apontar para o primeiro caractere do vetor n, ele estava apontando para o primeiro caractere da string constante "teste", para onde o campo s de r1 ainda está apontado)
  n[2] = *r1.s; // n (e r2.s) agora valem "stting"
  r2.s[2] = *r1.s; // faz o mesmo que a linha anterior
  q2->s[2] = *q1->s; // faz o mesmo que a linha anterior
  q2->s[2] = q1->s[0]; // faz o mesmo que a linha anterior
  q1->s[2] = q2->s[0]; // não permitido, r1.s está apontando para uma string constante, que não pode ser alterada
```
