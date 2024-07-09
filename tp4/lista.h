/*
 * TAD lista
 * -> versao com lista ligada com nodo cabeca
 * Autores:
 *    André Ricardo Abed Gregio
 *    Marcos Alexandre Castilho
 *    Luis Carlos Erpen de Bona
 *
 * Versao 1.0.0 de 22/05/2023
 * Versao 2.0.0 de 08/07/2024
*/

#ifndef _lista_t_H
#define _lista_t_H

struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};

/*
 * Cria e retorna uma nova lista.
 * Retorna NULL em caso de erro de alocação.
*/
struct lista *lista_cria ();

/* Desaloca toda memoria da lista e faz lista receber NULL. */
void lista_destroi (struct lista **lista);

/*
 * Insere chave no inicio da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_inicio (struct lista *lista, int chave);

/*
 * Insere chave no final da lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_fim (struct lista *lista, int chave);

/*
 * Insere chave em ordem na lista. Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int lista_insere_ordenado (struct lista *lista, int chave);

/*
 * Remove o elemento do inicio da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_inicio (struct lista *lista, int *chave);

/*
 * Remove o elemento do final da lista e o retorna
 * no parametro chave. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_fim (struct lista *lista, int *chave);

/*
 * Remove o elemento chave da lista mantendo-a ordenada.
 * A função considera que a cheve esta presente na lista, quem chama
 * esta funcao deve garantir isso.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da lista estar vazia.
*/
int lista_remove_ordenado (struct lista *lista, int chave);

/*
  Retorna 1 se a lista está vazia e 0 caso contrário.
*/
int lista_vazia (struct lista *lista);

/*
  Retorna o numero de elementos da lista
*/
int lista_tamanho (struct lista *lista);

/*
  Retorna 1 se o elemento chave esta presente na lista,
  caso contrário retorna 0.
*/
int lista_pertence (struct lista *lista, int chave);

/*
 * As funcoes abaixo implementam um iterador que vao permitir o usuario
 * de uma lista percorre-la, sem conhecer sua estrutura.
 *
 * Em conjunto, elas simulam um laço, sendo a inicializacao deste
 * a funcao lista_inicia_iterador e o incremento sendo a funcao
 * lista_incrementa_iterador.
 *
 * O ponteiro ptr da struct (iterador) eh inicializado apontando
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * da lista.
 *
 * Ver exemplo de uso em testa_lista.c (funcao testa_imprimir_lista)
*/

/*
 * Inicializa ptr usado na funcao incrementa_iterador.
 * A funcao main deve garantir que a lista nao eh vazia.
*/
void lista_inicia_iterador (struct lista *lista);

/*
 * Devolve no parametro *chave o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro da lista).
*/
int lista_incrementa_iterador (struct lista *lista, int *chave);

#endif
