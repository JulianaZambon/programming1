# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = tp4.o lista.o 

tp4: tp4.o lista.o
	$(CC) -o tp4 tp4.o lista.o $(LDFLAGS)

fila.o: fila.c
	$(CC) -c $(CFLAGS) lista.c

testa_fila.o: testa_fila.c
	$(CC) -c $(CFLAGS) tp4.c

clean:
	rm -f $(objects) tp4
