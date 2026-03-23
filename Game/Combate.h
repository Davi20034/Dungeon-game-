#ifndef COMBATE_H_INCLUDED
#define COMBATE_H_INCLUDED
#include "Jogador.h"
#include "Inimigo.h"
#include "Lista.h"
#include "Item.h"
#include "Balanceamento.h"


typedef struct no No;

No* criarIA();
void liberarIA(No* raiz);
char* decidirAcao(No* raiz, float vidaInimigo, float vidaMaxInimigo);
float calcularDano(float ataque, float defesa, int critico, float reducaoDefesa);
void batalhar(Jogador* j, Inimigo* inimigo);
float inimigoGetVidaMax(const Inimigo* ini);

#endif // COMBATE_H_INCLUDED
