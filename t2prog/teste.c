#include <stdio.h>
#include <math.h>
#include "polinomio.h"

int main () {
    struct polinomio p1 = {1, -5, 6};  // Polinômio com raízes 2 e 3
    struct polinomio p2 = {1, 0, -4};  // Polinômio com raízes 2 e -2
    struct polinomio p3;

    int erro = soma(p1, p2, &p3);
    if (erro != 0) {
        printf("Erro na soma\n");
        return 1;
    }
    printf("Soma: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);

    erro = subtracao(p1, p2, &p3);
    if (erro != 0) {
        printf("Erro na subtracao\n");
        return 1;
    }
    printf("Subtracao: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);

    erro = multiplicacao(p1, p2, &p3);
    if (erro != 0) {
        printf("Erro na multiplicacao\n");
        return 1;
    }
    printf("Multiplicacao: %dx^2 + %dx + %d\n", p3.a, p3.b, p3.c);

    struct raizes r;
    erro = resolve2(p1, &r);
    if (erro != 0) {
        printf("Erro na resolve2\n");
        return 1;
    }

    printf("Raizes: %.0f, %.0f\n", r.raiz1, r.raiz2);  

    return 0;
}

