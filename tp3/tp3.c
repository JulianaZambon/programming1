#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "racionais.h"
#define MAX 100

/* Função para ler o tamanho do vetor */
int ler_tamanho() {
    int n;
    printf("Insira o tamanho do vetor (entre 0 e %d):\n", MAX - 1);
    scanf("%d", &n);
    if (n <= 0 || n >= MAX) {
        printf("Tamanho inválido.\n");
        return -1;
    }
    return n;
}

/* Função principal que segue o pseudo-código fornecido */
/*    /* A sua fun¸c˜ao main deve
incluir o header racionais.h e deve ter um la¸co principal que implemente
corretamente em C o seguinte pseudo-c´odigo:
use srand (0)
leia um n tal que 0 < n < 100
crie um vetor de n posicoes contendo ponteiros para numeros racionais
- Os racionais deverao ser inicializados com valores lidos do teclado
- Este vetor tambem deve ser alocado dinamicamente
imprima os racionais apontados pelos elementos do vetor
elimine deste vetor os racionais invalidos
imprima o vetor resultante
ordene este vetor
imprima o vetor ordenado
calcule e imprima a soma de todos os racionais apontados pelo vetor
ao final, mude de linha
retorne 0
Seu programa deve liberar toda a mem´oria alocada:*/
int main() {
    srand(0);
    int n = ler_tamanho();
    if (n == -1) return 1;
    struct racional **vetor = (struct racional **) malloc(n * sizeof(struct racional *));
    for (int i = 0; i < n; i++) {
        long int num, den;
        printf("Insira o numerador e o denominador do racional %d:\n", i + 1);
        scanf("%ld %ld", &num, &den);
        vetor[i] = cria_r(num, den);
    }
    for (int i = 0; i < n; i++) {
        if (vetor[i] != NULL) {
            imprime_r(vetor[i]);
            printf(" ");
        }
    }
    int j = 0;

    // Remove os racionais inválidos
    for (int i = 0; i < n; i++) {
        if (vetor[i] != NULL && valido_r(vetor[i])) {
            vetor[j] = vetor[i];
            j++;
        } else {
            destroi_r(&vetor[i]);
        }
    }
    n = j;
    printf("\n");
    // Imprime o vetor resultante
    for (int i = 0; i < n; i++) {
        imprime_r(vetor[i]);
        printf(" ");
    }
    printf("\n");
    // Ordena o vetor
    qsort(vetor, n, sizeof(struct racional *), compara_r);

    // Imprime o vetor ordenado
    for (int i = 0; i < n; i++) {
        imprime_r(vetor[i]);
        printf(" ");
    }
    printf("\n");

    // Calcula e imprime a soma de todos os racionais apontados pelo vetor
    struct racional *soma = cria_r(0, 1);
    for (int i = 0; i < n; i++) {
        struct racional *temp = soma_r(soma, vetor[i]);
        destroi_r(&soma);
        soma = temp;
    }
    imprime_r(soma);
    destroi_r(&soma);
    printf("\n");
    free(vetor);
    return 0;
}