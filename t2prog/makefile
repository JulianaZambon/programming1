TARGET = teste
CC = gcc

CFLAGS = -Wall -g

LDFLAGS = -lm

$(TARGET): polinomio.o teste.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

polinomio.o: polinomio.c polinomio.h
	$(CC) $(CFLAGS) -c polinomio.c

teste.o: teste.c polinomio.h
	$(CC) $(CFLAGS) -c teste.c

clean:
	rm -f *.o

purge:
	rm -f *.o $(TARGET)

all: $(TARGET)