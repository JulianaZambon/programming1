#include <stdio.h>
#include <stdlib.h>
#include "lef.h"

struct evento_t *cria_evento(int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *e = (struct evento_t *)malloc(sizeof(struct evento_t));
    if (e)
    {
        e->tempo = tempo;
        e->tipo = tipo;
        e->dado1 = dado1;
        e->dado2 = dado2;
    }
    return e;
}

struct evento_t *destroi_evento(struct evento_t *e)
{
    if (e)
        free(e);
    return NULL;
}

struct lef_t *cria_lef()
{
    struct lef_t *l = (struct lef_t *)malloc(sizeof(struct lef_t));

    if (l)
        l->primeiro = NULL; // inicializa a lista vazia

    return l;
}

struct lef_t *destroi_lef(struct lef_t *l)
{
    struct nodo_lef_t *p, *q;

    if (l)
    {
        p = l->primeiro; 
        while (p)
        {
            q = p;
            p = p->prox;
            destroi_evento(q->evento);
            free(q);
        }
        free(l);
    }

    return NULL;
}

int insere_lef(struct lef_t *l, struct evento_t *e)
{
    struct nodo_lef_t *novo, *p, *q;
    novo = (struct nodo_lef_t *)malloc(sizeof(struct nodo_lef_t));

    if (!novo)
        return 0;

    novo->evento = e;

    if (!l->primeiro)
    {
        l->primeiro = novo;
        novo->prox = NULL;
    }
    else
    {
        p = l->primeiro;
        q = NULL;
        while (p && p->evento->tempo <= e->tempo)
        {
            q = p;
            p = p->prox;
        }
        if (!q)
        {
            novo->prox = l->primeiro;
            l->primeiro = novo;
        }
        else
        {
            q->prox = novo;
            novo->prox = p;
        }
    }
    return 1;
}

struct evento_t *retira_lef(struct lef_t *l)
{
    struct nodo_lef_t *p;
    struct evento_t *e;

    if (!l->primeiro)
        return NULL;

    p = l->primeiro;
    l->primeiro = p->prox;
    e = p->evento;
    free(p);
    return e;
}

int vazia_lef(struct lef_t *l)
{
    return l->primeiro == NULL;
}

void imprime_lef(struct lef_t *l)
{
    struct nodo_lef_t *p;
    int total = 0;
    p = l->primeiro;

    while (p)
    {
        printf("%d %d %d %d\n", p->evento->tempo, p->evento->tipo, p->evento->dado1, p->evento->dado2);
        p = p->prox;
        total++;
    }
    
    printf("total %d eventos\n", total);
}
