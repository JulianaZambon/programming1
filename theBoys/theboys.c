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
    int Relogio; /* tempo atual do mundo */
};

/* FUNÇÕES AUXILIARES ----------------------------------------------------------- */

/* distancia entre dois pontos */
int distancia(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int sorteia(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int base_cheia(struct base *b)
{
    return b->lotacao == b->espera->tamanho;
}

int paciencia_heroi(struct heroi *h)
{
}

/* FUNÇÕES DE INCIALIZACAO ------------------------------------------------------ */

struct heroi inicializa_heroi()
{
    struct heroi h;

    /* code here */

    return h;
}

struct base inicializa_base()
{
    struct base b;

    /* code here */

    return b;
}

struct mundo inicializa_mundo()
{
    struct mundo m;
    m.NHerois = N_HEROIS;
    m.Herois = (struct heroi *)malloc(m.NHerois * sizeof(struct heroi));
    if (!m.Herois)
    {
        fprintf(stderr, "Erro ao alocar memoria para herois.\n");
        return m;
    }
    m.NBases = N_BASES;
    m.Bases = (struct base *)malloc(m.NBases * sizeof(struct base));
    if (!m.Bases)
    {
        fprintf(stderr, "Erro ao alocar memoria para bases.\n");
        free(m.Herois);
        return m;
    }
    m.NMissoes = N_MISSOES;
    m.Missoes = (struct missao *)malloc(m.NMissoes * sizeof(struct missao));
    if (!m.Missoes)
    {
        fprintf(stderr, "Erro ao alocar memoria para missoes.\n");
        free(m.Herois);
        free(m.Bases);
        return m;
    }
    m.NHabilidades = N_HABILIDADES;
    m.TamanhoMundoX = m.TamanhoMundoY = N_TAMANHO_MUNDO;
    m.Relogio = T_INICIO;

    /* inicializa herois */
    for (int i = 0; i < m.NHerois; i++)
    {
        m.Herois[i] = inicializa_heroi();
    }

    /* inicializa bases */
    for (int i = 0; i < m.NBases; i++)
    {
        m.Bases[i] = inicializa_base();
    }

    /* inicializa missoes */
    for (int i = 0; i < m.NMissoes; i++)
    {
        m.Missoes[i].ID = i;
        m.Missoes[i].habilidades = cria_conjunto();
        if (!m.Missoes[i].habilidades)
        {
            fprintf(stderr, "Erro ao criar conjunto de habilidades para missao %d.\n", i);
            free(m.Herois);
            free(m.Bases);
            free(m.Missoes);
            return m;
        }

        int n_habilidades = MIN_HABILIDADES_MISSAO + rand() % (MAX_HABILIDADES_MISSAO - MIN_HABILIDADES_MISSAO + 1);
        for (int j = 0; j < n_habilidades; j++)
        {
            int habilidade = rand() % m.NHabilidades;
            if (!insere_cjt(m.Missoes[i].habilidades, habilidade))
            {
                fprintf(stderr, "Erro ao inserir habilidade %d na missao %d.\n", habilidade, i);
                destroi_conjunto(m.Missoes[i].habilidades);
                free(m.Herois);
                free(m.Bases);
                free(m.Missoes);
                return m;
            }
        }

        m.Missoes[i].localX = MIN_X_MISSAO + rand() % (MAX_X_MISSAO - MIN_X_MISSAO + 1);
        m.Missoes[i].localY = MIN_Y_MISSAO + rand() % (MAX_Y_MISSAO - MIN_Y_MISSAO + 1);
    }

    return m;
}

/* EVENTOS ---------------------------------------------------------------------- */

void evento_chegada(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    /* Formato da saída */
    printf("%6d:CHEGA HEROI %2d Local %d (%2d/%2d), ",
           mundo->Relogio,
           IDHeroi,
           IDBase,
           cardinalidade_cjt(mundo->Bases[IDBase].presentes),
           mundo->Bases[IDBase].lotacao);

    /* Se a base não estiver cheia */
    if (!base_cheia(&mundo->Bases[IDBase]))
    {
        insere_cjt(mundo->Bases[IDBase].presentes, IDHeroi); /* Insere herói na base */
        printf("ENTRA\n");                                   /* Formato da saída */

        /* Calcula o tempo de permanência na base */
        int paciencia = paciencia_heroi(&mundo->Herois[IDHeroi]);
        int t_permanencia_base = 15 + paciencia * sorteia(1, 20);

        /* Cria um evento para a saída do herói da base */
        struct evento_t *saida = malloc(sizeof(struct evento_t));
        if (!saida)
        {
            fprintf(stderr, "Erro ao alocar memória para evento de saída.\n");
            exit(EXIT_FAILURE);
        }
        saida->tempo = mundo->Relogio + t_permanencia_base;
        saida->tipo = SAIDA;
        saida->dado1 = IDHeroi;
        saida->dado2 = IDBase;
        adiciona_ordem_lef(lista_de_eventos, saida);
    }
    else
    {
        /* Verifica a paciência do herói */
        if (paciencia_heroi(&mundo->Herois[IDHeroi]) > 0)
        {
            /*Evento ESPERA
            O herói H entra na fila de espera da base B. Assim que H entrar na fila, o porteiro da base B deve ser avisado para verificar a fila*/

            insere_fila(mundo->Bases[IDBase].espera, IDHeroi);              /* Insere herói na fila */
            printf("FILA %d\n", tamanho_fila(mundo->Bases[IDBase].espera)); /* Formato da saída */
        }
        else
        {
            printf("DESISTE\n"); /* Formato da saída */

            /* Evento DESISTE
            Cria um evento para o herói desistir e viajar para uma base aleatória */
            
            struct evento_t *saida = malloc(sizeof(struct evento_t));
            if (!saida)
            {
                fprintf(stderr, "Erro ao alocar memória para evento de saída.\n");
                exit(EXIT_FAILURE);
            }
            saida->tempo = mundo->Relogio;
            saida->tipo = SAIDA;
            saida->dado1 = IDHeroi;
            saida->dado2 = IDBase;
            adiciona_ordem_lef(lista_de_eventos, saida);
        }
    }
}

/*  O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar;
o porteiro de B é avisado, pois uma vaga foi liberada: */
void evento_saida(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    /* formato da saida */
    printf("%6d:SAIDA HEROI %2d Local %d (%2d/%2d)",
           mundo->Relogio,
           IDHeroi,
           IDBase,
           cardinalidade_cjt(mundo->Bases[IDBase].presentes),
           mundo->Bases[IDBase].lotacao);

    /* remove heroi da base */
    if (pertence_cjt(mundo->Bases[IDBase].presentes, IDHeroi))
    {
        retira_cjt(mundo->Bases[IDBase].presentes, IDHeroi); /* remove heroi da base */
        if (!vazia_fila(mundo->Bases[IDBase].espera))        /* se houver herois na fila */
        {
            int ID_heroi_fila;                                                                     /* pega o primeiro heroi da fila */
            retira_fila(mundo->Bases[IDBase].espera, &ID_heroi_fila);                              /* remove heroi da fila */
            printf(", REMOVE FILA HEROI %d", ID_heroi_fila);                                       /* formato da saida */
            struct evento_t chegada_heroi_fila = {mundo->Relogio, CHEGADA, ID_heroi_fila, IDBase}; /* cria evento de chegada do heroi */
            adiciona_inicio_lef(lista_de_eventos, &chegada_heroi_fila);                            /* adiciona evento na lista de eventos */
        }
    }
    printf("\n");

    /*Evento VIAJA
    O herói H se desloca para uma base D (que pode ser a mesma onde já está)*/

    int id_local_destino = aleat(0, mundo->NBases - 1);                                      /* sorteia uma base de destino */
    int t_deslocamento = distancia(mundo->Bases[IDBase].localX, mundo->Bases[IDBase].localY, /* calcula o tempo de deslocamento */
                                   mundo->Bases[id_local_destino].localX,
                                   mundo->Bases[id_local_destino].localY) /
                         velocidade_heroi(mundo->Herois[IDHeroi]);

    struct evento_t chegada_heroi = {mundo->Relogio + t_deslocamento / 15, CHEGADA, IDHeroi, id_local_destino}; /* cria evento de chegada do heroi */
    adiciona_ordem_lef(lista_de_eventos, &chegada_heroi);                                                       /* adiciona evento na lista de eventos */
}

void evento_missao(int IDMissao, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
}

void evento_fim(struct mundo *mundo, struct lef_t **lista_de_eventos)
{
}

/* MAIN ------------------------------------------------------------------------ */
int main()
{
    srand(time(0));

    struct lef_t *lista_de_eventos;
    if (!(lista_de_eventos = cria_lef()))
    {
        fprintf(stderr, "Erro ao criar lista de eventos.\n");
        return 1;
    }

    struct mundo mundo = inicializa_mundo();
    if (!mundo.Herois || !mundo.Bases || !mundo.Missoes)
    {
        fprintf(stderr, "Erro ao inicializar mundo.\n");
        destroi_lef(lista_de_eventos);
        return 1;
    }

    struct evento_t *evento;
    /* ciclo da simulação do theBoys */
    while (!vazia_lef(lista_de_eventos))
    {
        evento = retira_lef(lista_de_eventos);
        if (!evento)
        {
            fprintf(stderr, "Erro ao retirar evento da lista.\n");
            destroi_lef(lista_de_eventos);
            return 1;
        }

        switch (evento->tipo)
        {
        case CHEGADA:
            evento_chegada(evento->dado1, evento->dado2, &mundo, lista_de_eventos);
            break;
        case SAIDA:
            evento_saida(evento->dado1, evento->dado2, &mundo, lista_de_eventos);
            break;
        case MISSAO:
            evento_missao(evento->dado1, &mundo, lista_de_eventos);
            break;
        case FIM_SIMULACAO:
            evento_fim(&mundo, &lista_de_eventos);
            break;
        default:
            fprintf(stderr, "Evento desconhecido.\n");
            destroi_evento(evento);
            destroi_lef(lista_de_eventos);
            return 1;
        }
        destroi_evento(evento);
    }

    destroi_lef(lista_de_eventos);
    free(mundo.Herois);
    free(mundo.Bases);
    free(mundo.Missoes);
    return 0;
}

