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
        lista->ptr = NULL; /* Inicializa o iterador como NULL */
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

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
 */
int lista_insere_inicio(struct lista *lista, int chave)
{
    /* Aloca memória para o novo nodo */
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL)
        return 0;

    /* Caso base */
    if (lista->ini == NULL) /* Lista vazia */
    {
        novo->chave = chave;
        novo->prox = NULL;
        lista->ini = novo;
    }
    else /* Lista não vazia */
    {
        novo->chave = chave;
        novo->prox = lista->ini;
        lista->ini = novo;
    }

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

    /* Caso base */
    /* Se a lista estiver vazia, insere no início */
    if (lista->ini == NULL)
    {
        lista->ini = novo;
    }
    else
    {
        /* Percorre a lista até o último nodo */
        struct nodo *atual = lista->ini;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        /* Adiciona o novo nodo ao final da lista */
        atual->prox = novo;
    }

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
    novo->prox = NULL;

    /* Caso a lista esteja vazia */
    if (lista->ini == NULL)
    {
        lista->ini = novo;
    }
    else
    {
        /* Caso o novo nodo deva ser o primeiro da lista */
        if (chave < lista->ini->chave)
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
            prev->prox = novo;
            novo->prox = atual;
        }
    }

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
        lista->tamanho--;
        return 1;
    }

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

/* Inicializa o iterador da lista */
void lista_inicia_iterador(struct lista *lista)
{
    lista->ptr = lista->ini;
}

/* Incrementa o iterador da lista e retorna o valor atual */
int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista->ptr == NULL)
        return 0;

    *chave = lista->ptr->chave;    /* Retorna o valor atual */
    lista->ptr = lista->ptr->prox; /* Incrementa o iterador */

    return 1;
}

