#ifndef JOGADOR_H_INCLUDED
#define JOGADOR_H_INCLUDED

#include "Lista.h"
#include "Pilha.h"
#include "Balanceamento.h"

typedef struct jogador Jogador;

Jogador* criarJogador(char nome[]);
void liberarJogador(Jogador* j);

// Getters
const char* jogadorGetNome(const Jogador* j);
int jogadorGetX(const Jogador* j);
int jogadorGetY(const Jogador* j);
float jogadorGetVida(const Jogador* j);
float jogadorGetVidaMax(const Jogador* j);
float jogadorGetDano(const Jogador* j);
float jogadorGetDefesa(const Jogador* j);
int jogadorGetNivel(const Jogador* j);
int jogadorGetExperiencia(const Jogador* j);
Lista* jogadorGetInventario(const Jogador* j);
Pilha* jogadorGetPassos(Jogador* j);

// Setters
void jogadorSetPosicao(Jogador* j, int x, int y);
void jogadorSetVida(Jogador* j, float vida);
void jogadorSetExperiencia(Jogador* j, int xp);

// Funções
void atualizarPosicaoJogador(Jogador* j, int novo_x, int novo_y);
void subirNivel(Jogador* j);
void ganharExperiencia(Jogador* j, int xp);
void mostrarStatusJogador(const Jogador* j);

// item
void aplicarEfeitoItem(int tipo, Jogador* j);
#endif
