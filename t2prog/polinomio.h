#include <stdio.h>

struct polinomio
{
    int a;
    int b;
    int c;
};

struct raizes
{
    double raiz1;
    double raiz2;
};

/*  recebe dois polinômios de primeiro ou segundo grau e retorna a soma dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int soma(struct polinomio p1, struct polinomio p2, struct polinomio *p3);

/*  recebe dois polinômios de primeiro ou segundo grau e retorna a subtração dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int subtracao(struct polinomio p1, struct polinomio p2, struct polinomio *p3);

/*  recebe dois polinômios de primeiro grau e retorna a multiplicação dos dois
    retorno é código de erro
    retorno do resultado é em p3*/
int multiplicacao(struct polinomio p1, struct polinomio p2, struct polinomio *p3);

/*  retorna a raiz de um polinômio de primeiro grau
    retorno é código de erro
    retorno da raiz do polinômio é em raiz*/
int resolve1(struct polinomio p1, double *raiz);

/*  retorna as raizes de um polinômio de segundo grau
    struct raizes é uma struct com dois campos, raiz1 e raiz2
    retorno é código de erro
    retorno da raiz do polinômio é em raizes*/
int resolve2(struct polinomio p1, struct raizes *raizes);
