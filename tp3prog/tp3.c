#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"
#define MAX 100

/* Função para ler o tamanho do vetor */
int ler_tamanho()
{
    int n;
    printf("Insira o tamanho do vetor (entre 0 e %d):\n", MAX - 1);
    scanf("%d", &n);
    if (n <= 0 || n >= MAX)
    {
        printf("Tamanho inválido.\n");
        return -1;
    }
    return n;
}

/* Função de comparação auxiliar para qsort_r */
int compara_aux(const void *a, const void *b, void *arg)
{
    return compara_r(*(struct racional **)a, *(struct racional **)b);
}

/* Função principal que segue o pseudo-código fornecido */
int main()
{
    srand(0);
    int n = ler_tamanho();

    if (n == -1)
        return 1;

    struct racional **vetor = (struct racional **)malloc(n * sizeof(struct racional *));

    if (vetor == NULL)
    {
        printf("Erro de alocação.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        long int num, den;
        printf("Insira o numerador e o denominador do racional %d:\n", i + 1);
        scanf("%ld %ld", &num, &den);
        vetor[i] = cria_r(num, den);
    }

    printf("Racionais lidos:\n");
    for (int i = 0; i < n; i++)
    {
        if (vetor[i] != NULL && valido_r(vetor[i]))
        {
            imprime_r(vetor[i]);
            printf(" ");
        }
    }
    printf("\n");

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (vetor[i] != NULL && valido_r(vetor[i]))
        {
            vetor[j++] = vetor[i];
        }
        else
        {
            destroi_r(&vetor[i]);
        }
    }
    n = j;

    printf("Racionais válidos:\n");
    for (int i = 0; i < n; i++)
    {
        imprime_r(vetor[i]);
        printf(" ");
    }
    printf("\n");

    qsort_r(vetor, n, sizeof(struct racional *), compara_aux, NULL);

    printf("Racionais ordenados:\n");
    for (int i = 0; i < n; i++)
    {
        imprime_r(vetor[i]);
        printf(" ");
    }
    printf("\n");

    struct racional *soma = cria_r(0, 1);
    for (int i = 0; i < n; i++)
    {
        struct racional *temp = soma_r(soma, vetor[i]);
        destroi_r(&soma);
        soma = temp;
    }

    printf("Soma dos racionais:\n");
    imprime_r(soma);
    printf("\n");

    destroi_r(&soma);
    for (int i = 0; i < n; i++)
    {
        destroi_r(&vetor[i]);
    }
    free(vetor);
    return 0;
}
