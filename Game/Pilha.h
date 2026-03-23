#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
typedef struct pilha Pilha;
Pilha* criaPilha();
int push(Pilha* pilha,int x, int y);
int pop(Pilha* pilha, int* x, int* y);
void imprimePilha(Pilha* pilha);
void liberarPilha(Pilha* pilha);
#endif // PILHA_H_INCLUDED
