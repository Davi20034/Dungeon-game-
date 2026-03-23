#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "Inimigo.h"
#include "Balanceamento.h"

struct inimigo {
    char nome[50];
    float vida;
    float vida_max;
    float dano;
    int tipo;
    int tipoItem;
    int qtdeItem;
    int x, y;
};

// Valores base para cada tipo de inimigo (fixos, não escalam com nível)
static const float VIDAS_BASE[] = {25, 50, 85, 120, 200, 150};
static const float DANOS_BASE[] = {4, 8, 15, 20, 30, 18};

Inimigo* gerarInimigoAleatorio(int x, int y, int nivelJogador) {
    Inimigo* ini = malloc(sizeof(Inimigo));
    if (!ini) return NULL;

    // Chance de Boss após nível 10 (opcional, pode manter ou remover)
    if (nivelJogador > 10 && (rand() % 100) < 10) {
        return boss(x, y);
    }

    // Escolhe tipo baseado no nível máximo disponível, mas sem escalar atributos
    int limiteTipo = fmin(1 + nivelJogador / 3, 5);
    ini->tipo = rand() % (limiteTipo + 1);

    // Chance de drop fixa
    int dropItem = (rand() % 100) < (CHANCE_DROP_BASE * 100);

    const char* nomes[] = {"Goblin", "Orc", "Uruk-Hai", "Olog-hai", "Troll", "Lobisomen"};

    // Configuração do inimigo (valores fixos)
    strcpy(ini->nome, nomes[ini->tipo]);
    ini->vida_max = VIDAS_BASE[ini->tipo];
    ini->vida = ini->vida_max;
    ini->dano = DANOS_BASE[ini->tipo];

    ini->tipoItem = dropItem ? ((rand() % 4) + 1) : 0;
    ini->qtdeItem = dropItem ? ((rand() % 3) + 1) : 0; // Quantidade fixa
    ini->x = x;
    ini->y = y;

    return ini;
}

Inimigo* boss(int x, int y) {
    Inimigo* ini = malloc(sizeof(Inimigo));
    if (!ini) return NULL;

    strcpy(ini->nome, "Balrogs, A Ruina de Durin");
    ini->vida_max = 300;  // Vida fixa do boss
    ini->vida = ini->vida_max;
    ini->dano = 40;       // Dano fixo do boss
    ini->tipo = 99;
    ini->tipoItem = ITEM_ESPADA;
    ini->qtdeItem = 1;
    ini->x = x;
    ini->y = y;

    return ini;
}

// Getters
int inimigoGetQtdeItem(const Inimigo* ini) { return ini->qtdeItem; }
int inimigoGetTipoItem(const Inimigo* ini) { return ini->tipoItem; }
const char* inimigoGetNome(const Inimigo* ini) { return ini->nome; }
float inimigoGetVida(const Inimigo* ini) { return ini->vida; }
float inimigoGetDano(const Inimigo* ini) { return ini->dano; }
int inimigoGetTipo(const Inimigo* ini) { return ini->tipo; }
float inimigoGetVidaMax(const Inimigo* ini) { return ini->vida_max; }

// Setter
void inimigoSetVida(Inimigo* ini, float vida) {
    ini->vida = fmaxf(0, fminf(vida, ini->vida_max));
}
