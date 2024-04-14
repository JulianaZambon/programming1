#include <stdio.h>

//struct para armazenar um polinomio de primeiro ou segundo grau
struct polinomio {
    int grau; 
    //a multiplicacao de dois polinomios pode resultar em um polinomio 
    //de grau ate 4 (se ambos os polinômios de entrada sao de grau 2)
    float coeficientes[5];
};

//struct para armazenar as raizes de um polinomio de segundo grau
struct raizes {
    float raiz1;
    float raiz2;
};

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a soma dos dois
struct polinomio soma(struct polinomio p1, struct polinomio p2);

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a subtracao dos dois
struct polinomio subtracao(struct polinomio p1, struct polinomio p2);

// funcao para receber dois polinomios de primeiro ou segundo grau e retornar a multiplicacao dos dois
struct polinomio multiplicacao(struct polinomio p1, struct polinomio p2);

// retorna a raiz de um polinomio de primeiro grau ou -1 para indicar erro
int resolve1(struct polinomio p1);

// funcao para retornar as raizes de um polinomio de segundo grau
struct raizes resolve2(struct polinomio p1);
    
