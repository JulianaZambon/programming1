#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conjunto.h"
#include "lef.h"
#include "fila.h"

/* STRUCTS H, B, M, W ----------------------------------------------------------- */

struct heroi
{
    int ID;                       /* num inteiro que identifica unicamente o heroi */
    struct conjunto *habilidades; /* cada habilidade eh representada por um num inteiro */
    int paciencia;                /* um num inteiro que indica o quao paciente a pessoa eh e isso afeta a permanencia em bases e filas */
    int velocidade;               /* num inteiro indica a velocidade de deslocamento, logo afeta o tempo */
    int experiencia;              /* num inteiro que indica o num de missoes que o heroi ja participou */
    int base;                     /* num inteiro que indica a base a qual o heroi se encontra no momento */
};

struct base
{
    int ID;                     /* num inteiro que identifica a base */
    int lotacao;                /* num de herois naquela base */
    struct conjunto *presentes; /* conjunto dos IDs dos herois presentes na base */
    struct fila *espera;        /* fila de herois esperando na base */
    int local[2];               /* localizacao da base (par de coordenadas inteiras X, Y ≥ 0) */
};

struct missao
{
    int ID;                       /* num inteiro que identifica unicamente a missao */
    struct conjunto *habilidades; /* conjunto de habilidades necessarias para a missao */
    int local[2];                 /* localizacao da missao (par de coordenadas inteiras X, Y ≥ 0) */
};

/* definido pelas entidades acima*/
struct mundo
{
    int NHerois;            /* num total de herois no mundo*/
    struct heroi *Herois;   /* vetor de herois */
    int NBases;             /* num total de bases no mundo */
    struct base *Bases;     /* vetor de bases */
    int NMissoes;           /* num total de missoes a cumprir */
    struct missao *Missoes; /* vetor de missoes */
    int NHabilidades;       /* num total de habilidades distintas */
    int TamanhoMundo[2];    /* tamanho do mundo (par de coordenadas inteiras X, Y ≥ 0) */
    int Relogio;            /* tempo atual do mundo */
};

/* INICIALIZAÇÕES ----------------------------------------------------------- */

int main()
{
    /* declaracoes de variaveis aqui */

    srand(0); /* use zero, nao faca com time (0) */

    /* coloque seu codigo aqui */

    return 0;
}
