#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Mapa.h"

char mapa[TAM][TAM];
int saida_x = -1;
int saida_y = -1;

void inicializarMapa() {
    srand(time(NULL));

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            int sorteio = rand() % 100;

            if (sorteio < 10)
                mapa[i][j] = '#';        // Parede
            else if (sorteio < 25)
                mapa[i][j] = 'I';        // Item
            else if (sorteio < 50)
                mapa[i][j] = 'E';        // Inimigo
            else if (sorteio < 100)
                mapa[i][j] = 'X';        // Armadilha
            else if (i == TAM-1 && j == TAM-1)
                mapa[i][j] = 'B';        // Boss
            else
                mapa[i][j] = '.';        // Passagem livre
        }
    }

    mapa[0][0] = '@';  // Posição inicial do jogador
    definirSaida(TAM-1, TAM-1);
}

void definirSaida(int x, int y) {
    if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
        if (saida_x != -1 && saida_y != -1) {
            mapa[saida_x][saida_y] = '.';
        }
        saida_x = x;
        saida_y = y;
        mapa[x][y] = 'S'; // 'S' representa a saída
    }
}

void exibirMapa() {
    system("clear");

    printf("\nMapa da Dungeon:\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            char visivel = mapa[i][j];

            // Esconde inimigos e armadilhas
            if (visivel == 'E' || visivel == 'X') {
                visivel = '.';
            }

            printf(" %c ", visivel);
        }
        printf("\n");
    }

    printf("\nLegenda:\n");
    printf("@ = Voce | # = Parede | I = Item | E = Inimigo\n");
    printf("X = Armadilha | B = Boss | S = Saida | . = Caminho livre\n\n");
}

void atualizarMapa(int x_antigo, int y_antigo, int x_novo, int y_novo) {
    // Restaura a posição antiga
    if (x_antigo == 0 && y_antigo == 0) {
        mapa[x_antigo][y_antigo] = '.';
    } else {
        int sorteio = rand() % 100;
        if (sorteio < 5) {
            mapa[x_antigo][y_antigo] = 'I';
        } else if (sorteio < 10) {
            mapa[x_antigo][y_antigo] = 'E';
        } else {
            mapa[x_antigo][y_antigo] = '.';
        }
    }

    mapa[x_novo][y_novo] = '@';
}
