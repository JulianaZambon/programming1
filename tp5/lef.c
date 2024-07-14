#include "lef.h"
#include <stdio.h>
#include <stdlib.h>

struct evento_t *cria_evento(int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *evento = (struct evento_t *)malloc(sizeof(struct evento_t));
    if (evento != NULL)
    {
        evento->tempo = tempo; 
        evento->tipo = tipo;
        evento->dado1 = dado1;
        evento->dado2 = dado2;
    }
    return evento;
}

struct evento_t *destroi_evento(struct evento_t *e)
{
    if (e != NULL)
        free(e);

    return NULL;
}

struct lef_t *cria_lef()
{
    struct lef_t *lef = (struct lef_t *)malloc(sizeof(struct lef_t));
    if (lef != NULL)
        lef->primeiro = NULL;

    return lef;
}

struct lef_t *destroi_lef(struct lef_t *l)
{
    if (l != NULL)
    {
        struct nodo_lef_t *atual = l->primeiro;
        while (atual != NULL)
        {
            struct nodo_lef_t *prox = atual->prox; 
            destroi_evento(atual->evento);
            free(atual);
            atual = prox;
        }
        free(l);
    }
    return NULL;
}

int insere_lef(struct lef_t *l, struct evento_t *e)
{
    if (l == NULL || e == NULL)
        return 0;

    struct nodo_lef_t *novo = (struct nodo_lef_t *)malloc(sizeof(struct nodo_lef_t));
    if (novo == NULL) 
        return 0;

    novo->evento = e;
    novo->prox = NULL;

    if (l->primeiro == NULL || l->primeiro->evento->tempo > e->tempo) /* insere no inicio */
    {
        novo->prox = l->primeiro; /* aponta para o primeiro */
        l->primeiro = novo;      /* novo é o primeiro */
        return 1;
    }

    struct nodo_lef_t *atual = l->primeiro;
    while (atual->prox != NULL && atual->prox->evento->tempo <= e->tempo)
    {
        atual = atual->prox;
    }

    novo->prox = atual->prox;
    atual->prox = novo;

    return 1;
}

struct evento_t *retira_lef(struct lef_t *l)
{
    if (l == NULL || l->primeiro == NULL)
        return NULL;

    struct nodo_lef_t *remover = l->primeiro;  /* primeiro evento */
    struct evento_t *evento = remover->evento; /* evento a ser retornado */

    l->primeiro = l->primeiro->prox;
    free(remover);

    return evento;
}

int vazia_lef(struct lef_t *l)
{
    return (l == NULL || l->primeiro == NULL);
}

void imprime_lef(struct lef_t *l) {
    if (l == NULL || l->primeiro == NULL) {
        printf("LEF: \n");
        printf("  Total 0 eventos\n");
        return;
    }

    struct nodo_lef_t *atual = l->primeiro;
    int total_eventos = 0;

    printf("LEF: \n");
    while (atual != NULL) {
        printf("  tempo %d tipo %d d1 %d d2 %d\n", atual->evento->tempo, atual->evento->tipo,
               atual->evento->dado1, atual->evento->dado2);
        total_eventos++;
        atual = atual->prox;
    }

    printf("  Total %d eventos\n", total_eventos);
}
