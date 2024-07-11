#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

struct lista *lista_cria()
{
    struct lista *l;
    l = (struct lista *)malloc(sizeof(struct lista)); // aloca memoria para a lista

    // em caso de erro de alocação
    if (l == NULL)
        return NULL;

    // cria uma lista vazia
    l->ini = NULL;
    l->ptr = NULL;
    l->tamanho = 0;

    return l;
}

void lista_destroi(struct lista **lista)
{
    struct nodo *aux;     // cria um nodo auxiliar
    while ((*lista)->ini) // enquanto a lista nao for vazia
    {
        aux = (*lista)->ini;                 // auxiliar recebe o inicio da lista
        (*lista)->ini = (*lista)->ini->prox; // inicio da lista recebe o proximo
        free(aux);
    }
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio(struct lista *lista, int chave)
{
    struct nodo *novo;                                 // cria um novo nodo
    novo = (struct nodo *)malloc(sizeof(struct nodo)); // aloca memoria para o novo nodo

    // em caso de erro de alocação
    if (novo == NULL)
        return 0;

    novo->chave = chave;     // novo nodo recebe a chave
    novo->prox = lista->ini; // novo nodo aponta para o inicio da lista
    lista->ini = novo;       // inicio da lista recebe o novo nodo
    lista->tamanho++;        // incrementa o tamanho da lista

    return 1;
}

int lista_insere_fim(struct lista *lista, int chave)
{
    struct nodo *novo;                                 // cria um novo nodo
    novo = (struct nodo *)malloc(sizeof(struct nodo)); // aloca memoria para o novo nodo

    // em caso de erro de alocação
    if (novo == NULL)
        return 0;

    novo->chave = chave; // novo nodo recebe a chave
    novo->prox = NULL;   // novo nodo aponta para NULL

    // se a lista estiver vazia
    if (lista->ini == NULL)
    {
        lista->ini = novo; // inicio da lista recebe o novo nodo
    }
    else
    {
        struct nodo *aux; // cria um nodo auxiliar
        aux = lista->ini; // auxiliar recebe o inicio da lista

        // percorre a lista ate o final
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novo; // o ultimo nodo aponta para o novo nodo
    }

    lista->tamanho++; // incrementa o tamanho da lista

    return 1;
}

int lista_insere_ordenado(struct lista *lista, int chave)
{
    struct nodo *novo;                                 // cria um novo nodo
    novo = (struct nodo *)malloc(sizeof(struct nodo)); // aloca memoria para o novo nodo

    // em caso de erro de alocação
    if (novo == NULL)
        return 0;

    novo->chave = chave; // novo nodo recebe a chave

    // se a lista estiver vazia ou a chave for menor que o inicio da lista
    if (lista->ini == NULL || chave < lista->ini->chave)
    {
        novo->prox = lista->ini; // novo nodo aponta para o inicio da lista
        lista->ini = novo;       // inicio da lista recebe o novo nodo
    }
    else
    {
        struct nodo *aux; // cria um nodo auxiliar
        aux = lista->ini; // auxiliar recebe o inicio da lista

        // percorre a lista ate o final ou ate a chave ser maior que o nodo
        while (aux->prox != NULL && chave > aux->prox->chave)
        {
            aux = aux->prox;
        }

        novo->prox = aux->prox; // novo nodo aponta para o proximo nodo
        aux->prox = novo;       // nodo anterior aponta para o novo nodo
    }

    lista->tamanho++; // incrementa o tamanho da lista

    return 1;
}

int lista_remove_inicio(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    struct nodo *aux; // cria um nodo auxiliar
    aux = lista->ini; // auxiliar recebe o inicio da lista
    *chave = aux->chave; // chave recebe a chave do nodo

    lista->ini = lista->ini->prox; // inicio da lista recebe o proximo nodo
    free(aux); // libera a memoria do nodo
    lista->tamanho--; // decrementa o tamanho da lista

    return 1;
}

int lista_remove_fim(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    struct nodo *aux; // cria um nodo auxiliar
    aux = lista->ini; // auxiliar recebe o inicio da lista

    // se a lista tiver apenas um nodo
    if (aux->prox == NULL)
    {
        *chave = aux->chave; // chave recebe a chave do nodo
        lista->ini = NULL; // inicio da lista recebe NULL
        free(aux); // libera a memoria do nodo
    }
    else
    {
        // percorre a lista ate o penultimo nodo
        while (aux->prox->prox != NULL)
        {
            aux = aux->prox;
        }

        *chave = aux->prox->chave; // chave recebe a chave do nodo
        free(aux->prox); // libera a memoria do nodo
        aux->prox = NULL; // penultimo nodo aponta para NULL
    }

    lista->tamanho--; // decrementa o tamanho da lista

    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave)
{
    if (lista->ini == NULL)
        return 0;

    struct nodo *aux; // cria um nodo auxiliar
    aux = lista->ini; // auxiliar recebe o inicio da lista

    // se a chave for igual ao inicio da lista
    if (aux->chave == chave)
    {
        lista->ini = lista->ini->prox; // inicio da lista recebe o proximo nodo
        free(aux); // libera a memoria do nodo
        lista->tamanho--; // decrementa o tamanho da lista
        return 1;
    }

    // percorre a lista ate o penultimo nodo
    while (aux->prox != NULL)
    {
        if (aux->prox->chave == chave)
        {
            struct nodo *aux2; // cria um nodo auxiliar
            aux2 = aux->prox; // auxiliar recebe o proximo nodo
            aux->prox = aux->prox->prox; // nodo anterior aponta para o proximo nodo
            free(aux2); // libera a memoria do nodo
            lista->tamanho--; // decrementa o tamanho da lista
            return 1;
        }
        aux = aux->prox; // auxiliar recebe o proximo nodo
    }

    return 0;
}

int lista_vazia(struct lista *lista)
{
    if (lista->ini == NULL)
        return 1;
    else
        return 0;
}

int lista_tamanho(struct lista *lista)
{
    return lista->tamanho;
}

int lista_pertence(struct lista *lista, int chave)
{
    if (lista->ini->chave == chave)
        return 1;
    else
        return 0;
}

void lista_inicia_iterador(struct lista *lista)
{
    lista->ptr = lista->ini; // ponteiro ptr recebe o inicio da lista
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista->ptr == NULL) // se o ponteiro ptr for NULL
        return 0;

    *chave = lista->ptr->chave; // chave recebe a chave do nodo
    lista->ptr = lista->ptr->prox; // ponteiro ptr recebe o proximo nodo

    return 1;
}

