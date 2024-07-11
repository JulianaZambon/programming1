/* 
 * Programa para testar a fila e a lef.
 * feito por Marcos Castilho em 11/07/2024
*/

#include <stdio.h>
#include "fila.h"
#include "lef.h"
#define MAX 5

struct fila* teste_criar_fila ()
{
    struct fila* f;

    if (! (f = fila_cria ()))
        fprintf (stderr, "Falha na alocacao da fila\n");

    printf ("  Fila criada com sucesso\n");
    return f;
}

void teste_fila_vazia (struct fila* f)
{
    if (fila_vazia (f))
        printf ("  fila esta vazia");
    else
        printf ("  fila nao esta vazia");
    printf (", seu tamanho eh %d.\n", fila_tamanho (f));
}

void teste_enqueue (struct fila* f, int limite)
{
    int i;

    for (i=1; i <= limite; i++)
    {
        printf ("  Enfileirando %d\n", i + 10);
        if (! enqueue (f, i + 10)){
            printf ("  Fila cheia, nao inseriu.\n");
            return;
        }
    }
}

void teste_dequeue (struct fila* f)
{
    int dado;

    /* remove todo mundo */
    while (! fila_vazia (f))
    {
        if (dequeue (f, &dado))
            printf ("  Desenfileirando %d\n", dado);
    }
}

int main (void)
{
    struct fila *f;
    struct lef_t *l ;
    struct evento_t *ev ;
    int dado;
    int i;

    printf ("Teste 1: criar fila e ver se esta vazia:\n");
    printf ("Esperado: tem que dar fila vazia com tamanho zero\n");
    f = teste_criar_fila ();
    teste_fila_vazia (f);
    printf ("\n\n");

    printf ("Teste 2: tenta desenfileirar elemento com fila vazia:\n");
    printf ("Esperado: nao pode ter dado segfault\n");
    if (! dequeue (f, &dado))
        printf ("  OK: dequeue na fila vazia nao deu segfault.\n");
    printf ("\n\n");

    printf ("Teste 3: inserir 5 elementos:\n");
    printf ("Esperado: tem que mostrar enfileirar de 11 ate 15\n");
    printf ("          o tamanho tem que terminar com valor 5\n");
    printf ("          E a fila NAO PODE estar vazia\n");
    teste_enqueue (f, MAX); 
    teste_fila_vazia (f);
    printf ("\n\n");

    printf ("Teste 4: esvaziar a fila:\n");
    printf ("Esperado: tem que mostrar desenfileirar de 11 ate 15\n");
    printf ("          o tamanho tem que terminar com valor 0\n");
    printf ("          E a fila tem que estar vazia\n");
    teste_dequeue (f); 
    teste_fila_vazia (f);
    printf ("\n\n");

    printf ("Teste 5: destruir uma fila vazia:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    fila_destroi (&f);
    printf ("\n\n");

    printf ("Teste 6: destruir uma fila com elementos:\n");
    printf ("Esperado: nao pode ter leak (conferir com valdrind)\n");
    printf ("          E nao pode ter segfault\n");
    f = fila_cria ();
    if (enqueue (f, 1) && enqueue (f, 2) && enqueue (f, 3))
        fila_destroi (&f);
    else
        printf ("Falha na alocação dos elementos!!!");
    printf ("\n\n");

    printf ("Teste 7: Teste de aterramento do ponteiro:\n");
    printf ("Esperado: Nao pode ter segfault\n");
    if (f != NULL)
        printf ("ERRO: fila nao eh NULL apos fila_destroi\n");
    printf ("\n\n");

    printf ("Teste 8: Teste de criar uma lef:\n");
    printf ("         Imprimir lef vazia\n");
    /* cria uma lef l vazia */
    l = cria_lef ();

    /* imprime l */
    imprime_lef (l);
    printf ("\n\n");

    printf ("Teste 9: Teste de inserir elementos na lef:\n");
    printf ("Esperado: Imprimir eventos de 1 a 4, com os id's zero\n");
    /* insere eventos na LEF */
    for (i = 0; i < 4; i++)
    {
        ev = cria_evento (i, 0, 0, 0) ;
        insere_lef (l, ev);
    }

    /* imprime l */
    imprime_lef (l);
    printf ("\n\n");

    printf ("Teste 10: Teste de inserir mais elementos na lef:\n");
    printf ("Esperado: Imprimir eventos de 2 a 6, com os id's 1\n");
    printf ("          Tem que manter a prioridades daqueles com id's 0\n");
    /* insere mais eventos na LEF */
    for (i = 2; i < 6; i++)
    {
        ev = cria_evento (i, 1, 1, 1);
        insere_lef (l, ev);
    }

    /* imprime l */
    imprime_lef (l);
    printf ("\n\n");

    printf ("Teste 10: Teste de inserir mais elementos na lef:\n");
    printf ("Esperado: Retirar corretamente os primeiros elementos.\n");
    /* enquanto l nao estiver vazia */
    while (!vazia_lef (l))
    {
        /*   retira o primeiro evento de l */
        ev = retira_lef (l);
        if (ev)
            printf ("retirei evento %d %d %d %d\n", ev->tempo, ev->tipo,
                ev->dado1, ev->dado2);
        else
            printf ("sem evento\n");
        destroi_evento (ev);

        /* imprime l */
        imprime_lef (l);
    }
    printf ("\n\n");

    printf ("Teste 11: Destruir a lef:\n");
    printf ("Esperado: Nao pode ter leak, usar valgrind.\n");
    /* destroi l */
    l = destroi_lef (l);

    return 0;
}
