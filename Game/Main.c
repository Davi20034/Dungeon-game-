#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Jogador.h"
#include "Lista.h"
#include "Pilha.h"
#include "Item.h"
#include "Mapa.h"
#include "Movimento.h"

int main() {
    char nome[20];
    printf("Digite o nome do seu jogador: ");
    scanf("%s",nome);
    Jogador* jogador = criarJogador(nome);
    inicializarMapa();
    configurarTerminal();
    srand(time(NULL));

printf("\nBem-vindo a Dungeon, %s!\n", jogadorGetNome(jogador));
    printf("Encontre o Boss (B) no canto inferior direito para vencer!\n");
    printf("Legenda:\n");
    printf("@ = Você | # = Parede | I = Item | E = Inimigo\n");
    printf("X = Armadilha | B = Boss | . = Caminho livre\n\n");

    exibirMapa();

    while (1) {
        moverJogador(jogador);
    }
    liberarJogador(jogador);
    restaurarTerminal();
    return 0;
}
