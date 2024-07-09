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
}

int lista_insere_fim(struct lista *lista, int chave)
{
}

int lista_insere_ordenado(struct lista *lista, int chave)
{
}

int lista_remove_inicio(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    // Remove o elemento do inicio da lista e o retorna
    // no parametro chave. Nao confundir com o retorno da funcao.
}

int lista_remove_fim(struct lista *lista, int *chave)
{
    if (lista->ini == NULL)
        return 0;

    // Remove o elemento do final da lista e o retorna
    // no parametro chave. Nao confundir com o retorno da funcao.
}

int lista_remove_ordenado(struct lista *lista, int chave)
{
    if (lista->ini == NULL)
        return 0;

    // Remove o elemento chave da lista mantendo-a ordenada.
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
    
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{

}
