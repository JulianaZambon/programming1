#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_COMPROMISSOS 20

struct Data
{
    int dia;
    int mes;
    int ano;
};

struct Horario
{
    int hora;
    int minuto;
    int segundo;
};

struct Compromisso
{
    char texto[201]; // string de até 200 caracteres
    struct Data data;
    struct Horario horario;
};

int main()
{
    struct Compromisso compromissos[NUM_COMPROMISSOS];
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    // Inicializa o vetor de compromissos com valores aleatórios
    for (int i = 0; i < NUM_COMPROMISSOS; i++)
    {
        compromissos[i].data.dia = rand() % 20 + 1;   // Dia entre 1 e 20
        compromissos[i].data.mes = rand() % 12 + 1;   // Mês entre 1 e 12
        compromissos[i].data.ano = rand() % 4 + 2016; // Ano entre 2016 e 2019

        compromissos[i].horario.hora = rand() % 24;    // Hora entre 0 e 23
        compromissos[i].horario.minuto = rand() % 60;  // Minuto entre 0 e 59
        compromissos[i].horario.segundo = rand() % 60; // Segundo entre 0 e 59

        strcpy(compromissos[i].texto, "Compromisso de teste gerado aleatoriamente.");
    }

    // Imprime o vetor de compromissos
    printf("======== Lista de Compromissos ========\n");
    for (int i = 0; i < NUM_COMPROMISSOS; i++)
    {
        printf("Compromisso %d:\n", i + 1);
        printf("Data: %02d/%02d/%04d\n", compromissos[i].data.dia, compromissos[i].data.mes, compromissos[i].data.ano);
        printf("Horario: %02d:%02d:%02d\n", compromissos[i].horario.hora, compromissos[i].horario.minuto, compromissos[i].horario.segundo);
        printf("Texto: %s\n\n", compromissos[i].texto);
    }

    return 0;
}
