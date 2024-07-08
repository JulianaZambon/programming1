#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void simplifica_r(struct racional *r);
long int mdc(long int a, long int b);
long int mmc(long int a, long int b);
int aleat(long int min, long int max);

struct racional *cria_r(long int numerador, long int denominador)
{
    if (denominador == 0)
        return NULL;
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = numerador;
        r->den = denominador;
        simplifica_r(r);
    }
    return r;
}

struct racional *sorteia_r(long int max)
{
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = aleat(-max, max);
        r->den = aleat(-max, max);
        simplifica_r(r);
    }
    return r;
}

int aleat(long int min, long int max)
{
    return min + rand() % (max - min + 1);
}

long int mdc(long int a, long int b)
{
    if (b == 0)
    {
        return a;
    }
    return mdc(b, a % b);
}

long int mmc(long int a, long int b)
{
    if (a == 0 || b == 0)
        return 0;

    return (a * b) / mdc(a, b);
}

void simplifica_r(struct racional *r)
{
    long int m = mdc(r->num, r->den);
    r->num /= m;
    r->den /= m;
    if (r->den < 0)
    {
        r->num *= -1;
        r->den *= -1;
    }
}

void destroi_r(struct racional **r)
{
    free(*r);
    *r = NULL;
}

long int numerador_r(struct racional *r)
{
    return r->num;
}

long int denominador_r(struct racional *r)
{
    return r->den;
}

int valido_r(struct racional *r)
{
    return r != NULL && r->den != 0;
}

struct racional *soma_r(struct racional *r1, struct racional *r2)
{
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = r1->num * r2->den + r2->num * r1->den;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

struct racional *subtrai_r(struct racional *r1, struct racional *r2)
{
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = r1->num * r2->den - r2->num * r1->den;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

struct racional *multiplica_r(struct racional *r1, struct racional *r2)
{
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = r1->num * r2->num;
        r->den = r1->den * r2->den;
        simplifica_r(r);
    }
    return r;
}

struct racional *divide_r(struct racional *r1, struct racional *r2)
{
    if (r2->num == 0)
    {
        return NULL;
    }
    struct racional *r = (struct racional *)malloc(sizeof(struct racional));
    if (r != NULL)
    {
        r->num = r1->num * r2->den;
        r->den = r1->den * r2->num;
        simplifica_r(r);
    }
    return r;
}

int compara_r(struct racional *r1, struct racional *r2)
{
    if (r1 == NULL || r2 == NULL)
    {
        return 0;
    }

    if (r1->den == 0 || r2->den == 0)
    {
        return 0;
    }

    long int m = mmc(r1->den, r2->den);
    long int n1 = r1->num * (m / r1->den);
    long int n2 = r2->num * (m / r2->den);

    if (n1 < n2)
    {
        return -1;
    }
    else if (n1 > n2)
    {
        return 1;
    }
    return 0;
}

void imprime_r(struct racional *r)
{
    if (r == NULL || r->den == 0)
    {
        printf("INVALIDO");
    }
    else if (r->num == 0)
    {
        printf("0");
    }
    else if (r->den == 1)
    {
        printf("%ld", r->num);
    }
    else if (r->num == r->den)
    {
        printf("1");
    }
    else
    {
        printf("%ld/%ld", r->num, r->den);
    }
}