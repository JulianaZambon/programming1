#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "conjunto.h"
#include "lef.h"
#include "fila.h"

#define TAMANHO_DO_MUNDO 20000
#define FIM_DO_MUNDO 34944

/* EVENTOS --------------------------------------------------------------------- */
#define CHEGADA 0
#define SAIDA 1
#define MISSAO 2
#define FIM 3

/* STRUCTS H, B, M, W ----------------------------------------------------------- */
struct heroi
{
    int ID;                             /* num inteiro que identifica unicamente o heroi */
    struct conjunto *habilidades_heroi; /* cada habilidade eh representada por um num inteiro */
    int paciencia;                      /* um num inteiro que indica o quao paciente a pessoa eh e isso afeta a permanencia em bases e filas */
    int velocidade;                     /* num inteiro indica a velocidade de deslocamento, logo afeta o tempo */
    int experiencia;                    /* num inteiro que indica o num de missoes que o heroi ja participou */
    int base_atual;                     /* num inteiro que indica a base a qual o heroi se encontra no momento */
};

struct base
{
    int ID_base;                /* num inteiro que identifica a base */
    int lotacao;                /* num de herois naquela base */
    struct conjunto *presentes; /* conjunto dos IDs dos herois presentes na base */
    struct fila *espera;        /* fila de herois esperando na base */
    int localX;                 /* localizacao da base (par de coordenadas inteiras X, Y ≥ 0) */
    int localY;
};

struct missao
{
    int ID_missao;                /* num inteiro que identifica unicamente a missao */
    struct conjunto *habilidades; /* conjunto de habilidades necessarias para a missao */
    int localX;                   /* localizacao da missao (par de coordenadas inteiras X, Y ≥ 0) */
    int localY;
};

/* definido pelas entidades acima*/
struct mundo
{
    int n_herois;                    /* num total de herois no mundo*/
    struct heroi *herois;            /* vetor de herois */
    int n_bases;                     /* num total de bases no mundo */
    struct base *bases;              /* vetor de bases */
    int n_missoes;                   /* num total de missoes a cumprir */
    struct missao *Missoes;          /* vetor de missoes */
    struct conjunto *cj_habilidades; /* num total de habilidades distintas */
    int tamanho_do_mundo;
    int fim_do_mundo;
    int tempo_atual; /* tempo atual do mundo */
};

/* FUNÇÕES AUXILIARES ----------------------------------------------------------- */

/* calcula a distancia entre dois pontos */
int distancia(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); /* distancia euclidiana */
}

/* numero aleatorio */
int aleat(int a, int b)
{
    return rand() % b + 1 + a;
}

int max(int a, int b)
{
    return a > b ? a : b; /* retorna o maior valor */
}

int base_lotada(int ID_base, struct mundo *mundo)
{
    return cardinalidade_cjt(mundo->bases[ID_base].presentes) >= mundo->bases[ID_base].lotacao;
}

int paciencia_do_heroi()
{
    return aleat(0, 100);
}

int velocidade_heroi()
{
    return aleat(50, 5000); /* velocidade em metros por minuto = 3Km/h a 300Km/h */
}

struct conjunto *escolhe_menor_equipe(struct conjunto missao, int ID_missao, struct mundo *mundo, struct base *base_encontrada)
{
    struct conjunto *menor;
    if (!(menor = cria_cjt(cardinalidade_cjt(mundo->cj_habilidades))))
        return NULL;

    struct conjunto *antiga_uniao;
    struct conjunto *uniao;

    int i, j, ID_heroi_atual;

    for (i = 0; i < mundo->n_bases; i++)
    {
        if (vazio_cjt(mundo->bases[i].presentes))
            continue;

        /* copia o conjunto de habilidades do primeiro heroi da base atual */
        inicia_iterador_cjt(mundo->bases[i].presentes);
        incrementa_iterador_cjt(mundo->bases[i].presentes, &ID_heroi_atual);

        if (!(uniao = copia_cjt(mundo->herois[ID_heroi_atual].habilidades_heroi)))
            return NULL;

        /* faz a uniao entre os conjutnos de habilidades de todos os herois prsentes na base atual*/
        for (j = 1; j < cardinalidade_cjt(mundo->bases[i].presentes); j++)
        {
            antiga_uniao = uniao;
            incrementa_iterador_cjt(mundo->bases[i].presentes, &ID_heroi_atual);
            uniao = uniao_cjt(antiga_uniao, mundo->herois[ID_heroi_atual].habilidades_heroi);
            antiga_uniao = destroi_cjt(antiga_uniao);
        }

        printf("%6d:MISSAO %3d HAB_EQL %d:", mundo->tempo_atual, ID_missao, mundo->bases[i].ID_base);
        imprime_cjt(uniao);

        /* compara se o conjunto construido contem a missao e se eh menor que o encontrado antes */
        if (contido_cjt(&missao, uniao))
        {
            if (vazio_cjt(menor) || cardinalidade_cjt(uniao) < cardinalidade_cjt(menor))
            {
                menor = destroi_cjt(menor);
                if (!(menor = copia_cjt(uniao)))
                    return NULL;
                *base_encontrada = mundo->bases[i];
            }
        }
        uniao = destroi_cjt(uniao);
    }
    return menor;
}

/* FUNÇÕES DE INCIALIZACAO ------------------------------------------------------ */

struct heroi inicializa_heroi(int ID, struct conjunto *habilidades)
{
    struct heroi h;

    h.ID = ID;
    h.paciencia = aleat(0, 100);
    h.experiencia = 0;

    if (!(h.habilidades_heroi = cria_subcjt_cjt(habilidades, aleat(1, 3)))) /* conjunto com tamanho aleatório [1...3] de habilidades aleatórias */
        exit(EXIT_FAILURE);

    return h;
}

struct base inicializa_base(int ID, int tamanho_do_mundo)
{
    struct base b;

    b.ID_base = ID;
    b.lotacao = aleat(3, 10); /* número aleatório [3...10] */

    if (!(b.presentes = cria_cjt(b.lotacao)))
        exit(EXIT_FAILURE);

    if (!(b.espera = fila_cria()))
        exit(EXIT_FAILURE);

    b.localX = aleat(0, tamanho_do_mundo - 1);
    b.localY = aleat(0, tamanho_do_mundo - 1);

    return b;
}

struct mundo *inicializa_mundo(struct lef_t *lista_de_eventos)
{
    struct mundo *mundo = malloc(sizeof(struct mundo));
    if (!mundo)
        exit(EXIT_FAILURE);

    mundo->tempo_atual = 0;
    mundo->tamanho_do_mundo = TAMANHO_DO_MUNDO;
    mundo->fim_do_mundo = FIM_DO_MUNDO;
    mundo->n_missoes = mundo->fim_do_mundo / 100;

    const int habilidades = 10;
    int i;

    mundo->cj_habilidades = cria_cjt(habilidades);
    if (!mundo->cj_habilidades)
    {
        free(mundo);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < habilidades; i++)
        insere_cjt(mundo->cj_habilidades, i);

    mundo->n_herois = habilidades * 5;
    mundo->n_bases = mundo->n_herois / 6;

    mundo->herois = malloc(mundo->n_herois * sizeof(struct heroi));
    if (!mundo->herois)
    {
        destroi_cjt(mundo->cj_habilidades);
        free(mundo);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < mundo->n_herois; i++)
        mundo->herois[i] = inicializa_heroi(i, mundo->cj_habilidades);

    mundo->bases = malloc(mundo->n_bases * sizeof(struct base));
    if (!mundo->bases)
    {
        free(mundo->herois);
        destroi_cjt(mundo->cj_habilidades);
        free(mundo);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < mundo->n_bases; i++)
        mundo->bases[i] = inicializa_base(i, mundo->tamanho_do_mundo);

    for (i = 0; i < mundo->n_herois; i++)
    {
        struct evento_t *chegada_heroi = cria_evento(aleat(0, mundo->fim_do_mundo), CHEGADA, i, aleat(0, mundo->n_bases - 1));
        if (!chegada_heroi)
        {
            fprintf(stderr, "Erro ao criar evento de chegada\n");
            free(mundo->bases);
            free(mundo->herois);
            destroi_cjt(mundo->cj_habilidades);
            free(mundo);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, chegada_heroi);
    }

    struct evento_t *fim = malloc(sizeof(struct evento_t));
    if (!fim)
    {
        fprintf(stderr, "Erro ao criar evento de fim\n");
        free(mundo->bases);
        free(mundo->herois);
        destroi_cjt(mundo->cj_habilidades);
        free(mundo);
        exit(EXIT_FAILURE);
    }
    fim->tempo = mundo->fim_do_mundo;
    fim->tipo = FIM;
    fim->dado1 = 0;
    fim->dado2 = 0;
    insere_lef(lista_de_eventos, fim);

    return mundo;
}

/* EVENTOS ---------------------------------------------------------------------- */
/* Os eventos implementam as mudanças de estado que fazem evoluir a simulação.
Cada evento tem um instante de ocorrência, pode consultar e alterar variáveis
(atributos das entidades) e pode criar outros eventos no presente ou no futuro.
*/

void evento_chegada(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    printf("%6d:CHEGA HEROI %2d Local %d (%2d/%2d), ",
           mundo->tempo_atual, IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes),
           mundo->bases[IDBase].lotacao);

    if (base_lotada(IDBase, mundo)) /* se a base estiver lotada */
    {
        if (paciencia_do_heroi() > 50) /* se a paciencia do heroi for maior que 50 */
        {
            enqueue(mundo->bases[IDBase].espera, IDHeroi); /* coloca o heroi na fila de espera */
            printf("FILA %d\n", fila_tamanho(mundo->bases[IDBase].espera));
            return;
        }

        printf("DESISTE\n");
        struct evento_t saida = {mundo->tempo_atual, SAIDA, IDHeroi, IDBase}; /* cria um evento de saida para o heroi */
        insere_lef(lista_de_eventos, &saida);
        return;
    }

    printf("ENTRA\n");
    insere_cjt(mundo->bases[IDBase].presentes, IDHeroi);                                           /* insere o heroi na base */
    int tempo_permanencia_base = max(1, mundo->herois[IDHeroi].paciencia / 10 + aleat(-2, 6));     /* calcula o tempo de permanencia do heroi na base */
    struct evento_t saida = {mundo->tempo_atual + tempo_permanencia_base, SAIDA, IDHeroi, IDBase}; /* cria um evento de saida para o heroi */
    insere_lef(lista_de_eventos, &saida);                                                          /* insere o evento na lista de eventos */
}

/*  O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar;
o porteiro de B é avisado, pois uma vaga foi liberada: */
void evento_saida(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    printf("%6d:SAIDA HEROI %2d Local %d (%2d/%2d)",
           mundo->tempo_atual, IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes),
           mundo->bases[IDBase].lotacao);

    if (pertence_cjt(mundo->bases[IDBase].presentes, IDHeroi)) /* se o heroi estiver presente na base */
    {
        retira_cjt(mundo->bases[IDBase].presentes, IDHeroi);
        if (!(fila_vazia(mundo->bases[IDBase].espera))) /* se a fila nao estiver vazia */
        {
            int ID_heroi_fila;
            dequeue(mundo->bases[IDBase].espera, &ID_heroi_fila); /* retira o heroi da fila */
            printf(", REMOVE FILA HEROI %d", ID_heroi_fila);
            struct evento_t chegada_heroi_fila = {mundo->tempo_atual, CHEGADA, ID_heroi_fila, IDBase}; /* cria um evento de chegada para o heroi retirado da fila */
            insere_lef(lista_de_eventos, &chegada_heroi_fila);                                         /* insere o evento na lista de eventos */
        }
    }
    printf("\n");

    int destino = aleat(0, mundo->n_bases - 1);
    int tempo_viagem = distancia(mundo->bases[IDBase].localX, mundo->bases[IDBase].localY,
                                 mundo->bases[destino].localX, mundo->bases[destino].localY) /
                       velocidade_heroi();
    struct evento_t chegada = {mundo->tempo_atual + tempo_viagem, CHEGADA, IDHeroi, destino};
    insere_lef(lista_de_eventos, &chegada);
}

/*  Calcula a distância de cada base ao local da missão M
    encontra BMP = base mais próxima da missão cujos heróis possam cumpri-la
se houver uma BMP:
    incrementa a experiência dos heróis presentes na base BMP
senão:
    cria e insere na LEF o evento MISSAO (T + 24*60, M) para o dia seguinte
*/
void evento_missao(int IDMissao, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    struct conjunto *missao;
    if (!(missao = cria_subcjt_cjt(mundo->cj_habilidades, aleat(3, 6))))
        exit(EXIT_FAILURE);

    printf("%6d:MISSAO %3d HAB_REQ ", mundo->tempo_atual, IDMissao);
    imprime_cjt(missao);

    struct base base_encontrada;
    struct conjunto *equipe_escolhida = escolhe_menor_equipe(*missao, IDMissao, mundo, &base_encontrada);

    printf("%6d:MISSAO %3d ", mundo->tempo_atual, IDMissao);
    if (vazio_cjt(equipe_escolhida)) /* se nao houver equipe apta */
    {
        printf("IMPOSSIVEL\n");
        /* Cria um evento de nova tentativa para o dia seguinte */
        struct evento_t nova_tentativa = {mundo->tempo_atual + 24 * 60, MISSAO, IDMissao, 0};
        insere_lef(lista_de_eventos, &nova_tentativa);
    }
    else /* se houver equipe apta */
    {
        printf("HER_EQS %d:", base_encontrada.ID_base);
        imprime_cjt(base_encontrada.presentes); /* imprime os herois presentes na base escolhida */

        int ID_heroi_encontrado;
        inicia_iterador_cjt(base_encontrada.presentes);
        int i;
        for (i = 0; i < cardinalidade_cjt(base_encontrada.presentes); i++) /* incrementa a experiencia dos herois presentes na base escolhida */
        {
            incrementa_iterador_cjt(base_encontrada.presentes, &ID_heroi_encontrado);
            if (ID_heroi_encontrado >= 0 && ID_heroi_encontrado < mundo->n_herois)
            {
                mundo->herois[ID_heroi_encontrado].experiencia++;
            }
            else
            {
                fprintf(stderr, "ID do herói inválido: %d\n", ID_heroi_encontrado);
            }
        }
    }

    /* Libera memória dos conjuntos */
    missao = destroi_cjt(missao);
    equipe_escolhida = destroi_cjt(equipe_escolhida);
}

/* encerra a simulacao no instante T */
void evento_fim(struct mundo *mundo, struct lef_t **lista_de_eventos)
{
    printf("%6d:FIM\n", mundo->tempo_atual); /* imprime o fim do mundo */
    int i;

    for (i = 0; i < mundo->n_herois; i++) /* imprime a experiencia de cada heroi */
    {
        printf("HEROI %2d EXPERIENCIA %2d\n", mundo->herois[i].ID, mundo->herois[i].experiencia);
        mundo->herois[i].habilidades_heroi = destroi_cjt(mundo->herois[i].habilidades_heroi); /* destroi os conjuntos de habilidades */
    }

    for (i = 0; i < mundo->n_bases; i++)
    {
        mundo->bases[i].presentes = destroi_cjt(mundo->bases[i].presentes); /* destroi os conjuntos de herois presentes */
        fila_destroi(&mundo->bases[i].espera);                              /* destroi as filas de espera */
    }

    /* libera memoria */
    free(mundo->herois);
    free(mundo->bases);
    mundo->cj_habilidades = destroi_cjt(mundo->cj_habilidades);
    free(mundo);
    *lista_de_eventos = destroi_lef(*lista_de_eventos);
}

/* MAIN ------------------------------------------------------------------------ */
int main()
{
    srand(time(0));

    struct lef_t *lista_de_eventos;
    if (!(lista_de_eventos = cria_lef()))
        exit(EXIT_FAILURE);

    struct mundo *mundo = inicializa_mundo(lista_de_eventos); /* inicializa o mundo */

    struct evento_t *evento_atual;

    /* ciclo da simulação */
    while (lista_de_eventos && (evento_atual = retira_lef(lista_de_eventos))) /* enquanto houver eventos */
    {
        mundo->tempo_atual = evento_atual->tempo; /* atualiza o tempo do mundo */

        switch (evento_atual->tipo)
        {
        case CHEGADA:
            evento_chegada(evento_atual->dado1, evento_atual->dado2, mundo, lista_de_eventos);
            break;

        case SAIDA:
            evento_saida(evento_atual->dado1, evento_atual->dado2, mundo, lista_de_eventos);
            break;

        case MISSAO:
            evento_missao(evento_atual->dado1, mundo, lista_de_eventos);
            break;

        case FIM:
            evento_fim(mundo, &lista_de_eventos);
            break;
        }
    }
    destroi_lef(lista_de_eventos); /* destroi a lista de eventos */
    return 0;
}
