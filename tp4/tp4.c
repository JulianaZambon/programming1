/* 
 * Programa para testar a liblista.
 * feito por Marcos Castilho em 05/04/2022
*/

#include <stdio.h>
#include "lista.h"
#define MAX 5

void imprimir_lista (struct lista *l){
    int chave;

    if (lista_vazia (l)){
        printf ("lista vazia\n");
        return;
    }

    lista_inicia_iterador (l);
    while (lista_incrementa_iterador (l, &chave))
        printf ("%d ", chave);
    printf ("%d\n", chave);
}

struct lista *teste_criar_lista ()
{
    struct lista *l;

    if (! (l = lista_cria ()))
        fprintf (stderr, "Falha na alocacao da lista\n");

    return l;
}

void teste_lista_vazia (struct lista *l)
{
    if (lista_vazia (l))
        printf ("lista esta vazia");
    else
        printf ("lista nao esta vazia");
}

void teste_insere_inicio (struct lista *l, int limite)
{
    int i;

    for (i=1; i <= limite; i++)
    {
        if (! lista_insere_inicio (l, i + 10)){
            printf ("Lista cheia, nao inseriu.\n");
            return;
        }
        imprimir_lista (l);
    }
}

void teste_insere_fim (struct lista *l, int limite)
{
    int i;

    for (i=1; i <= limite; i++)
    {
        if (! lista_insere_fim (l, i + 10)){
            printf ("Lista cheia, nao inseriu.\n");
            return;
        }
        imprimir_lista (l);
    }
}

void teste_remove_inicio (struct lista *l)
{
    int chave;

    /* remove todo mundo */
    while (! lista_vazia (l))
        if (lista_remove_inicio (l, &chave))
            imprimir_lista (l);
}

void teste_remove_fim (struct lista *l)
{
    int chave;

    /* remove todo mundo */
    while (! lista_vazia (l))
        if (lista_remove_fim (l, &chave))
            imprimir_lista (l);
}

void teste_insere_ordenado (struct lista *l)
{
    lista_insere_ordenado (l, 13); imprimir_lista (l);
    lista_insere_ordenado (l, 15); imprimir_lista (l);
    lista_insere_ordenado (l, 11); imprimir_lista (l);
    lista_insere_ordenado (l, 12); imprimir_lista (l);
    lista_insere_ordenado (l, 14); imprimir_lista (l);
}


void teste_remove_ordenado (struct lista *l)
{
    lista_remove_ordenado (l, 13); imprimir_lista (l);
    lista_remove_ordenado (l, 15); imprimir_lista (l);
    lista_remove_ordenado (l, 11); imprimir_lista (l);
    lista_remove_ordenado (l, 12); imprimir_lista (l);
    lista_remove_ordenado (l, 14); imprimir_lista (l);
}

void teste_de_pertinencia (struct lista *l)
{
    lista_insere_inicio (l, 13);
    lista_insere_inicio (l, 15);
    lista_insere_inicio (l, 11);
    lista_insere_inicio (l, 12);
    lista_insere_inicio (l, 14);
    imprimir_lista (l);
    if (lista_pertence (l, 11)) printf ("11 pertence\n");
    if (lista_pertence (l, 12)) printf ("12 pertence\n");
    if (lista_pertence (l, 13)) printf ("13 pertence\n");
    if (lista_pertence (l, 14)) printf ("14 pertence\n");
    if (lista_pertence (l, 15)) printf ("15 pertence\n");
    if (! lista_pertence (l, 10)) printf ("10 nao pertence\n");
    if (! lista_pertence (l, 16)) printf ("16 nao pertence\n");
}

int main (void)
{
    struct lista *l;
    int chave;

    printf ("Teste 1: criar lista e ver se esta vazia:\n");
    printf ("Esperado: tem que imprimir mensagem 'lista esta vazia'\n");
    l = teste_criar_lista ();
    teste_lista_vazia (l);
    printf ("\n\n");

    printf ("Teste 2: tenta remover elemento com lista vazia:\n");
    printf ("Esperado: nao pode ter dado segfault\n");
    if (! lista_remove_inicio (l, &chave))
        printf ("\tOK: remover da lista vazia nao deu segfault.\n");
    printf ("\n\n");

    printf ("Teste 3: inserir 5 elementos no inicio:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez com o maior elemento no inicio. \n");
    printf ("\nATENCAO: se nao imprimir a lista corretamente o erro pode estar:\n");
    printf ("- ou na insercao\n");
    printf ("- ou na implementacao das funcoes que controlam o iterador\n");
    printf ("- voce pode implementar TEMPORARIAMENTE uma funcao que imprime a lista acessando os nodos diretamente, ate encontrar o problema.\n");
    teste_insere_inicio (l, MAX); 
    printf ("\n\n");

    printf ("Teste 4: esvaziar a lista retirando do inicio:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez sem o primeiro elemento\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_inicio (l); 
    printf ("\n\n");

    printf ("Teste 5: inserir 5 elementos no fim:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez com o maior elemento no fim\n");
    teste_insere_fim (l, MAX); 
    printf ("\n\n");

    printf ("Teste 6: esvaziar a lista retirando do fim:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, a cada vez sem o maior elemento\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_fim (l); 
    printf ("\n\n");

    printf ("Teste 7: inserir 5 elementos em ordem:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, sempre ordenada\n");
    printf ("Esperado: tem que mostrar remover de 11 ate 15\n");
    teste_insere_ordenado (l); 
    printf ("\n\n");

    printf ("Teste 8: remover 5 elementos em ordem:\n");
    printf ("Esperado: tem que imprimir a lista 5 vezes, sempre ordenada\n");
    printf ("          Ao final, mostrar a mensagem 'lista vazia'\n");
    teste_remove_ordenado (l); 
    printf ("\n\n");

    printf ("Teste 9: teste de pertinencia \n");
    printf ("Esperado: apos imprimir a lista, tem que mostrar que de 11 a 15 pertence\n");
    printf ("          E que 10 e 16 nao pertencem\n");
    teste_de_pertinencia (l); 
    printf ("\n\n");

    printf ("Teste 10: destruir uma lista com elementos:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    lista_destroi (&l);
    printf ("\n\n");

    printf ("Teste 11: destruir uma lista vazia:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    l = lista_cria ();
    lista_destroi (&l);
    printf ("\n\n");

    return 0;
}
