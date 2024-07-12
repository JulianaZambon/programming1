#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/* Função para criar uma nova lista encadeada */
struct lista *lista_cria()
{
    struct lista *lista = (struct lista *)malloc(sizeof(struct lista));
    if (lista != NULL)
    {
        lista->ini = NULL;
        lista->ptr = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi(struct lista **lista)
{
    struct nodo *atual = (*lista)->ini;
    while (atual != NULL)
    {
        struct nodo *aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(*lista);
    *lista = NULL;
}

/* Função para inserir um novo elemento no início da lista */
int lista_insere_inicio(struct lista *lista, int chave)
{
    /* Aloca memória para o novo nodo */
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL)
        return 0;

    /* Preenche os campos do novo nodo */
    novo->chave = chave;
    novo->prox = lista->ini;

    /* Atualiza o início da lista */
    lista->ini = novo;

    /* Incrementa o tamanho da lista */
    lista->tamanho++;

    return 1;
}

/* Função para inserir um novo elemento no fim da lista */
int lista_insere_fim(struct lista *lista, int chave)
{
    /* Aloca memória para o novo nodo */
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL)
        return 0;

    /* Preenche os campos do novo nodo */
    novo->chave = chave;
    novo->prox = NULL;

    /* Caso a lista esteja vazia */
    if (lista->ini == NULL)
    {
        lista->ini = novo;
    }
    else
    {
        /* Encontra o último nodo da lista */
        struct nodo *atual = lista->ini;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }

        /* Insere o novo nodo no final da lista */
        atual->prox = novo;
    }

    /* Incrementa o tamanho da lista */
    lista->tamanho++;

    return 1;
}

/* Função para inserir um novo elemento de forma ordenada na lista */
int lista_insere_ordenado(struct lista *lista, int chave)
{
    /* Aloca memória para o novo nodo */
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL)
        return 0;

    /* Preenche os campos do novo nodo */
    novo->chave = chave;

    /* Caso a lista esteja vazia ou o novo nodo seja menor que o primeiro */
    if (lista->ini == NULL || chave < lista->ini->chave)
    {
        novo->prox = lista->ini;
        lista->ini = novo;
    }
    else
    {
        /* Encontra o nodo anterior ao novo nodo */
        struct nodo *prev = NULL;
        struct nodo *atual = lista->ini;
        while (atual != NULL && atual->chave < chave)
        {
            prev = atual;
            atual = atual->prox;
        }

        /* Insere o novo nodo na lista */
        if (prev != NULL)
        {
            prev->prox = novo;
        }
        else
        {
            lista->ini = novo;
        }
        novo->prox = atual;
    }

    /* Incrementa o tamanho da lista */
    lista->tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
 */
int lista_remove_inicio(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    /* Preenche o valor do elemento removido */
    *chave = lista->ini->chave;

    /* Remove o primeiro nodo da lista */
    struct nodo *aux = lista->ini;
    lista->ini = lista->ini->prox;
    free(aux);

    /* Decrementa o tamanho da lista */
    lista->tamanho--;

    return 1;
}

/* Função para remover o último elemento da lista */
int lista_remove_fim(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    /* Caso a lista tenha apenas um elemento */
    if (lista->ini->prox == NULL)
    {
        *chave = lista->ini->chave;
        free(lista->ini);
        lista->ini = NULL;
    }
    else
    {
        /* Encontra o penúltimo nodo da lista */
        struct nodo *prev = NULL;
        struct nodo *atual = lista->ini;
        while (atual->prox != NULL)
        {
            prev = atual;
            atual = atual->prox;
        }

        /* Preenche o valor do elemento removido */
        *chave = atual->chave;

        /* Remove o último nodo da lista */
        prev->prox = NULL;
        free(atual);
    }

    /* Decrementa o tamanho da lista */
    lista->tamanho--;

    return 1;
}

/* Função para remover um elemento específico da lista */
int lista_remove_ordenado(struct lista *lista, int chave)
{
    if (lista->ini == NULL)
        return 0;

    /* Caso o elemento a ser removido seja o primeiro da lista */
    if (lista->ini->chave == chave)
    {
        struct nodo *aux = lista->ini;
        lista->ini = lista->ini->prox;
        free(aux);
        lista->tamanho--;
        return 1;
    }

    /* Encontra o nodo anterior ao nodo a ser removido */
    struct nodo *prev = NULL;
    struct nodo *atual = lista->ini;
    while (atual != NULL && atual->chave != chave)
    {
        prev = atual;
        atual = atual->prox;
    }

    /* Caso o elemento não tenha sido encontrado */
    if (atual == NULL)
        return 0;

    /* Remove o nodo da lista */
    prev->prox = atual->prox;
    free(atual);
    lista->tamanho--;

    return 1;
}

/* Função que verifica se a lista está vazia */
int lista_vazia(struct lista *lista)
{
    return lista->ini == NULL;
}

/* Função que retorna o tamanho atual da lista */
int lista_tamanho(struct lista *lista)
{
    return lista->tamanho;
}

/* Função que verifica se um elemento pertence à lista */
int lista_pertence(struct lista *lista, int chave)
{
    struct nodo *atual = lista->ini;
    while (atual != NULL)
    {
        if (atual->chave == chave)
            return 1;
        atual = atual->prox;
    }
    return 0;
}


void lista_inicia_iterador(struct lista *lista)
{
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista->ptr == NULL)
        return 0;

    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;

    return 1;
}
