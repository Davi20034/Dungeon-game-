#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "Combate.h"
#include "Inimigo.h"
#include "Movimento.h"
struct no {
    char condicao[30];
    char acao[20];
    struct no* esq;
    struct no* dir;
};

No* criarIA() {
    No* raiz = malloc(sizeof(No));
    strcpy(raiz->condicao, "vida < 0.5");
    raiz->esq = malloc(sizeof(No));
    raiz->dir = malloc(sizeof(No));

    strcpy(raiz->esq->acao, "curar");
    raiz->esq->esq = raiz->esq->dir = NULL;

    strcpy(raiz->dir->acao, "atacar");
    raiz->dir->esq = raiz->dir->dir = NULL;

    return raiz;
}

void liberarIA(No* raiz) {
    if (!raiz) return;
    liberarIA(raiz->esq);
    liberarIA(raiz->dir);
    free(raiz);
     raiz = NULL;
}

char* decidirAcao(No* raiz, float vidaInimigo, float vidaMaxInimigo) {
    if (!raiz) return "atacar";

    if ((vidaInimigo/vidaMaxInimigo) < 0.5f && raiz->esq) {
        return raiz->esq->acao;
    }
    return raiz->dir->acao;
}

float calcularDano(float ataque, float defesa, int critico, float reducaoDefesa) {
    float dano = ataque * (1.0f + (critico ? 0.5f : 0.0f)) * (1.0f - (defesa / (defesa + 100.0f)));
    return fmaxf(1.0f, dano - reducaoDefesa);
}

void batalhar(Jogador* j, Inimigo* inimigo) {
    No* ia = criarIA();
    int fugir = 0;
    int defesa_ativa;
    int usando_bomba = 0;

    printf("\nUm %s apareceu! (Nível: %d)\n", inimigoGetNome(inimigo), jogadorGetNivel(j));

    while (jogadorGetVida(j) > 0 && inimigoGetVida(inimigo) > 0 && !fugir) {
        printf("\n=== STATUS ===\n");
        printf("Jogador: %s (Nivel %d)\n",
              jogadorGetNome(j),
              jogadorGetNivel(j));
        printf("Vida: %.1f/%.1f | XP: %d/%d\n",
              jogadorGetVida(j),
              jogadorGetVidaMax(j),
              jogadorGetExperiencia(j),
              (int)(XP_BASE * pow(jogadorGetNivel(j), FATOR_ESCALA_NIVEL)));
              printf("Inimigo: %s\n", inimigoGetNome(inimigo));
              printf("Vida: %.1f/%.1f\n\n", inimigoGetVida(inimigo), inimigoGetVidaMax(inimigo));

        int entradaValida = 0;
        int critico;
        float reducaoDefesa;
        do {
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        printf("3 - Usar Item\n");
        printf("4 - Fugir\n");
        printf("Escolha: ");

        int escolha;
        scanf(" %d", &escolha);

            entradaValida = 1;
             critico = rand() % 100 < (CHANCE_CRITICO * 100);
             reducaoDefesa = jogadorGetDefesa(j) * (defesa_ativa ? 2.0f : 1.0f);

            switch (escolha) {
                case 1: {
                    float dano = calcularDano(jogadorGetDano(j), 0, critico, reducaoDefesa);
                    if (usando_bomba) {
                        dano += 30 * (1.0f + (jogadorGetNivel(j) * 0.5f));
                        usando_bomba = 0;
                        printf("Bomba explodiu! ");
                    }
                    inimigoSetVida(inimigo, inimigoGetVida(inimigo) - dano);
                    printf(critico ? "Golpe critico! " : "");
                    printf("Voce causou %.1f de dano!\n", dano);
                    break;
                }
                case 2:
                    defesa_ativa = 1;
                    printf("Voce assume posicao defensiva!\n");
                    break;
                case 3: {
                    printf("\n Itens disponíveis:\n");
                    imprimirListaFormatada(jogadorGetInventario(j), jogadorGetNivel(j));

                    printf("\n Digite o tipo do item (1-4) ou 0 para cancelar:\n ");
                    int tipo;
                    scanf("%d", &tipo);

                    if (tipo == 0) {
                        printf("\n Voce cancelou o uso de item.\n");
                        entradaValida = 0;  // Volta para o menu sem consumir turno
                        break;
                    }

                    if (tipo < 1 || tipo > 4) {
                        printf("\n Tipo invalido. Tente novamente.\n");
                        entradaValida = 0;
                        break;
                    }

                    printf("Digite a quantidade: \n");
                    int quantidade;
                    scanf("%d", &quantidade);

                    if (quantidade <= 0) {
                        printf("\n Quantidade invalida. Tente novamente.\n");
                        entradaValida = 0;
                        break;
                    }

                    int resultado = remover(jogadorGetInventario(j), tipo, quantidade);
                    if (resultado > 0) {
                        if (tipo == ITEM_BOMBA) {
                            usando_bomba = 1;
                            printf("\n Bomba preparada para o proximo ataque!\n");
                        } else {
                            aplicarEfeitoItem(tipo, j);
                        }
                    } else {
                        printf("\n Voce nao tem essa quantidade de item. Tente novamente.\n");
                        entradaValida = 0;
                    }
                    break;
                }
                case 4:
                    fugir = ((float)rand() / RAND_MAX) < CHANCE_FUGA;
                    printf(fugir ? "Fuga bem sucedida!\n" : "Fuga falhou!\n");
                    break;
                default:
                    printf("\n Nao possui esta escolha! Tente novamente.\n");
                    entradaValida = 0;
            }
        } while (!entradaValida);


      if (inimigoGetVida(inimigo) > 0 && !fugir) {
            char* acao = decidirAcao(ia, inimigoGetVida(inimigo), inimigoGetVidaMax(inimigo));

            if (strcmp(acao, "atacar") == 0) {
                float dano = calcularDano(inimigoGetDano(inimigo), jogadorGetDefesa(j), critico, reducaoDefesa);
                jogadorSetVida(j, jogadorGetVida(j) - dano);
                printf("O %s te atacou causando %.1f de dano!\n", inimigoGetNome(inimigo), dano);
            }
            else if (strcmp(acao, "curar") == 0) {
                float cura = 15 * (1.0f + (jogadorGetNivel(j) * ESCALA_INIMIGO_NIVEL));
                inimigoSetVida(inimigo, fminf(inimigoGetVida(inimigo) + cura, inimigoGetVidaMax(inimigo)));
                printf("O %s se curou em %.1f pontos de vida!\n", inimigoGetNome(inimigo), cura);
            }
        }

        if (jogadorGetVida(j) <= 0) {
            printf("\nVoce foi derrotado pelo %s...\n", inimigoGetNome(inimigo));
            liberarIA(ia);
            restaurarTerminal();
            exit(0);
        }


    if (inimigoGetVida(inimigo) <= 0) {
    printf("\nVoce derrotou o %s!\n", inimigoGetNome(inimigo));

    int xp_base = 0;
    switch(inimigoGetTipo(inimigo)) {
        case 0: xp_base = 20; break;
        case 1: xp_base = 35; break;
        case 2: xp_base = 50; break;
        case 3: xp_base = 75; break;
        case 4: xp_base = 100; break;
        case 99: xp_base = 500; break; // Boss
        default: xp_base = 30;
    }

    ganharExperiencia(j, xp_base);

    if (inimigoGetQtdeItem(inimigo) > 0) {
        int tipo = inimigoGetTipoItem(inimigo);
        int qtde = inimigoGetQtdeItem(inimigo);
        inserirOuSomar(jogadorGetInventario(j), qtde, tipo);

        Item* temp = criarItem(tipo, qtde, jogadorGetNivel(j));
        printf("Voce recebeu %d unidade(s) do item tipo %d - %s!\n",qtde, tipo, getItemNome(temp));
        sleep(2);

        free(temp);

}

liberarIA(ia);
  }
  defesa_ativa = 0;
}
}
