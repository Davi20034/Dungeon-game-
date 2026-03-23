#include <stdio.h>
#include <stdlib.h>
#include "Jogador.h"
#include "Item.h"
#include "Lista.h"

typedef struct cel {
    int quantidade;
    int tipo;
    struct cel* prox;
    struct cel* ant;
} Celula;

typedef struct lista {
    Celula* inicio;
    Celula* fim;
    int tamanho;
} Lista;

Lista* criarLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

Celula* busca(Lista* lista, int pos) {
    if (pos < 0 || pos >= lista->tamanho) return NULL;
    Celula* bus = lista->inicio;
    for (int i = 0; i < pos; i++) {
        bus = bus->prox;
    }
    return bus;
}

int inserirOuSomar(Lista* lista, int quantidade, int tipo) {
    Celula* atual = lista->inicio;

    while (atual != NULL) {
        if (atual->tipo == tipo) {
            atual->quantidade += quantidade;
            return quantidade;
        }
        atual = atual->prox;
    }

    Celula* nova = (Celula*)malloc(sizeof(Celula));
    nova->tipo = tipo;
    nova->quantidade = quantidade;
    nova->prox = NULL;
    nova->ant = lista->fim;

    if (lista->inicio == NULL) {
        lista->inicio = nova;
        lista->fim = nova;
    } else {
        lista->fim->prox = nova;
        lista->fim = nova;
    }

    lista->tamanho++;
    return tipo;
}

int removerInicio(Lista* lista) {
    if (lista->inicio == NULL) return -1;

    Celula* cel = lista->inicio;
    int v = cel->tipo;

    lista->inicio = cel->prox;

    if (lista->inicio == NULL) {
        lista->fim = NULL;
    } else {
        lista->inicio->ant = NULL;
    }

    free(cel);
    lista->tamanho--;
    return v;
}

int removerFim(Lista* lista) {
    if (lista->fim == NULL) return -1;

    Celula* cel = lista->fim;
    int v = cel->tipo;

    lista->fim = cel->ant;

    if (lista->fim == NULL) {
        lista->inicio = NULL;
    } else {
        lista->fim->prox = NULL;
    }

    free(cel);
    lista->tamanho--;
    return v;
}

int remover(Lista* lista, int tipo, int quantidade) {
    if (lista == NULL || lista->inicio == NULL) return -1;
    Celula* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->tipo == tipo) {
            if (quantidade <= 0 || quantidade >= atual->quantidade) {
                if (atual->ant == NULL) {
                    return removerInicio(lista);
                } else if (atual->prox == NULL) {
                    return removerFim(lista);
                } else {
                    atual->ant->prox = atual->prox;
                    atual->prox->ant = atual->ant;
                    int v = atual->tipo;
                    free(atual);
                    lista->tamanho--;
                    return v;
                }
            } else {
                atual->quantidade -= quantidade;
                return quantidade;
            }
        }
        atual = atual->prox;
    }
    return -1;
}

void imprimirLista(Lista* lista) {
    printf("Lista: (tipo:quantidade)\n");
    Celula* atual = lista->inicio;
    while (atual != NULL) {
        printf("[%d:%d] ", atual->tipo, atual->quantidade);
        atual = atual->prox;
    }
    printf("\n");
}

void imprimirListaFormatada(Lista* lista, int nivelJogador) {
        if (!lista || lista->tamanho == 0) {
        printf("Inventario vazio.\n");
        return;
    }

    printf("%-20s %-10s %-10s\n", "Nome", "Quantidade", "Tipo");
    printf("----------------------------------------\n");
    Celula* atual = lista->inicio;

        while (atual != NULL) {
            Item* item = criarItem(atual->tipo, atual->quantidade, nivelJogador);
            printf("%-20s %-10d %-10d\n",
            getItemNome(item),
            atual->quantidade,
            getItemTipo(item));
            free(item);
            atual = atual->prox;
        }
}

void liberarLista(Lista* lista) {
    if (!lista) return;

    Celula* atual = lista->inicio;
    while (atual != NULL) {
        Celula* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(lista);
}
