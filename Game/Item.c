#include "Item.h"
#include "Balanceamento.h"
#include "Jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct item {
    char nome[120];
    int tipo;
    int quantidade;
    int efeito;
};

Item* criarItem(int tipo, int quantidade, int nivelJogador) {
    Item* item = malloc(sizeof(Item));
    item->tipo = tipo;
    item->quantidade = quantidade;

    float fatorNivel = 1.0f + (nivelJogador * 0.5f);

    switch(tipo) {
        case ITEM_POT_VIDA:
            strcpy(item->nome, "Pocao de Vida");
            item->efeito = 25 * fatorNivel;
            break;
        case ITEM_ESPADA:
            strcpy(item->nome, "Espada Afiada");
            item->efeito = 25 * fatorNivel;
            break;
        case ITEM_ESCUDO:
            strcpy(item->nome, "Escudo Resistente");
            item->efeito = 25 * fatorNivel;
            break;
        case ITEM_BOMBA:
            strcpy(item->nome, "Bomba Explosiva");
            item->efeito = 40 * fatorNivel;
            break;
        default:
            strcpy(item->nome, "Item Desconhecido");
            item->efeito = 0;
    }

    return item;
}

void mostrarDescricaoItem(int tipo) {
    switch(tipo) {
        case ITEM_POT_VIDA:
            printf("Pocao de Vida - Recupera 25 pontos de vida\nTipo: Consumivel\nEfeito: Restauracao de HP\n");
            break;
        case ITEM_ESPADA:
            printf("Espada Afiada - Aumenta o dano do jogador\nTipo: Equipamento\nEfeito: +25 de dano permanente\n");
            break;
        case ITEM_ESCUDO:
            printf("Escudo Resistente - Aumenta a defesa do jogador\nTipo: Equipamento\nEfeito: +25 de defesa permanente\n");
            break;
        case ITEM_BOMBA:
            printf("Bomba Explosiva - Causa dano massivo ao inimigo\nTipo: Consumivel\nEfeito: 40 de dano\n");
            break;
        default:
            printf("Item desconhecido - Sem informacoes\n");
    }
}

// Getters
int getItemQuantidade(const Item* item) {
    return item->quantidade;
}

int getItemTipo(const Item* item) {
    return item->tipo;
}

const char* getItemNome(const Item* item) {
    return item->nome;
}
