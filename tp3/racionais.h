#ifndef _LIBracionais_t_H
#define _LIBracionais_t_H

/* 
 * Tipos Abstratos de Dados - TAD's
 * Arquivo de header para TAD racional.
 * Feito em 17/08/2023 para a disciplina prog1
 * Revisado em 02/04/2024.
*/

/***************** NAO ALTERE ESTE ARQUIVO ****************************/

struct racional {
    long int num;                   /* numerador do racional          */
    long int den;                   /* denominador do racional        */
};

/* Observacoes iniciais sobre como a struct racional deve ser
 * utilizada para representar o conceito abstrato de um numero
 * racional, conforme definido na matematica:
 *
 * Os campos "num" e "den" conterao respectivamente o numerador
 * e o denominador de um racional. Diferentemente dos trabalhos
 * TP1 e TP2, esta struct nao contem o campo "valido".
 * Desta vez, cabera ao usuario testar a validade usando a funcao
 * "valido_r" caso queira.
 *
 * Esta modificacao tem fins didaticos, para que voces vejam as
 * diversas possibilidades na especificacao de um modulo.
 *
 * Nossos racionais serao sempre simplificados, isto eh, conterao
 * os menores inteiros que representam o mesmo numero racional.
 * Por exemplo, o racional 10/8 pode ser simplificado para 5/4.
 *
 * Tambem consideraremos que, caso o racional seja negativo, o
 * sinal estara sempre no numerador e nunca no denominador.
 * Por exemplo, o racional 5/-4 devera ser representado por -5/4.
 *
 * Usaremos duas funcoes que permitem que um racional seja
 * inicializado pelos usuarios deste modulo. As funcoes serao
 * "cria_r" e "sorteia_r", que sao definidas abaixo.
 *
 * Dentro do conceito de Tipos Abstratos de Dados, o usuario
 * deste modulo nunca pode violar o tipo acessando diretamente
 * seus campos "num", "den" ou "valido". Por isso este modulo
 * contera tres funcoes para que o usuario tenha acesso a estes
 * campos. As funcoes definidas abaixo sao respectivamente
 * "numerador_r", "denominador_r" e "valido_r".
 *
 * Um Tipo Abstrato de Dados tambem define as operacoes que
 * podem ser feitas sobre a abstracao do numero racional.
 * No nosso caso definiremos somente quatro operacoes, que sao:
 * somar (soma_r), subtrair (subtrai_r), multiplicar (multiplica_r)
 * e, finalmente, dividir (divede_r).
 * Isto permitira que o usuario possa realizar as quatro operacoes
 * sem ter acesso aos campos internos da struct.
 * As 4 operacoes sao especificadas abaixo.
 *
 * Para permitir que o usuario compare dois numeros racionais,
 * este modulo tambem preve uma funcao para isso, para permitir
 * operacoes abstratas equivalentes aos operadores
 * "<", "==" e ">". Os demais operadores ("<=", "!=" e ">=")
 * poderao ser implementados com o uso dos operadores logicos
 * "&&", "||" e "!".
 *
 * Finalmente, este modulo tambem preve uma funcao que imprime
 * o racional na forma convencional que o ser humano prefere.
 *
 * A seguir, as especificacoes de cada funcao deste modulo.
*/

/* Cria um ponteiro para um numero racional e o inicializa com base
 * nas informacoes dos parametros. Isto eh, os campos "num" e "den"
 * da struct racional devem receber respectivamente os valores dos
 * parametros numerador e denominador.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. O racional apontado pelo ponteiro deve ser retornado
 * na forma simplificada, conforme especificado acima.
 * A funcao retorna NULL em caso de falha na alocacao. */
struct racional *cria_r (long int numerador, long int denominador);

/* Cria um ponteiro para um numero racional e o inicializa com valores
 * aleatorios. O numerador e o denominador devem ser inteiros longos
 * aleatorios cujos valores variam de -max a max, onde o valor de max
 * esta no parametro.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. O racional apontado pelo ponteiro deve ser retornado
 * na forma simplificada, conforme especificado acima.
 * A funcao retorna NULL em caso de falha na alocacao */
struct racional *sorteia_r (long int max);

/* Libera a memoria alocada para o racional *r,
 * e aterra o ponteiro *r */
void destroi_r (struct racional **r);

/* Retorna o numerador do racional *r */
long int numerador_r (struct racional *r);

/* Retorna o denominador do racional *r */
long int denominador_r (struct racional *r);

/* Retorna 1 se o racional *r eh valido ou 0 caso contrario.
 * Um racional eh invalido se o denominador for nulo. */
int valido_r (struct racional *r);

/* Retorna a soma (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a soma de dois racionais validos seja
 * valido. */
struct racional *soma_r (struct racional *r1, struct racional *r2);

/* Retorna a subtracao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a subtracao de dois racionais validos seja
 * valido. */
struct racional *subtrai_r (struct racional *r1, struct racional *r2);

/* Retorna a multiplicacao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta funcao. Retorna NULL se nao conseguiu alocar a memoria.
 * Eh matematicamente garantido que a multiplicacao de dois racionais validos seja
 * valido. */
struct racional *multiplica_r (struct racional *r1, struct racional *r2);

/* Retorna a divisao (simplificada) dos racionais *r1 e *r2.
 * Quem chama esta funcao deve garantir que *r seja valido e nao NULL.
 * A memoria para o número racional deve ser alocada dinamicamente
 * nesta função. Retorna NULL se nao conseguiu alocar a memoria ou
 * caso o resultado da divisao for um racional invalido.
 * --NAO eh-- matematicamente garantido que a divisao de dois racionais validos 
 * seja valido. Se o numerador do racional *r2 for 0, entao o racional 
 * resultante eh invalido. */
struct racional *divide_r (struct racional *r1, struct racional *r2);

/* Retorna -1 se *r1 < *r2; 0 se *r1 == *r2; 1 se *r1 > *r2.
 * Quem chama esta funcao deve garantir que *r1 e *r2 sejam valido e nao NULL.
 * Atencao: faca a comparacao normalizando os denominadores pelo MMC.
 * Fazer a comparacao baseado na divisao de numerador pelo denominador
 * pode resultar em erro numerico e falsear o teste. */
int compara_r (struct racional *r1, struct racional *r2);

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
void imprime_r (struct racional *r);
 
#endif
