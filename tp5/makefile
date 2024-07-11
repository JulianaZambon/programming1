# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = tp5.o fila.o lef.o 

tp5: tp5.o fila.o lef.o
	$(CC) -o tp5 tp5.o fila.o lef.o $(LDFLAGS)

fila.o: fila.c
	$(CC) -c $(CFLAGS) fila.c

lef.o: lef.c
	$(CC) -c $(CFLAGS) lef.c

tp5.o: tp5.c
	$(CC) -c $(CFLAGS) tp5.c

clean:
	rm -f $(objects) tp4
