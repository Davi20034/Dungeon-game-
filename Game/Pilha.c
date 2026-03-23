#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int x;
    int y;
    struct cel* proximo;
} Celula;

struct pilha {
    Celula* topo;
    int tamanho;
};

Pilha* criaPilha() {
    Pilha* p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

int push(Pilha* pilha, int x, int y) {
    Celula* nova = (Celula*)malloc(sizeof(Celula));
    if (!nova) return 0;

    nova->x = x;
    nova->y = y;
    nova->proximo = pilha->topo;
    pilha->topo = nova;
    pilha->tamanho += 1;
    return 1;
}

int pop(Pilha* pilha, int* x, int* y) {
    if (pilha->tamanho < 1)
        return 0;

    Celula* cel_topo = pilha->topo;
    *x = cel_topo->x;
    *y = cel_topo->y;

    pilha->topo = cel_topo->proximo;
    pilha->tamanho--;
    free(cel_topo);
    return 1;
}

void imprimePilha(Pilha* pilha) {
    Celula* atual = pilha->topo;
    printf("Pilha:\n");
    while (atual != NULL) {
        printf("(%d, %d)\n", atual->x, atual->y);
        atual = atual->proximo;
    }
}
void liberarPilha(Pilha* pilha) {
    if (!pilha) return;

    Celula* atual = pilha->topo;
    while (atual != NULL) {
        Celula* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(pilha);
}
