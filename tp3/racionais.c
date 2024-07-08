#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Funcoes privadas restritas a este modulo. */
void simplifica_r(struct racional *r);
long int mdc(long int a, long int b);
long int mmc(long int a, long int b);
int aleat(long int min, long int max);

/* Cria um ponteiro para um numero racional e o inicializa com base
 * nas informacoes dos parametros. Isto eh, os campos "num" e "den"
 * da struct racional devem receber respectivamente os valores dos
 * parametros numerador e denominador.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. O racional apontado pelo ponteiro deve ser retornado
 * na forma simplificada, conforme especificado acima.
 * A funcao retorna NULL em caso de falha na alocacao. */
struct racional *cria_r(long int numerador, long int denominador) {
    if (denominador == 0) return NULL;
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = numerador;
        r->den = denominador;
        simplifica_r(r);
    }
    return r;
}

/* Cria um ponteiro para um numero racional e o inicializa com valores
 * aleatorios. O numerador e o denominador devem ser inteiros longos
 * aleatorios cujos valores variam de -max a max, onde o valor de max
 * esta no parametro.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. O racional apontado pelo ponteiro deve ser retornado
 * na forma simplificada, conforme especificado acima.
 * A funcao retorna NULL em caso de falha na alocacao */
struct racional *sorteia_r(long int max) {
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = aleat(-max, max);
        r->den = aleat(-max, max);
        simplifica_r(r);
    }
    return r;
}

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat(long int min, long int max) {
    return min + rand() % (max - min + 1);
}

/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc(long int a, long int b) {
    if (b == 0) {
        return a;
    }
    return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long int mmc(long int a, long int b) {
    return (a * b) / mdc(a, b);
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r(struct racional *r) {
    long int m = mdc(r->num, r->den);
    r->num /= m;
    r->den /= m;
    if (r->den < 0) {
        r->num *= -1;
        r->den *= -1;
    }
}

/* Libera a memoria alocada para o racional *r,
 * e aterra o ponteiro *r */
void destroi_r(struct racional **r) {
    free(*r);
    *r = NULL;
}

/* Retorna o numerador do racional *r */
long int numerador_r(struct racional *r) {
    return r->num;
}

/* Retorna o denominador do racional *r */
long int denominador_r(struct racional *r) {
    return r->den;
}

/* Retorna 1 se o racional *r eh valido ou 0 caso contrario.
 * Um racional eh invalido se o denominador for nulo. */
int valido_r(struct racional *r) {
    return r != NULL && r->den != 0;
}

/* Retorna a soma (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a soma de dois racionais validos seja
 * valido. */
struct racional *soma_r(struct racional *r1, struct racional *r2) {
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = r1->num * r2->den + r2->num * r1->den;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

/* Retorna a subtracao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a subtracao de dois racionais validos seja
 * valido. */
struct racional *subtrai_r(struct racional *r1, struct racional *r2) {
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = r1->num * r2->den - r2->num * r1->den;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

/* Retorna a multiplicacao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a multiplicacao de dois racionais validos seja
 * valido. */
struct racional *multiplica_r(struct racional *r1, struct racional *r2) {
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = r1->num * r2->num;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

/* Retorna a divisao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. Retorna NULL se nao conseguiu alocar a memoria ou
 * caso o resultado da divisao for um racional invalido.
 * --NAO eh-- matematicamente garantido que a divisao de dois racionais validos 
 * seja valido. Se o numerador do racional *r2 for 0, entao o racional 
 * resultante eh invalido. */
struct racional *divide_r(struct racional *r1, struct racional *r2) {
    if (r2->num == 0) {
        return NULL;
    }
    struct racional *r = (struct racional *) malloc(sizeof(struct racional));
    if (r != NULL) {
        r->num = r1->num * r2->den;
        r->den = r1->den * r2->num;
        simplifica_r(r);
    }
    return r;
}

/* Retorna -1 se *r1 < *r2; 0 se *r1 == *r2; 1 se *r1 > *r2.
 * Quem chama esta funcao deve garantir que *r1 e *r2 sejam valido e nao NULL.
 * Atencao: faca a comparacao normalizando os denominadores pelo MMC.
 * Fazer a comparacao baseado na divisao de numerador pelo denominador
 * pode resultar em erro numerico e falsear o teste. */
int compara_r(struct racional *r1, struct racional *r2) {
    long int m = mmc(r1->den, r2->den);
    long int n1 = r1->num * (m / r1->den);
    long int n2 = r2->num * (m / r2->den);
    if (n1 < n2) {
        return -1;
    } else if (n1 > n2) {
        return 1;
    }
    return 0;
}

/* Imprime um racional *r.
   A impressao deve respeitar o seguinte:
   - nao use espacos em branco apos o numero e nao mude de linha;
   - o formato de saida deve ser "r.num/r.den", a menos dos casos abaixo;
   - se o numerador for igual a 0, deve ser impresso somente zero;
   - se o denominador for igual a 1, deve ser impresso somente o numerador;
   - se o numerador e denominador forem o mesmo valor, deve imprimir somente 1;
   - se o racional for negativo, o sinal deve ser impresso antes do numero;
   - se ambos numerador e denominador forem negativos, o racional eh positivo;
   - se o racional for invalido, deve imprimir a mensagem "INVALIDO" */
void imprime_r(struct racional *r) {
    if (r == NULL || r->den == 0) {
        printf("INVALIDO");
    } else if (r->num == 0) {
        printf("0");
    } else if (r->den == 1) {
        printf("%ld", r->num);
    } else if (r->num == r->den) {
        printf("1");
    } else {
        printf("%ld/%ld", r->num, r->den);
    }
}