#include "polinomio.h"
#include <stdio.h>

int main()
{
    struct polinomio p1 = {1, -3, 2}; // 1x^2 - 3x + 2
    struct polinomio p2 = {2, 1, -1}; // 2x^2 + 1x - 1
    struct polinomio p3;
    struct raizes raizes;
    double raiz;

    // Teste da função 'soma'
    if (soma(p1, p2, &p3) == 0)
        printf("Soma: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);
    else
        printf("Erro ao somar polinômios.\n");

    // Teste da função 'subtração'
    if (subtracao(p1, p2, &p3) == 0)
        printf("Subtração: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);
    else
        printf("Erro ao subtrair polinômios.\n");

    /*  Teste da função 'multiplicação'
        definindo polinômios de primeiro grau, tendo em vista
        que a função multiplicação só aceita polinômios de primeiro grau */
    struct polinomio p1_primeiro_grau = {0, 3, -5}; // 3x - 5
    struct polinomio p2_primeiro_grau = {0, -2, 4}; // -2x + 4

    if (multiplicacao(p1_primeiro_grau, p2_primeiro_grau, &p3) == 0)
        printf("Multiplicação: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);
    else
        printf("Erro ao multiplicar polinômios.\n");

    // Cálculo da raiz do polinômio de primeiro grau
    struct polinomio p3_primeiro_grau = {0, 5, -10}; // 5x - 10
    if (resolve1(p3_primeiro_grau, &raiz) == 0)
        printf("Raiz do polinômio de primeiro grau: %.6f\n", raiz);
    else
        printf("Erro ao resolver polinômio de primeiro grau.\n");

    // Cálculo das raízes do polinômio de segundo grau
    if (resolve2(p1, &raizes) == 0)
        printf("Raízes do polinômio de segundo grau: %f e %f\n", raizes.raiz1, raizes.raiz2);
    else
        printf("Erro ao resolver polinômio de segundo grau.\n");

    return 0;
}
