#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "conjunto.h"
#include "lef.h"
#include "fila.h"

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
    int n_herois;           /* num total de herois no mundo*/
    struct heroi *herois;   /* vetor de herois */
    int n_bases;            /* num total de bases no mundo */
    struct base *bases;     /* vetor de bases */
    int n_missoes;          /* num total de missoes a cumprir */
    struct missao *Missoes; /* vetor de missoes */
    int *cj_habilidades;    /* num total de habilidades distintas */
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

int vazia_lef(struct lef_t *l)
{
    return (l == NULL || l->primeiro == NULL);
}

int base_lotada(int ID_base, struct mundo *mundo)
{
    return cardinalidade_cjt(mundo->bases[ID_base].presentes) >= mundo->bases[ID_base].lotacao;
}

int paciencia_do_heroi()
{
    return aleat(0,100);
}

int velocidade_heroi()
{
    return aleat(50, 5000); /* velocidade em metros por minuto = 3Km/h a 300Km/h */
}

struct conjunto *escolhe_menor_equipe(struct conjunto missao, int ID_missao, struct mundo *mundo, struct base *base_encontrada)
{
    struct conjunto *menor;
    if (!(menor = cria_cjt(cardinalidade_cjt(mundo->cj_habilidades))))
    {
        return NULL;
    }

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

    if (!(h.habilidades_heroi = cria_subcjt_cjt(habilidades, aleat(2, 5))))
        exit(EXIT_FAILURE);

    return h;
}

struct base inicializa_base(int ID, int tamanho_do_mundo)
{
    struct base b;

    b.ID_base = ID;
    b.lotacao = aleat(5, 30);

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
    struct mundo *mundo;
    mundo = malloc(sizeof(struct mundo));
    
    if (!mundo) {
        exit(EXIT_FAILURE);
    }

    mundo->tempo_atual = 0;
    mundo->tamanho_do_mundo = 20000;
    mundo->fim_do_mundo = 34944;
    mundo->n_missoes = mundo->fim_do_mundo / 100;

    const int habilidades = 10;
    if (!(mundo->cj_habilidades = cria_cjt(habilidades))) {
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < habilidades; i++) {
        insere_cjt(mundo->cj_habilidades, i);
    }

    mundo->n_herois = habilidades * 5;
    mundo->n_bases = mundo->n_herois / 6;

    /* cria um vetor de heróis e preenche ele */
    if (!(mundo->herois = malloc(mundo->n_herois * sizeof(struct heroi)))) {
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < mundo->n_herois; i++) {
        mundo->herois[i] = inicializa_heroi(i, mundo->cj_habilidades);
    }

    /* cria vetor de bases e preenche ele */
    if (!(mundo->bases = malloc(mundo->n_bases * sizeof(struct base)))) {
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < mundo->n_bases; i++) {
        mundo->bases[i] = inicializa_base(i, mundo->tamanho_do_mundo);
    }

    /* para cada heroi, cria um evento e insere na lef */
    for (i = 0; i < mundo->n_herois; i++) {
        struct evento_t *chegada_heroi = cria_evento(aleat(0, mundo->fim_do_mundo), CHEGADA, i, aleat(0, mundo->n_bases - 1));
        insere_lef(lista_de_eventos, chegada_heroi);
    }

    /* cria um evento de fim e insere na lef tbm */
    struct evento_t *fim = cria_evento(mundo->fim_do_mundo, FIM, 0, 0);
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

    if (base_lotada(IDBase, mundo))
    {
        if (paciencia_do_heroi(IDHeroi, mundo) > 50)
        {
            enqueue(mundo->bases[IDBase].espera, IDHeroi);
            printf("FILA %d\n", fila_tamanho(mundo->bases[IDBase].espera));
            return;
        }

        printf("DESISTE\n");
        struct evento_t saida = {mundo->tempo_atual, SAIDA, IDHeroi, IDBase};
        insere_lef(lista_de_eventos, &saida);
        return;
    }

    printf("ENTRA\n");
    insere_cjt(mundo->bases[IDBase].presentes, IDHeroi);
    int tempo_permanencia_base = max(1, mundo->herois[IDHeroi].paciencia / 10 + aleat(-2, 6));
    struct evento_t saida = {mundo->tempo_atual + tempo_permanencia_base, SAIDA, IDHeroi, IDBase};
    insere_lef(lista_de_eventos, &saida);
}

/*  O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar;
o porteiro de B é avisado, pois uma vaga foi liberada: */
void evento_saida(int IDHeroi, int IDBase, struct mundo *mundo, struct lef_t *lista_de_eventos)
{
    printf("%6d:SAIDA HEROI %2d Local %d (%2d/%2d)",
           mundo->tempo_atual, IDHeroi, IDBase, cardinalidade_cjt(mundo->bases[IDBase].presentes),
           mundo->bases[IDBase].lotacao);

    if (pertence_cjt(mundo->bases[IDBase].presentes, IDHeroi))
    {
        remove_cjt(mundo->bases[IDBase].presentes, IDHeroi);
        if (!(fila_vazia(mundo->bases[IDBase].espera)))
        {
            int ID_heroi_fila;
            dequeue(mundo->bases[IDBase].espera, &ID_heroi_fila);
            printf(", REMOVE FILA HEROI %d", ID_heroi_fila);
            struct evento_t chegada_heroi_fila = {mundo->tempo_atual, CHEGADA, ID_heroi_fila, IDBase};
            insere_lef(lista_de_eventos, &chegada_heroi_fila);
        }
    }
    printf("\n");

    int destino = aleat(0, mundo->n_bases - 1);
    int tempo_viagem = distancia(mundo->bases[IDBase].localX, mundo->bases[IDBase].localY,
                                 mundo->bases[destino].localX, mundo->bases[destino].localY) /
                       velocidade_heroi(&mundo->herois[IDHeroi]);
    struct evento_t chegada = {mundo->tempo_atual + tempo_viagem, CHEGADA, IDHeroi, destino};
    insere_lef(lista_de_eventos, &chegada);
}

/* Uma missão M é disparada no instante T. São características de uma missão:
    Cada missão ocorre em um local aleatório e requer um conjunto aleatório de habilidades; ambos são definidos durante a inicialização.
    Cada equipe é formada pelo conjunto de heróis presentes em uma base.
    Uma equipe está apta para a missão se a união das habilidades de seus heróis contém as habilidades requeridas pela missão.
    Deve ser escolhida para a missão a equipe da base mais próxima ao local da missão e que esteja apta para ela.
    Ao completar uma missão, os heróis da equipe escolhida ganham pontos de experiência.
    Se uma missão não puder ser completada, ela é marcada como “impossível” e adiada de 24 horas.
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
    if (vazio_cjt(equipe_escolhida))
    {
        printf("IMPOSSIVEL\n");
        struct evento_t nova_tentativa = {aleat(mundo->tempo_atual, mundo->fim_do_mundo), MISSAO, IDMissao, 0 };
        insere_lef(lista_de_eventos, &nova_tentativa);
    }
    else 
    {
        printf("HER_EQS %d:", base_encontrada.ID_base);
        imprime_cjt(base_encontrada.presentes);

        int ID_heroi_encontrado;
        inicia_iterador_cjt(base_encontrada.presentes);
        int i;
        for (i = 0; i < cardinalidade_cjt(base_encontrada.presentes); i++)
        {
            incrementa_iterador_cjt(base_encontrada.presentes, &ID_heroi_encontrado);
            mundo->herois[ID_heroi_encontrado].experiencia++;
        } 
    }
    missao = destroi_cjt(missao);
    equipe_escolhida = destroi_cjt(equipe_escolhida);
}

void evento_fim(struct mundo *mundo, struct lef_t **lista_de_eventos)
{
    printf("%6d:FIM\n", mundo->tempo_atual);
    int i;

    for (i = 0; i < mundo->n_herois; i++)
    {
        printf("HEROI %2d EXPERIENCIA %2d\n", mundo->herois[i].ID, mundo->herois[i].experiencia);
        mundo->herois[i].habilidades_heroi = destroi_cjt(mundo->herois[i].habilidades_heroi);
    }

    for (i = 0; i < mundo->n_bases; i++)
    {
        mundo->bases[i].presentes = destroi_cjt(mundo->bases[i].presentes);
        fila_destroi(&mundo->bases[i].espera);
    }

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

    struct mundo *mundo = inicializa_mundo(lista_de_eventos);

    struct evento_t *evento_atual;
    /* ciclo da simulação do the boys*/
    while (lista_de_eventos && (evento_atual = retira_lef(lista_de_eventos)))
    {
        mundo->tempo_atual = evento_atual->tempo;

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
            printf("%6d:FIM\n", mundo->tempo_atual);
            break;
        }

        free(evento_atual);
    }

    return 0;
}
