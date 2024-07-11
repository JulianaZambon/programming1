#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila *fila_cria()
{
    struct fila *f = (struct fila *)malloc(sizeof(struct fila));
    if (f)
    {
        f->ini = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

void fila_destroi(struct fila **fila)
{
    struct nodo *p, *q;
    if (*fila)
    {
        p = (*fila)->ini;
        while (p) // libera todos os nodos
        {
            q = p;
            p = p->prox;
            free(q);
        }
        free(*fila);
        *fila = NULL;
    }
}

int enqueue(struct fila *fila, int dado)
{
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));

    if (!novo)
        return 0;

    novo->chave = dado;
    novo->prox = NULL;

    if (!fila->ini)
        fila->ini = novo;
    else
        fila->fim->prox = novo;

    fila->fim = novo;
    fila->tamanho++;
    return 1;
}

int dequeue(struct fila *fila, int *dado)
{
    struct nodo *p;

    if (!fila->ini)
        return 0;

    *dado = fila->ini->chave;
    p = fila->ini;

    fila->ini = fila->ini->prox;
    free(p);
    fila->tamanho--;

    if (!fila->ini)
        fila->fim = NULL;
        
    return 1;
}

int fila_tamanho(struct fila *fila)
{
    return fila->tamanho;
}

int fila_vazia(struct fila *fila)
{
    return !fila->ini;
}
