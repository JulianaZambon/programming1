#include "polinomios.h"
#include <stdio.h>
#include <math.h> 

void testar_soma() {
    struct polinomio p1 = {2, {1, 3, 2}}; // 2x^2 + 3x + 1
    struct polinomio p2 = {2, {5, 4, -1}}; // -x^2 + 4x + 5

    struct polinomio resultado = soma(p1, p2);
    
    printf("Teste de Soma\n");
    printf("Esperado: grau = 2, coeficientes = {6, 7, 1}\n");
    printf("Obtido: grau = %d, coeficientes = {%.1f, %.1f, %.1f}\n\n",
           resultado.grau, resultado.coeficientes[0], resultado.coeficientes[1], resultado.coeficientes[2]);
}

void testar_subtracao() {
    struct polinomio p1 = {2, {2, 5, 3}}; // 3x^2 + 5x + 2
    struct polinomio p2 = {2, {1, -2, 1}}; // x^2 - 2x + 1

    struct polinomio resultado = subtracao(p1, p2);
    
    printf("Teste de Subtração\n");
    printf("Esperado: grau = 2, coeficientes = {1, 7, 2}\n");
    printf("Obtido: grau = %d, coeficientes = {%.1f, %.1f, %.1f}\n\n",
           resultado.grau, resultado.coeficientes[0], resultado.coeficientes[1], resultado.coeficientes[2]);
}

void testar_multiplicacao() {
    struct polinomio p1 = {2, {1, 2, 1}}; // x^2 + 2x + 1
    struct polinomio p2 = {1, {1, 1}}; // x + 1

    struct polinomio resultado = multiplicacao(p1, p2);
    
    printf("Teste de Multiplicação\n");
    printf("Esperado: grau = 3, coeficientes = {1, 3, 3, 1}\n");
    printf("Obtido: grau = %d, coeficientes = {%.1f, %.1f, %.1f, %.1f}\n\n",
           resultado.grau, resultado.coeficientes[0], resultado.coeficientes[1], resultado.coeficientes[2], resultado.coeficientes[3]);
}

void testar_resolve1() {
    struct polinomio p1 = {1, {-8, 4}}; // 4x - 8

    float raiz = resolve1(p1);
    
    printf("Teste de Raiz de Polinômio de Primeiro Grau\n");
    printf("Esperado: raiz = 2.0\n");
    printf("Obtido: raiz = %.1f\n\n", raiz);
}

void testar_resolve2() {
    struct polinomio p1 = {2, {-3, -2, 1}}; // x^2 - 2x - 3

    struct raizes r = resolve2(p1);
    
    printf("Teste de Raízes de Polinômio de Segundo Grau\n");
    printf("Esperado: raiz1 = 3.0, raiz2 = -1.0\n");
    printf("Obtido: raiz1 = %.1f, raiz2 = %.1f\n\n", r.raiz1, r.raiz2);
}

int main() {
    testar_soma();
    testar_subtracao();
    testar_multiplicacao();
    testar_resolve1();
    testar_resolve2();
    return 0;
}

