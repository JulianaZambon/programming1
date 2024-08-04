#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "conjunto.h"
#include "lef.h"
#include "fila.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 100000
#define TAMANHO_DO_MUNDO 200
#define N_HABILIDADES 10
#define N_HEROIS 50
#define N_BASES 8
#define N_MISSOES 5

/* EVENTOS --------------------------------------------------------------------- */
#define CHEGA 0
#define ESPERA 1
#define DESISTE 2
#define SAI 3
#define AVISA 4
#define ENTRA 5
#define VIAJA 6
#define MISSAO 7
#define FIM 8

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
    int tentativas; /* num de tentativas para cumprir a missao */
    bool cumprida;  /* indica se a missao foi cumprida ou nao */
};

/* definido pelas entidades acima*/
struct mundo
{
    int n_herois;           /* num total de herois no mundo*/
    struct heroi *herois;   /* vetor de herois */
    int n_bases;            /* num total de bases no mundo */
    struct base *bases;     /* vetor de bases */
    int n_missoes;          /* num total de missoes a cumprir */
    struct missao *missoes; /* vetor de missoes */
    int n_habilidades;      /* num total de habilidades distintas */
    int tamanho_do_mundo;
    int t_fim_do_mundo;
    int tempo_atual; /* tempo atual do mundo */
};

/* FUNÇÕES AUXILIARES ----------------------------------------------------------- */

/* calcula a distancia euclidiana entre dois pontos */
int distancia(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    int quadrado = dx * dx + dy * dy;
    return sqrt(quadrado);
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
    if (!(menor = cria_cjt(mundo->n_habilidades)))
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

        /* faz a uniao entre os conjuntos de habilidades de todos os herois prsentes na base atual*/
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

struct heroi inicializa_heroi(int id, int n_habilidades)
{
    struct heroi h;

    h.ID = id;
    h.experiencia = 0;
    h.paciencia = paciencia_do_heroi();
    h.velocidade = velocidade_heroi();

    struct conjunto *c = cria_cjt(n_habilidades);
    int i;
    for (i = 0; i < n_habilidades; i++)
        insere_cjt(c, i + 1);
    h.habilidades_heroi = cria_subcjt_cjt(c, aleat(1, 3));

    if (!(h.habilidades_heroi)) /* conjunto com tamanho aleatório [1...3] de habilidades aleatórias */
        exit(EXIT_FAILURE);

    destroi_cjt(c);
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

struct mundo *inicializa_mundo()
{
    int i;

    struct mundo *mundo = malloc(sizeof(struct mundo));
    if (!mundo)
    {
        fprintf(stderr, "Erro ao alocar memória para mundo\n");
        exit(EXIT_FAILURE);
    }

    mundo->tempo_atual = T_INICIO;
    mundo->t_fim_do_mundo = T_FIM_DO_MUNDO;
    mundo->tamanho_do_mundo = TAMANHO_DO_MUNDO;
    mundo->n_habilidades = N_HABILIDADES;
    mundo->n_herois = mundo->n_habilidades * 5;
    mundo->n_bases = mundo->n_herois / 6;
    mundo->n_missoes = mundo->t_fim_do_mundo / 100;

    mundo->herois = malloc(mundo->n_herois * sizeof(struct heroi));
    if (!(mundo->herois))
    {
        free(mundo);
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < mundo->n_herois; i++)
        mundo->herois[i] = inicializa_heroi(i, mundo->n_habilidades);

    mundo->bases = malloc(mundo->n_bases * sizeof(struct base));
    if (!(mundo->bases))
    {
        free(mundo->herois);
        free(mundo);
        exit(EXIT_FAILURE);
    }

    struct conjunto *c = cria_cjt(mundo->n_habilidades);
    for (i = 0; i < mundo->n_habilidades; i++)
        insere_cjt(c, i + 1);

    for (i = 0; i < mundo->n_bases; i++)
        mundo->bases[i] = inicializa_base(i, mundo->tamanho_do_mundo);

    mundo->missoes = malloc(sizeof(struct missao) * mundo->n_missoes);
    /* inicializa as missoes */
    for (i = 0; i < mundo->n_missoes; i++)
    {
        mundo->missoes[i].ID_missao = i;
        mundo->missoes[i].localX = aleat(0, mundo->tamanho_do_mundo - 1);
        mundo->missoes[i].localY = aleat(0, mundo->tamanho_do_mundo - 1);
        mundo->missoes[i].habilidades = cria_subcjt_cjt(c, aleat(6, 10));
        mundo->missoes[i].tentativas = 0;
        mundo->missoes[i].cumprida = false;
    }

    destroi_cjt(c);
    return mundo;
}
/*
Antes de iniciar a simulação, é necessário criar e inserir na LEF alguns eventos iniciais.
Esses eventos serão em seguida processados e poderão gerar novos eventos, o que fará avançar a simulação.
*/
void inicializa_eventos_iniciais(struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    int i;
    for (i = 0; i < mundo->n_herois; i++)
    {
        int base = aleat(0, mundo->n_bases - 1);
        int tempo = aleat(0, 4320); /* 4320 = 60*24*3 = 3 dias */
        struct evento_t *chegada_heroi = cria_evento(tempo, CHEGA, i, base);
        if (!chegada_heroi)
        {
            fprintf(stderr, "Erro ao criar evento de chegada\n");
            destroi_evento(chegada_heroi);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, chegada_heroi);
    }

    for (i = 0; i < mundo->n_missoes; i++)
    {
        int tempo = aleat(0, T_FIM_DO_MUNDO);
        struct evento_t *missao = cria_evento(tempo, MISSAO, i, 0);
        if (!missao)
        {
            fprintf(stderr, "Erro ao criar evento de missao\n");
            destroi_evento(missao);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, missao);
    }

    struct evento_t *fim = cria_evento(T_FIM_DO_MUNDO, FIM, 0, 0);
    if (!fim)
    {
        fprintf(stderr, "Erro ao criar evento de fim\n");
        destroi_evento(fim);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, fim);
}

/* EVENTOS ---------------------------------------------------------------------- */

/*Representa um herói H chegando em uma base B no instante T.
Ao chegar, o herói analisa o tamanho da fila e decide se espera para entrar ou desiste

atualiza base de H
se há vagas em B e a fila de espera em B está vazia:
    espera = true
senão:
    espera = (paciência de H) > (10 * tamanho da fila em B)

se espera:
    cria e insere na LEF o evento ESPERA (agora, H, B)
senão:
    cria e insere na LEF o evento DESISTE (agora, H, B)
*/
void evento_chega(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    mundo->herois[IDHeroi].base_atual = IDBase; /* atualiza base de H */

    int espera = 0;
    if (!base_lotada(IDBase, mundo) && fila_vazia(mundo->bases[IDBase].espera))
        espera = 1;
    else
        espera = mundo->herois[IDHeroi].paciencia > 10 * fila_tamanho(mundo->bases[IDBase].espera);

    if (espera)
    {
        struct evento_t *espera = cria_evento(mundo->tempo_atual, ESPERA, IDHeroi, IDBase); /* cria e insere na LEF o evento ESPERA (agora, H, B) */

        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ESPERA\n", mundo->tempo_atual, IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes), mundo->bases[IDBase].lotacao);

        if (!espera)
        {
            fprintf(stderr, "Erro ao criar evento de espera\n");
            destroi_evento(espera);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, espera); /* insere na LEF o evento ESPERA */
    }
    else
    {
        struct evento_t *desiste = cria_evento(mundo->tempo_atual, DESISTE, IDHeroi, IDBase); /* cria e insere na LEF o evento DESISTE (agora, H, B) */

        printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) DESISTE\n", mundo->tempo_atual, IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes), mundo->bases[IDBase].lotacao);

        if (!desiste)
        {
            fprintf(stderr, "Erro ao criar evento de desiste\n");
            destroi_evento(desiste);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, desiste); /* insere na LEF o evento DESISTE */
    }
}

/*
O herói H entra na fila de espera da base B. Assim que H entrar na fila, o porteiro da base B deve ser avisado para verificar a fila:

ESPERA (T, H, B):
adiciona H ao fim da fila de espera de B
cria e insere na LEF o evento AVISA (agora, B)
*/
void evento_espera(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    enqueue(mundo->bases[IDBase].espera, IDHeroi);                                    /* adiciona H ao fim da fila de espera de B */
    struct evento_t *avisa = cria_evento(mundo->tempo_atual, AVISA, IDHeroi, IDBase); /* cria e insere na LEF o evento AVISA (agora, B) */

    printf("%6d: ESPERA HEROI %2d BASE %d\n", mundo->tempo_atual, IDHeroi, IDBase);

    if (!avisa)
    {
        fprintf(stderr, "Erro ao criar evento de avisa\n");
        destroi_evento(avisa);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, avisa); /* insere na LEF o evento AVISA */
}

/*
O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja para lá:

escolhe uma base destino D aleatória
cria e insere na LEF o evento VIAJA (agora, H, D)
*/
void evento_desiste(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    int IDBaseDestino = aleat(0, mundo->n_bases - 1);                                        /* escolhe uma base destino D aleatória */
    struct evento_t *viaja = cria_evento(mundo->tempo_atual, VIAJA, IDHeroi, IDBaseDestino); /* cria e insere na LEF o evento VIAJA (agora, H, D) */

    printf("%6d: DESIST HEROI %2d BASE %d\n", mundo->tempo_atual, IDHeroi, IDBase);

    if (!viaja)
    {
        fprintf(stderr, "Erro ao criar evento de viaja\n");
        destroi_evento(viaja);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, viaja); /* insere na LEF o evento VIAJA */
}

/*
O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o porteiro de B é avisado, pois uma vaga foi liberada:

retira H do conjunto de heróis presentes em B
escolhe uma base destino D aleatória
cria e insere na LEF o evento VIAJA (agora, H, D)
cria e insere na LEF o evento AVISA (agora, B)
*/
void evento_sai(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    /* escolhe uma base destino D aleatória */
    int IDBaseDestino = aleat(0, mundo->n_bases - 1);

    retira_cjt(mundo->bases[IDBase].presentes, IDHeroi);                                     /* retira H do conjunto de heróis presentes em B */
    struct evento_t *viaja = cria_evento(mundo->tempo_atual, VIAJA, IDHeroi, IDBaseDestino); /* cria e insere na LEF o evento VIAJA (agora, H, D) */
    struct evento_t *avisa = cria_evento(mundo->tempo_atual, AVISA, IDHeroi, IDBase);        /* cria e insere na LEF o evento AVISA (agora, B) */

    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", mundo->tempo_atual, IDHeroi,
           IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes), mundo->bases[IDBase].lotacao);

    if (!viaja)
    {
        fprintf(stderr, "Erro ao criar evento VIAJA \n");
        destroi_evento(viaja);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, viaja); /* insere na LEF o evento VIAJA */

    if (!avisa)
    {
        fprintf(stderr, "Erro ao criar evento AVISA \n");
        destroi_evento(avisa);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, avisa); /* insere na LEF o evento AVISA */
}

/*
O porteiro da base B trata a fila de espera:

enquanto houver vaga em B e houver heróis esperando na fila:
    retira primeiro herói (H') da fila de B
    adiciona H' ao conjunto de heróis presentes em B
    cria e insere na LEF o evento ENTRA (agora, H', B)
*/
void evento_avisa(int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) FILA ", mundo->tempo_atual, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes), mundo->bases[IDBase].lotacao);
    fila_imprime(mundo->bases[IDBase].espera);

    while (!fila_vazia(mundo->bases[IDBase].espera) && !base_lotada(IDBase, mundo))
    {
        int IDHeroi = 0;
        dequeue(mundo->bases[IDBase].espera, &IDHeroi);                                   /* retira primeiro herói (H') da fila de B */
        insere_cjt(mundo->bases[IDBase].presentes, IDHeroi);                              /* adiciona H' ao conjunto de heróis presentes em B */
        struct evento_t *entra = cria_evento(mundo->tempo_atual, ENTRA, IDHeroi, IDBase); /* cria e insere na LEF o evento ENTRA (agora, H', B) */

        printf("%6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", mundo->tempo_atual, IDBase, IDHeroi);

        if (!entra)
        {
            fprintf(stderr, "Erro ao criar evento de entra\n");
            destroi_evento(entra);
            exit(EXIT_FAILURE);
        }
        insere_lef(lista_de_eventos, entra); /* insere na LEF o evento ENTRA */
    }
}

/*
O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e agenda sua saída da base:

calcula TPB = tempo de permanência na base:
    TPB = 15 + paciência de H * aleatório [1...20]
cria e insere na LEF o evento SAI (agora + TPB, H, B)
*/
void evento_entra(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    int TPB = 15 + mundo->herois[IDHeroi].paciencia * aleat(1, 20);                     /* calcula TPB = tempo de permanência na base */
    struct evento_t *sai = cria_evento(mundo->tempo_atual + TPB, SAI, IDHeroi, IDBase); /* cria e insere na LEF o evento SAI (agora + TPB, H, B) */

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", mundo->tempo_atual,
           IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes), mundo->bases[IDBase].lotacao, mundo->tempo_atual + TPB);

    if (!sai)
    {
        fprintf(stderr, "Erro ao criar evento SAI\n");
        destroi_evento(sai);
        exit(EXIT_FAILURE);
    }
    insere_lef(lista_de_eventos, sai); /* insere na LEF o evento SAI */
}

/*
O herói H se desloca para uma base D (que pode ser a mesma onde já está):
VIAJA (T, H, D):

calcula duração da viagem:
    distância = distância cartesiana entre a base atual de H e a base D
    duração = distância / velocidade de H
cria e insere na LEF o evento CHEGA (agora + duração, H, D)

saída:
%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d
*/
void evento_viaja(int IDHeroi, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    /* O herói H se desloca para uma base D (que pode ser a mesma onde já está) */
    struct heroi heroi = mundo->herois[IDHeroi];
    struct base base = mundo->bases[heroi.base_atual];
    int IDBaseDestino = aleat(0, mundo->n_bases - 1);
    struct base base_destino = mundo->bases[IDBaseDestino];

    int dist = 0;
    int duracao = 0;
    int velocidade = heroi.velocidade;

    duracao = dist / velocidade;

    if (IDBaseDestino == base.ID_base)
    {
        duracao = 0;
    }
    else
    {
        dist = distancia(base.localX, base.localY, base_destino.localX, base_destino.localY);
        duracao = dist / velocidade;
    }

    int tempo_chega = mundo->tempo_atual + duracao;
    /* cria e insere na LEF o evento CHEGA (agora + duração, H, D) */
    struct evento_t *chega;
    chega = cria_evento(tempo_chega, CHEGA, IDHeroi, IDBaseDestino);

    /* erro */
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
           mundo->tempo_atual, IDHeroi, base.ID_base, base_destino.ID_base, dist, velocidade, tempo_chega);

    if (!chega)
        exit(EXIT_FAILURE);

    insere_lef(lista_de_eventos, chega);
}

/*
MISSAO (T, M):
calcula a distância de cada base ao local da missão M
encontra BMP = base mais próxima da missão cujos heróis possam cumpri-la
se houver uma BMP:
    incrementa a experiência dos heróis presentes na base BMP
senão:
    cria e insere na LEF o evento MISSAO (T + 24*60, M) para o dia seguinte
*/

void evento_missao(int IDMissao, struct mundo *mundo, struct evento_t *evento, struct lef_t *lista_de_eventos)
{
    int i;
    mundo->missoes[IDMissao].tentativas++;

    struct missao missao = mundo->missoes[IDMissao];
    struct base *base_mais_proxima = NULL;
    int menor_distancia = 987654321; /* valor grande para representar infinito */

    printf("%6d: MISSAO %d TENT %d HAB REQ: ", mundo->tempo_atual, IDMissao, mundo->missoes[IDMissao].tentativas);
    imprime_cjt(missao.habilidades);

    /* percorre todas as bases para encontrar a base mais próxima */
    for (i = 0; i < mundo->n_bases; i++)
    {
        int dist = distancia(mundo->bases[i].localX, mundo->bases[i].localY, missao.localX, missao.localY);

        if (dist < menor_distancia)
        {
            menor_distancia = dist;
            base_mais_proxima = &mundo->bases[i];
        }
    }

    if (base_mais_proxima)
    {
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [", mundo->tempo_atual, IDMissao, base_mais_proxima->ID_base, menor_distancia);
        inicia_iterador_cjt(base_mais_proxima->presentes);
        int IDHeroi;
        while (incrementa_iterador_cjt(base_mais_proxima->presentes, &IDHeroi))
        {
            printf("%d ", IDHeroi);
        }
        printf("]\n");

        struct conjunto *equipe = escolhe_menor_equipe(*missao.habilidades, IDMissao, mundo, base_mais_proxima);
        if (equipe)
        {
            printf("%6d: MISSAO %d HAB HEROI %2d: ", mundo->tempo_atual, IDMissao, IDHeroi);
            imprime_cjt(equipe); /* imprime as habilidades da equipe */

            printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", mundo->tempo_atual, IDMissao, base_mais_proxima->ID_base);
            imprime_cjt(base_mais_proxima->presentes);

            /* incrementa a experiência dos heróis */
            inicia_iterador_cjt(base_mais_proxima->presentes);
            while (incrementa_iterador_cjt(base_mais_proxima->presentes, &IDHeroi))
            {
                mundo->herois[IDHeroi].experiencia++;
            }
            printf("%6d: MISSAO %d CUMPRIDA BASE %d\n", mundo->tempo_atual, IDMissao, base_mais_proxima->ID_base);
            missao.cumprida = true;
        }
        else
        {
            /* Se não houver equipe disponível, reagenda a missão para o dia seguinte */
            cria_evento(mundo->tempo_atual + 24 * 60, MISSAO, IDMissao, evento->dado2);
            insere_lef(lista_de_eventos, evento);
            printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->tempo_atual, IDMissao);
        }
    }
    else
    {
        /* Se não houver base mais próxima, reagenda a missão para o dia seguinte */
        cria_evento(mundo->tempo_atual + 24 * 60, 1, MISSAO, evento->dado2);
        insere_lef(lista_de_eventos, evento);
        printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->tempo_atual, IDMissao);
    }
}

/*
FIM (T):
  apresenta as experiências dos heróis
  apresenta as estatísticas das missões
  encerra a simulação
*/
void evento_fim(struct mundo *mundo, struct lef_t **lista_de_eventos)
{
    int i;
    /* informaçõe sobre herois */
    for (i = 0; i < mundo->n_herois; i++)
    {
        printf("HEROI %2d PAC %2d VEL %d EXP %d HABS ", i, mundo->herois[i].paciencia,
               mundo->herois[i].velocidade, mundo->herois[i].experiencia);
        imprime_cjt(mundo->herois[i].habilidades_heroi);
    }

    /* informacoes sobre missoes */
    int missao_cumprida = 0;
    int min_tentativas = 987654321;
    int max_tentativas = 0;
    int total_tentativas = 0;

    for (i = 0; i < mundo->n_missoes; i++)
    {
        if (contido_cjt(mundo->missoes[i].habilidades, mundo->bases[i].presentes)) /* se as habilidades dos presentes na base contem as habilidades da missao */
            missao_cumprida++;
        if (mundo->missoes[i].tentativas < min_tentativas)
            min_tentativas = mundo->missoes[i].tentativas;
        if (mundo->missoes[i].tentativas > max_tentativas)
            max_tentativas = mundo->missoes[i].tentativas;
        total_tentativas += mundo->missoes[i].tentativas;
    }

    printf("MISSOES CUMPRIDAS: %d/%d (%.2f%%)\n", missao_cumprida, mundo->n_missoes, (float)missao_cumprida / mundo->n_missoes * 100);
    printf("TENTATIVAS/MISSAO: MIN %d MAX %d MEDIA %.2f\n", min_tentativas, max_tentativas, (float)total_tentativas / mundo->n_missoes);

    destroi_lef(*lista_de_eventos);
    *lista_de_eventos = NULL;
}

/* MAIN ------------------------------------------------------------------------ */
int main()
{
    srand(time(0));

    struct lef_t *lista_de_eventos = cria_lef(); /* cria a lista de eventos futuros */
    struct mundo *mundo = inicializa_mundo();    /* inicializa o mundo */

    if (!(mundo) || !(lista_de_eventos))
        exit(EXIT_FAILURE);

    inicializa_eventos_iniciais(mundo, lista_de_eventos); /* inicializa os eventos iniciais */

    mundo->tempo_atual = T_INICIO;

    evento_viaja(15, mundo, lista_de_eventos);

    /* ciclo da simulação */
    while (lista_de_eventos)
    {
        struct evento_t *evento;
        evento = retira_lef(lista_de_eventos);
        mundo->tempo_atual = evento->tempo;

        switch (evento->tipo)
        {
        case CHEGA:
            evento_chega(evento->dado1, evento->dado2, mundo, lista_de_eventos);
            break;
        case ESPERA:
            evento_espera(evento->dado1, evento->dado2, mundo, lista_de_eventos);
            break;
        case DESISTE:
            evento_desiste(evento->dado1, evento->dado2, mundo, lista_de_eventos);
            break;
        case SAI:
            evento_sai(evento->dado1, evento->dado2, mundo, lista_de_eventos);
            break;
        case AVISA:
            evento_avisa(evento->dado2, mundo, lista_de_eventos);
            break;
        case ENTRA:
            evento_entra(evento->dado1, evento->dado2, mundo, lista_de_eventos);
            break;
        case VIAJA:
            evento_viaja(evento->dado1, mundo, lista_de_eventos);
            break;
        case MISSAO:
            evento_missao(evento->dado1, mundo, evento, lista_de_eventos);
            break;
        case FIM:
            evento_fim(mundo, &lista_de_eventos);
            break;
        }
        destroi_evento(evento);
    }

    destroi_lef(lista_de_eventos); /* destroi a lista de eventos */
    int i;
    for (i = 0; i < mundo->n_bases; i++)
    {
        destroi_cjt(mundo->bases[i].presentes);
        fila_destroi(&mundo->bases[i].espera);
    }
    free(mundo->bases);
    for (i = 0; i < mundo->n_herois; i++)
        destroi_cjt(mundo->herois[i].habilidades_heroi);
    free(mundo->herois);
    for (i = 0; i < mundo->n_missoes; i++)
        destroi_cjt(mundo->missoes[i].habilidades);
    free(mundo->missoes);
    free(mundo);
    return 0;
}
