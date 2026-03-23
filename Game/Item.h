#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
typedef struct item Item;
Item* criarItem(int tipo, int quantidade, int nivelJogador);
void mostrarDescricaoItem(int tipo);

// Getters
int getItemQuantidade(const Item* item);
int getItemTipo(const Item* item);
const char* getItemNome(const Item* item);

#endif
