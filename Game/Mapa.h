#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#define TAM 10
extern char mapa[TAM][TAM];
void inicializarMapa(void);
void exibirMapa(void);
void atualizarMapa(int x_antigo, int y_antigo, int x_novo, int y_novo);
void definirSaida(int x, int y);

#endif // MAPA_H_INCLUDED
