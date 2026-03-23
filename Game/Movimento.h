#ifndef MOVIMENTO_H_INCLUDED
#define MOVIMENTO_H_INCLUDED
#include "Jogador.h"
#include "Pilha.h"
#include "Lista.h"
#include "Mapa.h"
#include "Item.h"
#include "Inimigo.h"
#include "Combate.h"
#include "Balanceamento.h"

void configurarTerminal(void);
void restaurarTerminal(void);
char lerTecla(void);
void moverJogador(Jogador* j);
void menuInventario(Jogador* j);
void voltarPasso(Jogador* j);

#endif // MOVIMENTO_H_INCLUDED
