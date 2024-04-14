#include "polinomios.h" 
#include <stdio.h>
#include <math.h> // para usar sqrt()

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a soma dos dois
struct polinomio soma(struct polinomio p1, struct polinomio p2)
{
    struct polinomio resultado;
    int grau_max = p1.grau > p2.grau ? p1.grau : p2.grau; // determina o grau máximo

    // inicializa todos os coeficientes com zero
    for (int i = 0; i <= grau_max; i++) {
        resultado.coeficientes[i] = 0;
    }

    // soma os coeficientes dos termos correspondentes
    for (int i = 0; i <= p1.grau; i++) {
        resultado.coeficientes[i] += p1.coeficientes[i];
    }
    for (int i = 0; i <= p2.grau; i++) {
        resultado.coeficientes[i] += p2.coeficientes[i];
    }

    resultado.grau = grau_max; // o grau do polinomio resultado eh o grau maximo
    return resultado;
}

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a subtracao dos dois
struct polinomio subtracao(struct polinomio p1, struct polinomio p2)
{
    struct polinomio resultado;
    int grau_max = p1.grau > p2.grau ? p1.grau : p2.grau; // determina o grau maximo

    // inicializa todos os coeficientes com zero
    for (int i = 0; i <= grau_max; i++) {
        resultado.coeficientes[i] = 0;
    }

    // subtrai os coeficientes dos termos correspondentes
    for (int i = 0; i <= p1.grau; i++) {
        resultado.coeficientes[i] += p1.coeficientes[i];
    }
    for (int i = 0; i <= p2.grau; i++) {
        resultado.coeficientes[i] -= p2.coeficientes[i];
    }

    resultado.grau = grau_max; 
    return resultado;
}

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a multiplicacao dos dois
struct polinomio multiplicacao(struct polinomio p1, struct polinomio p2) 
{
    struct polinomio resultado;
    int grau_max = p1.grau + p2.grau; // o grau do polinomio resultado eh a soma dos graus dos polinômios

    // inicializa todos os coeficientes com zero
    for (int i = 0; i <= grau_max; i++) {
        resultado.coeficientes[i] = 0;
    }

    // multiplica os coeficientes dos termos correspondentes
    for (int i = 0; i <= p1.grau; i++) {
        for (int j = 0; j <= p2.grau; j++) {
            resultado.coeficientes[i + j] += p1.coeficientes[i] * p2.coeficientes[j];
        }
    }

    resultado.grau = grau_max; 
    return resultado;
}

// retorna a raiz de um polinomio de primeiro grau ou -1 para indicar erro
int resolve1(struct polinomio p1) 
{
    if (p1.grau != 1) {
        printf("O polinomio nao eh de primeiro grau\n");
        return -1; // Retorna -1 para indicar um erro
    } else if (p1.coeficientes[1] == 0) {
        printf("O coeficiente do termo de primeiro grau eh 0\n");
        return -1; // Retorna -1 para indicar um erro
    }

    // calcula e retorna a raiz do polinomio de primeiro grau
    return -p1.coeficientes[0] / p1.coeficientes[1];
}

// funcao para retornar as raizes de um polinomio de segundo grau
struct raizes resolve2(struct polinomio p1)
{
    struct raizes r;
    if (p1.grau != 2) {
        printf("O polinomio nao eh de segundo grau\n");
        r.raiz1 = r.raiz2 = NAN; // retorna NaN para indicar um erro
        return r;
    }

    float a = p1.coeficientes[2];
    float b = p1.coeficientes[1];
    float c = p1.coeficientes[0];
    float delta = b * b - 4 * a * c;

    if (delta < 0) {
        printf("O polinomio nao possui raizes reais\n");
        r.raiz1 = r.raiz2 = NAN; // retorna NaN para indicar a ausência de raizes reais
    } else {
        // calculo das raizes 
        r.raiz1 = (-b + sqrt(delta)) / (2 * a);
        r.raiz2 = (-b - sqrt(delta)) / (2 * a);
    }

    return r;
}
