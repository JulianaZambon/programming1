#include "polinomio.h"
#include <stdio.h>
#include <math.h>

/*  recebe dois polinômios de primeiro ou segundo grau e retorna a soma dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int soma (struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    // Verifica se os polinômios são válidos
    if (p1.a == 0 && p1.b == 0 && p1.c == 0)
        return -1;
    else if (p2.a == 0 && p2.b == 0 && p2.c == 0)
        return -1;
    else if (p3 == NULL)
        return -1;

    // Soma os polinômios
    p3->a = p1.a + p2.a;
    p3->b = p1.b + p2.b;
    p3->c = p1.c + p2.c;

    return 0;
}

/*  recebe dois polinômios de primeiro ou segundo grau e retorna a subtração dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int subtracao (struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    // Verifica se os polinômios são válidos
    if (p1.a == 0 && p1.b == 0 && p1.c == 0)
        return -1;
    else if (p2.a == 0 && p2.b == 0 && p2.c == 0)
        return -1;
    else if (p3 == NULL)
        return -1;

    // Subtrai os polinômios
    p3->a = p1.a - p2.a;
    p3->b = p1.b - p2.b;
    p3->c = p1.c - p2.c;

    return 0;
}

/*  recebe dois polinômios de primeiro grau e retorna a multiplicação dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int multiplicacao (struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    // Verifica se os polinômios são válidos
    if (p1.a == 0 && p1.b == 0 && p1.c == 0)
        return -1;
    else if (p2.a == 0 && p2.b == 0 && p2.c == 0)
        return -1;
    else if (p3 == NULL)
        return -1;

    // Multiplica os polinômios
    p3->a = p1.a * p2.a; // Termo x^2
    p3->b = p1.a * p2.b + p1.b * p2.a; // Termo x
    p3->c = p1.b * p2.b; // Termo constante

    return 0;
}

/*  retorna a raiz de um polinômio de primeiro grau
    retorno é código de erro
    retorno da raiz do polinômio é em raiz*/
int resolve1 (struct polinomio p1, int *raiz)
{
    // Verifica se o polinômio é válido
    if (p1.a == 0 && p1.b == 0 && p1.c == 0)
        return -1;
    else if (raiz == NULL)
        return -1;

    // Resolve o polinômio
    *raiz = -p1.c / p1.b;

    return 0;
}

/*  retorna as raizes de um polinômio de segundo grau
    struct raizes é uma struct com dois campos, raiz1 e raiz2
    retorno é código de erro
    retorno da raiz do polinômio é em raizes*/
int resolve2 (struct polinomio p1, struct raizes *raizes)
{
    // Verifica se o polinômio é válido
    if (p1.a == 0 && p1.b == 0 && p1.c == 0)
        return -1;
    else if (raizes == NULL)
        return -1;

    // Calcula o delta
    int delta = p1.b * p1.b - 4 * p1.a * p1.c;

    // Verifica se o delta é negativo
    if (delta < 0)
        return -1;

    // Calcula as raízes
    raizes->raiz1 = (-p1.b + sqrt(delta)) / (2 * p1.a);
    raizes->raiz2 = (-p1.b - sqrt(delta)) / (2 * p1.a);

    return 0;
}