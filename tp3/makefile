# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -g # flags de compilacao
CC = gcc

tp3: tp3.o racionais.o
	$(CC) -o tp3 tp3.o racionais.o

tp3.o: tp3.c
	$(CC) -c $(CFLAGS) tp3.c

racionais.o: racionais.c
	$(CC) -c $(CFLAGS) racionais.c

clean:
	rm -f *.o tp3
