#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
typedef struct cel Celula;
typedef struct lista Lista;

Lista* criarLista();
Celula* busca(Lista* lista, int pos);
int inserirOuSomar(Lista* lista, int quantidade, int tipo);
int removerInicio(Lista* lista);
int removerFim(Lista* lista);
void imprimirLista(Lista* lista);
void imprimirListaFormatada(Lista* lista, int nivelJogador);
int remover(Lista* lista, int tipo, int quantidade);
void liberarLista(Lista* lista);

#endif // LISTA_H_INCLUDED
