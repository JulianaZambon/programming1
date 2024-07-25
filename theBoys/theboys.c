#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conjunto.h"
#include "lef.h"
#include "fila.h"

/* EVENTOS --------------------------------------------------------------------- */
#define CHEGADA 0
#define SAIDA 1
#define MISSAO 2
#define FIM_SIMULACAO 3

/* MUNDO VIRTUAL --------------------------------------------------------------- */
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES T_FIM_DO_MUNDO / 100

/* HEROI ------------------------------------------------------------------------ */
#define MIN_EXPERIENCIA 0
#define MIN_PACIENCIA 0
#define MAX_PACIENCIA 100
#define MIN_VELOCIDADE 50
#define MAX_VELOCIDADE 5000
#define MIN_HABILIDADES 1
#define MAX_HABILIDADES 3

/* BASE ------------------------------------------------------------------------- */
#define MIN_LOTACAO 3
#define MAX_LOTACAO 10
#define MIN_X 0
#define MAX_X N_TAMANHO_MUNDO - 1
#define MIN_Y 0
#define MAX_Y N_TAMANHO_MUNDO - 1

/* MISSAO ---------------------------------------------------------------------- */
#define MIN_HABILIDADES_MISSAO 6
#define MAX_HABILIDADES_MISSAO 10
#define MIN_X_MISSAO 0
#define MAX_X_MISSAO N_TAMANHO_MUNDO - 1
#define MIN_Y_MISSAO 0
#define MAX_Y_MISSAO N_TAMANHO_MUNDO - 1
#define MIN_ID 0
#define MAX_ID N_MISSOES - 1


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
    int localX;                 /* localizacao da base (par de coordenadas inteiras X, Y ≥ 0) */
    int localY;
};

struct missao
{
    int ID;                       /* num inteiro que identifica unicamente a missao */
    struct conjunto *habilidades; /* conjunto de habilidades necessarias para a missao */
    int localX;                   /* localizacao da missao (par de coordenadas inteiras X, Y ≥ 0) */
    int localY;
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
    int TamanhoMundoX;      /* tamanho do mundo (par de coordenadas inteiras X, Y ≥ 0) */
    int TamanhoMundoY;
    int Relogio;            /* tempo atual do mundo */
};

/* FUNÇÕES AUXILIARES ----------------------------------------------------------- */

/* distancia entre dois pontos */
int distancia(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

/* FUNCOES DE INICIALIZACAO ----------------------------------------------------- */

/* EVENTOS --------------------------------------------------------------------- */

int main()
{
    /* declaracoes de variaveis aqui */

    srand(0); /* use zero, nao faca com time (0) */

    /* coloque seu codigo aqui */

    return 0;
}

