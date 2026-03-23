#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "Movimento.h"


extern char mapa[TAM][TAM];

static struct termios oldt, newt;

void configurarTerminal(void) {
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restaurarTerminal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

char lerTecla(void) {
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void moverJogador(Jogador* j) {
    printf("\nUse WASD para mover, I para inventário, V para voltar, Q para sair\n");
    printf("Selecione uma ação: ");
    fflush(stdout);

    char direcao = lerTecla();
    printf("\n");

    int novo_x = jogadorGetX(j);
    int novo_y = jogadorGetY(j);

    switch(direcao) {
        case 'w': case 'W': novo_x--; break;
        case 's': case 'S': novo_x++; break;
        case 'a': case 'A': novo_y--; break;
        case 'd': case 'D': novo_y++; break;
        case 'i': case 'I': menuInventario(j); return;
        case 'v': case 'V': voltarPasso(j); return;
        case 'q': case 'Q': exit(0); break;
        default:
            printf("Comando invalido!\n");
            return;
    }

    if (novo_x < 0 || novo_x >= TAM || novo_y < 0 || novo_y >= TAM) {
        printf("Voce bateu na parede do mapa!\n");
        return;
    }

    if (mapa[novo_x][novo_y] == '#') {
        printf("Voce encontrou uma parede!\n");
        return;
    }


    int x_antigo = jogadorGetX (j);
    int y_antigo = jogadorGetY (j);

    push(jogadorGetPassos(j), x_antigo, y_antigo);

    if (mapa[novo_x][novo_y] == 'I') {
        int itemvariado = (rand() % 4) + 1;
        int quantidade = (rand() % (1 + jogadorGetNivel(j)/2)) + 1;
        Item* item = criarItem(itemvariado, quantidade, jogadorGetNivel(j));
        printf("Voce encontrou %d %s!\n", quantidade, getItemNome(item));
        sleep(2);
        inserirOuSomar(jogadorGetInventario(j), quantidade, itemvariado);
    }
        else if (mapa[novo_x][novo_y] == 'E') {
            Inimigo* ini = gerarInimigoAleatorio(novo_x, novo_y, jogadorGetNivel(j));
            batalhar(j, ini);
            free(ini);  // Libera o inimigo
        }
        else if (mapa[novo_x][novo_y] == 'X') {
         float danoArmadilha = 10 * (1.0f + (jogadorGetNivel(j) * 0.1f));
            printf("Voce caiu em uma armadilha! Perdeu %.1f de vida.\n", danoArmadilha);
            sleep(2);
            float novaVida = jogadorGetVida(j) - danoArmadilha;
            jogadorSetVida(j, novaVida);

            if (jogadorGetVida(j) <= 0) {
                printf("Voce morreu na armadilha. Fim de jogo.\n");
                restaurarTerminal();
                exit(0);
            }
        }
        else if (mapa[novo_x][novo_y] == 'S') {
            Inimigo* ini = boss(novo_x, novo_y, jogadorGetNivel(j));
            printf("Um %s apareceu! Cuidado!\n", inimigoGetNome(ini));
            batalhar(j, ini);

            if (inimigoGetVida(ini) <= 0) {
                printf("\nVoce derrotou o boss e alcançou a saida! Parabens, voce venceu o jogo!\n");
                free(ini);
                restaurarTerminal();
                exit(0);
            } else {
                printf("Voce fugiu do boss ou ele ainda esta vivo.\n");
                free(ini);
            }
        }

    atualizarPosicaoJogador(j, novo_x, novo_y);
        exibirMapa();
         printf("Posicao atual: (%d, %d)\n", jogadorGetX(j), jogadorGetY(j));
}

void menuInventario(Jogador* j) {
    int opcao, tipo, quantidade;

    restaurarTerminal();

    while (1) {
        printf("\n=== INVENTARIO ===\n");
        imprimirListaFormatada(jogadorGetInventario(j), jogadorGetNivel(j));
        printf("\n1 - Usar item\n");
        printf("2 - Descartar item\n");
        printf("3 - Ver descricao do item\n");
        printf("4 - Ver status do jogador\n");
        printf("0 - Voltar ao jogo\n");
        printf("Escolha: ");

        scanf("%d", &opcao);

        if (opcao == 0){
            system("clear");
            exibirMapa();
            break;
        }

        if (opcao == 4) {
            mostrarStatusJogador(j);
            continue;
        }

        if (opcao == 3) {
            mostrarDescricaoItem(tipo);
            continue;
        }

        printf("Digite o tipo do item (ou 0 para voltar): ");
        scanf("%d", &tipo);

        if (tipo == 0) {
            continue; // volta para menu anterior
        }

        printf("Digite a quantidade: ");
        scanf("%d", &quantidade);

        int resultado = remover(jogadorGetInventario(j), tipo, quantidade);
        if (resultado > 0) {
            if (opcao == 1) {
                aplicarEfeitoItem(tipo, j);
                printf("Item usado com sucesso!\n");
            } else if (opcao == 2) {
                printf("Item descartado com sucesso!\n");
            }
        } else {
            printf("Item inexistente ou quantidade invalida. Tente novamente.\n");
            continue;
        }
    }

    configurarTerminal(); // volta ao modo de jogo
}

void voltarPasso(Jogador* j) {
    int x, y;
    if (pop(jogadorGetPassos(j), &x, &y)) {
        atualizarPosicaoJogador(j, x, y);
        printf("Voce voltou para (%d, %d)\n", x, y);
        sleep(5);
    } else {
        printf("Nao ha movimentos para voltar.\n");
    }
}
