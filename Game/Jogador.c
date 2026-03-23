#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Jogador.h"
#include "Movimento.h"

struct jogador {
    char nome[50];
    int x, y;
    float vida, vida_max;
    float dano, defesa;
    int nivel, experiencia;
    Lista* inventario;
    Pilha* passos;
};

Jogador* criarJogador(char nome[]) {
    Jogador* j = malloc(sizeof(Jogador));
    strcpy(j->nome, nome);
    j->x = j->y = 0;
    j->vida = j->vida_max = VIDA_BASE;
    j->dano = 3000;
    j->defesa = DEFESA_BASE;
    j->nivel = 1;
    j->experiencia = 0;
    j->inventario = criarLista();
    j->passos = criaPilha();
    mapa[0][0] = '@';
    return j;
}

void liberarJogador(Jogador* j) {
    if (!j) return;
    liberarLista(j->inventario);
    liberarPilha(j->passos);
    free(j);
}

// Getters
const char* jogadorGetNome(const Jogador* j) { return j->nome; }
int jogadorGetX(const Jogador* j) { return j->x; }
int jogadorGetY(const Jogador* j) { return j->y; }
float jogadorGetVida(const Jogador* j) { return j->vida; }
float jogadorGetVidaMax(const Jogador* j) { return j->vida_max; }
float jogadorGetDano(const Jogador* j) { return j->dano; }
float jogadorGetDefesa(const Jogador* j) { return j->defesa; }
int jogadorGetNivel(const Jogador* j) { return j->nivel; }
int jogadorGetExperiencia(const Jogador* j) { return j->experiencia; }
Lista* jogadorGetInventario(const Jogador* j) { return j->inventario; }
Pilha* jogadorGetPassos(Jogador* j) { return j->passos; }

// Setters
void jogadorSetPosicao(Jogador* j, int x, int y) { j->x = x; j->y = y; }
    void jogadorSetVida(Jogador* j, float vida) {
        j->vida = fmaxf(0, vida);
        if (j->vida <= 0) {
            printf("\nVocê foi derrotado!\n");
            restaurarTerminal();
            exit(0);
        }
    }
void jogadorSetExperiencia(Jogador* j, int xp) { j->experiencia = xp; }

// Funções auxiliares
void atualizarPosicaoJogador(Jogador* j, int novo_x, int novo_y) {
    int x_antigo = j->x, y_antigo = j->y;
    j->x = novo_x; j->y = novo_y;
    atualizarMapa(x_antigo, y_antigo, novo_x, novo_y);
}

void mostrarStatusJogador(const Jogador* j) {
    printf("\n=== STATUS DO JOGADOR ===\n");
    printf("Nome: %s\nNivel: %d\nExperiencia: %d/%d\n", j->nome, j->nivel, j->experiencia, j->nivel * 100);
    printf("Vida: %.1f/%.1f\nDano: %.1f\nDefesa: %.1f\nPosicao: (%d, %d)\n",
        j->vida, j->vida_max, j->dano, j->defesa, j->x, j->y);
}

void subirNivel(Jogador* j) {
    j->nivel++;
    j->experiencia = 0;

    float aumentoVida = ESCALA_VIDA_NIVEL + (j->nivel * 2);
    float aumentoDano = ESCALA_DANO_NIVEL + (j->nivel / 3.0f);
    float aumentoDefesa = ESCALA_DEFESA_NIVEL + (j->nivel / 4.0f);

    j->vida_max += aumentoVida;
    j->vida = j->vida_max;
    j->dano += aumentoDano;
    j->defesa += aumentoDefesa;

    printf("\nParabens! Voce subiu para o nivel %d!\n", j->nivel);
    printf("Vida maxima: %.1f (+%.1f)\nDano: %.1f (+%.1f)\nDefesa: %.1f (+%.1f)\n\n",
        j->vida_max, aumentoVida, j->dano, aumentoDano, j->defesa, aumentoDefesa);
}

void ganharExperiencia(Jogador* j, int xp) {
    float xpModificado = xp * (1.0f + j->nivel * 0.1f);
    j->experiencia += xpModificado;

    int xp_necessario = XP_BASE * pow(j->nivel, FATOR_ESCALA_NIVEL);
    if (j->experiencia >= xp_necessario) {
        subirNivel(j);
    }
}
//item
void aplicarEfeitoItem(int tipo, Jogador* j) {
    if (!j) return;
    float fatorNivel = 1.0f + (j->nivel * 0.5f);

    switch(tipo) {
        case ITEM_POT_VIDA: {
            float cura = 20.0f * fatorNivel;
            j->vida = fminf(j->vida + cura, j->vida_max);
            printf("Voce recuperou %.1f pontos de vida! (%.1f/%.1f)\n", cura, j->vida, j->vida_max);
            break;
        }
        case ITEM_ESPADA: {
            float bonusDano = 5.0f * fatorNivel;
            j->dano += bonusDano;
            printf("Seu dano aumentou em %.1f pontos! (Dano total: %.1f)\n", bonusDano, j->dano);
            break;
        }
        case ITEM_ESCUDO: {
            float bonusDefesa = 5.0f * fatorNivel;
            j->defesa += bonusDefesa;
            printf("Sua defesa aumentou em %.1f pontos! (Defesa total: %.1f)\n", bonusDefesa, j->defesa);
            break;
        }
        case ITEM_BOMBA:
            printf("Bomba preparada! Seu proximo ataque causara dano extra!\n");
            break;
        default:
            printf("Item nao tem efeito conhecido.\n");
    }

    mostrarStatusJogador(j);
}

