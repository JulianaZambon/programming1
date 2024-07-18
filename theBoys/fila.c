#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct fila *fila_cria()
{
    struct fila *f = (struct fila *)malloc(sizeof(struct fila));
    if (f != NULL)
    {
        f->ini = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

void fila_destroi(struct fila **fila)
{
    if (*fila != NULL)
    {
        struct nodo *atual = (*fila)->ini;
        struct nodo *prox;
        while (atual != NULL)
        {
            prox = atual->prox;
            free(atual);
            atual = prox;
        }
        free(*fila);
        *fila = NULL;
    }
}

int enqueue(struct fila *fila, int dado)
{
    if (fila == NULL)
    {
        return 0;
    }

    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL)
    {
        return 0;
    }

    novo->chave = dado; /* insere o dado no novo nodo */
    novo->prox = NULL;  /* o novo nodo será o ultimo da fila */

    if (fila->ini == NULL)
    {
        fila->ini = novo;
    }
    else
    {
        fila->fim->prox = novo;
    }

    fila->fim = novo;
    fila->tamanho++;

    return 1;
}

int dequeue(struct fila *fila, int *dado)
{
    if (fila == NULL || fila->ini == NULL)
    {
        return 0;
    }

    struct nodo *remover = fila->ini; /* nodo a ser removido */
    *dado = remover->chave;           /* valor a ser retornado */

    fila->ini = fila->ini->prox;
    free(remover);

    if (fila->ini == NULL)
    {
        fila->fim = NULL;
    }

    fila->tamanho--;

    return 1;
}

int fila_tamanho(struct fila *fila)
{
    if (fila == NULL)
    {
        return 0;
    }
    return fila->tamanho;
}

int fila_vazia(struct fila *fila)
{
    return (fila == NULL || fila->ini == NULL);
}

/* Imprime a fila no formato "[ e1 e2 ... en ]" 
 * Se a fila for vazia imprime "[ ]" */
void fila_imprime (struct fila *fila)
{
    if (fila == NULL)
        printf("[ ]\n");

    
    struct nodo *atual = fila->ini;
    printf("[ ");
    while (atual != NULL)
    {
        printf("%d ", atual->chave);
        atual = atual->prox;
    }
    printf("]\n");

    return;
}
