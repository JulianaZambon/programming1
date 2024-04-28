#include "polinomio.h"
#include <stdio.h>
#include <math.h>

/*
   Recebe dois polinômios de primeiro ou segundo grau e retorna a soma dos dois
   Retorno é código de erro
   Retorno do resultado é em p3
*/
int soma(struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    if (!p3)
        return -1; // Verifica se o ponteiro para o resultado é nulo

    // Soma os polinômios
    p3->a = p1.a + p2.a;
    p3->b = p1.b + p2.b;
    p3->c = p1.c + p2.c;

    return 0;
}

/*
   Recebe dois polinômios de primeiro ou segundo grau e retorna a subtração dos dois
   Retorno é código de erro
   Retorno do resultado é em p3
*/
int subtracao(struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    if (!p3)
        return -1; // Verifica se o ponteiro para o resultado é nulo

    // Subtrai os polinômios
    p3->a = p1.a - p2.a;
    p3->b = p1.b - p2.b;
    p3->c = p1.c - p2.c;

    return 0;
}

/*
   Recebe dois polinômios de primeiro grau e retorna a multiplicação dos dois
   Retorno é código de erro
   Retorno do resultado é em p3
*/
int multiplicacao(struct polinomio p1, struct polinomio p2, struct polinomio *p3)
{
    if (!p3)
        return -1; // Verifica se o ponteiro para o resultado é nulo

    if (p1.a != 0 || p2.a != 0)
        return -1; // Verifica se os polinômios são de primeiro grau

    // Multiplica os polinômios de primeiro grau
    p3->a = p1.b * p2.b;               // Coeficiente de x^2: produtos dos coeficientes de x
    p3->b = p1.b * p2.c + p1.c * p2.b; // Coeficiente de x: soma dos produtos cruzados
    p3->c = p1.c * p2.c;               // Termo constante: produto dos termos constantes

    return 0;
}

/*
   Retorna a raiz de um polinômio de primeiro grau
   Retorno é código de erro
   Retorno da raiz do polinômio é em raiz
*/
int resolve1(struct polinomio p1, double *raiz)
{
    if (!raiz)
        return -1; // Verifica se o ponteiro para a raiz é nulo
    if (p1.b == 0)
        return -1; // Verifica se o coeficiente b é zero para evitar divisão por zero

    // Calcula a raiz
    *raiz = -p1.c / p1.b;

    return 0;
}

/*
   Retorna as raízes de um polinômio de segundo grau
   struct raizes é uma struct com dois campos, raiz1 e raiz2
   Retorno é código de erro
   Retorno da raiz do polinômio é em raizes
*/
int resolve2(struct polinomio p1, struct raizes *raizes)
{
    if (!raizes)
        return -1; // Verifica se o ponteiro para raizes é nulo
    if (p1.a == 0)
        return -1; // Verifica se o coeficiente a é zero, pois nesse caso não é um polinômio de segundo grau

    // Calcula o delta
    double delta = p1.b * p1.b - 4 * p1.a * p1.c;

    // Verifica se o delta é negativo
    if (delta < 0)
        return -1;

    // Calcula as raízes
    raizes->raiz1 = (-p1.b + sqrt(delta)) / (2 * p1.a);
    raizes->raiz2 = (-p1.b - sqrt(delta)) / (2 * p1.a);

    return 0;
}
