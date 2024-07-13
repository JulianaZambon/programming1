#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista *lista_cria()
{
    struct lista *nova_lista = (struct lista *)malloc(sizeof(struct lista));

    if (nova_lista != NULL)
    {
        nova_lista->ini = (struct nodo *)malloc(sizeof(struct nodo)); /* nodo cabeça */
        if (nova_lista->ini != NULL)
        {
            nova_lista->ini->prox = NULL;      /* lista vazia */
            nova_lista->ptr = nova_lista->ini; /* iterador no inicio da lista */
            nova_lista->tamanho = 0;           /* lista vazia */
            return nova_lista;
        }
        else
        {
            free(nova_lista);
            return NULL;
        }
    }
    return NULL;
}

void lista_destroi(struct lista **lista)
{
    if (lista != NULL && *lista != NULL)
    {
        struct nodo *atual = (*lista)->ini;
        while (atual != NULL)
        {
            struct nodo *prox = atual->prox; /* guarda o proximo nodo */
            free(atual);
            atual = prox;
        }
        free(*lista);
        *lista = NULL;
    }
}

int lista_insere_inicio(struct lista *lista, int chave)
{
    if (lista == NULL || lista->ini == NULL)
        return 0;

    struct nodo *novo_nodo = (struct nodo *)malloc(sizeof(struct nodo));

    if (novo_nodo != NULL)
    {
        novo_nodo->chave = chave;           /* insere a chave no novo nodo */
        novo_nodo->prox = lista->ini->prox; /* aponta para o nodo que era o primeiro */
        lista->ini->prox = novo_nodo;       /* aponta o inicio da lista para o novo nodo */
        lista->tamanho++;
        return 1;
    }
    return 0;
}

int lista_insere_fim(struct lista *lista, int chave)
{
    if (lista == NULL || lista->ini == NULL)
        return 0;

    struct nodo *novo_nodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo_nodo != NULL)
    {
        novo_nodo->chave = chave; /* insere a chave no novo nodo */
        novo_nodo->prox = NULL;

        struct nodo *atual = lista->ini;
        while (atual->prox != NULL) /* percorre a lista */
        {
            atual = atual->prox;
        }
        atual->prox = novo_nodo;
        lista->tamanho++;
        return 1;
    }
    return 0;
}

int lista_insere_ordenado(struct lista *lista, int chave)
{
    if (lista == NULL || lista->ini == NULL)
        return 0;

    struct nodo *novo_nodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo_nodo != NULL)
    {
        novo_nodo->chave = chave;

        struct nodo *anterior = lista->ini;
        struct nodo *atual = lista->ini->prox;

        while (atual != NULL && atual->chave < chave)
        {
            anterior = atual;
            atual = atual->prox;
        }

        novo_nodo->prox = atual;
        anterior->prox = novo_nodo;
        lista->tamanho++;
        return 1;
    }
    return 0;
}

int lista_remove_inicio(struct lista *lista, int *chave)
{
    if (lista == NULL || lista->ini == NULL || lista->ini->prox == NULL)
        return 0;

    struct nodo *removido = lista->ini->prox;
    *chave = removido->chave;

    lista->ini->prox = removido->prox;
    free(removido);
    lista->tamanho--;
    return 1;
}

int lista_remove_fim(struct lista *lista, int *chave)
{
    if (lista == NULL || lista->ini == NULL || lista->ini->prox == NULL)
        return 0;

    struct nodo *anterior = lista->ini;
    struct nodo *atual = lista->ini->prox;

    while (atual->prox != NULL)
    {
        anterior = atual;
        atual = atual->prox;
    }

    *chave = atual->chave; /* retorna o valor do nodo removido */
    anterior->prox = NULL;
    free(atual);
    lista->tamanho--;
    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave)
{
    if (lista == NULL || lista->ini == NULL || lista->ini->prox == NULL)
        return 0;

    struct nodo *anterior = lista->ini; 
    struct nodo *atual = lista->ini->prox;

    while (atual != NULL && atual->chave != chave) 
    {
        anterior = atual; 
        atual = atual->prox; 
    }

    if (atual != NULL)
    {
        anterior->prox = atual->prox;
        free(atual);
        lista->tamanho--;
        return 1;
    }
    return 0;
}

int lista_vazia(struct lista *lista)
{
    if (lista == NULL || lista->ini == NULL)
        return 1;
    return lista->ini->prox == NULL;
}

int lista_tamanho(struct lista *lista)
{
    if (lista == NULL || lista->ini == NULL)
        return 0;
    return lista->tamanho;
}

int lista_pertence(struct lista *lista, int chave)
{
    if (lista == NULL || lista->ini == NULL)
        return 0;

    struct nodo *atual = lista->ini->prox;
    while (atual != NULL) /* percorre a lista */
    {
        if (atual->chave == chave) /* chave encontrada */
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void lista_inicia_iterador(struct lista *lista)
{
    if (lista != NULL && lista->ini != NULL) /* lista não vazia */
        lista->ptr = lista->ini->prox;
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista == NULL || lista->ini == NULL || lista->ptr == NULL) /* lista vazia ou iterador fora da lista */
        return 0;

    *chave = lista->ptr->chave;    /* retorna o valor do nodo atual */
    lista->ptr = lista->ptr->prox; /* avança o ponteiro para o próximo nodo */

    if (lista->ptr == NULL) /* fim da lista */
        return 0;
    else
        return 1;
}
