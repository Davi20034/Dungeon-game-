CC = gcc
CFLAGS = -Wall -Wextra -std=c99
# Flags de linkedição (biblioteca matemática no final)
LDFLAGS = -lm

TARGET = jogo

OBJS = Main.o Jogador.o Lista.o Pilha.o Mapa.o Inimigo.o Combate.o Movimento.o Item.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

Main.o: Main.c Jogador.h Mapa.h Movimento.h Item.h
	$(CC) $(CFLAGS) -c Main.c

Jogador.o: Jogador.c Jogador.h Lista.h Pilha.h Mapa.h Balanceamento.h
	$(CC) $(CFLAGS) -c Jogador.c

Lista.o: Lista.c Lista.h Jogador.h
	$(CC) $(CFLAGS) -c Lista.c

Pilha.o: Pilha.c Pilha.h
	$(CC) $(CFLAGS) -c Pilha.c

Mapa.o: Mapa.c Mapa.h Jogador.h
	$(CC) $(CFLAGS) -c Mapa.c

Inimigo.o: Inimigo.c Inimigo.h Balanceamento.h
	$(CC) $(CFLAGS) -c Inimigo.c

Combate.o: Combate.c Combate.h Jogador.h Inimigo.h Balanceamento.h Lista.h
	$(CC) $(CFLAGS) -c Combate.c

Movimento.o: Movimento.c Movimento.h Jogador.h Mapa.h Inimigo.h Combate.h Balanceamento.h
	$(CC) $(CFLAGS) -c Movimento.c

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild