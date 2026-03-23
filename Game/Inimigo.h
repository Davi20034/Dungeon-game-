#ifndef INIMIGO_H_INCLUDED
#define INIMIGO_H_INCLUDED

typedef struct inimigo Inimigo;

Inimigo* gerarInimigoAleatorio(int x, int y, int nivelJogador);
Inimigo* boss(int x, int y); // Removido parâmetro de nível

// Getters
const char* inimigoGetNome(const Inimigo* ini);
float inimigoGetVida(const Inimigo* ini);
float inimigoGetVidaMax(const Inimigo* ini);
float inimigoGetDano(const Inimigo* ini);
int inimigoGetTipo(const Inimigo* ini);
int inimigoGetQtdeItem(const Inimigo* ini);
int inimigoGetTipoItem(const Inimigo* ini);

// Setter
void inimigoSetVida(Inimigo* ini, float vida);

#endif // INIMIGO_H_INCLUDED
