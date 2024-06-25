#include <stdio.h>
#include <string.h>

#define NUM_FUNCIONARIOS 3

struct DataNascimento
{
    int dia;
    char mes[10];
    int ano;
};

struct Funcionario
{
    char nome[31];
    int idade;
    char sexo; // M ou F
    char cpf[12]; // 11 caracteres mais o terminador nulo
    char cargo[31];
    float salario;
    struct DataNascimento dataNascimento;
    int codigoSetor;
};

int main()
{
    struct Funcionario funcionarios[NUM_FUNCIONARIOS];

    // Entrada de dados
    for (int i = 0; i < NUM_FUNCIONARIOS; i++)
    {
        printf("Digite os dados do funcionário %d:\n", i + 1);

        printf("Nome: ");
        fgets(funcionarios[i].nome, sizeof(funcionarios[i].nome), stdin);
        funcionarios[i].nome[strcspn(funcionarios[i].nome, "\n")] = '\0'; 

        printf("Idade: ");
        scanf("%d", &funcionarios[i].idade);

        printf("Sexo (M/F): ");
        scanf(" %c", &funcionarios[i].sexo);

        printf("CPF: ");
        scanf("%s", funcionarios[i].cpf);

        printf("Cargo: ");
        getchar(); // Limpar o buffer do \n deixado pelo scanf
        fgets(funcionarios[i].cargo, sizeof(funcionarios[i].cargo), stdin);
        funcionarios[i].cargo[strcspn(funcionarios[i].cargo, "\n")] = '\0'; // Remove newline

        printf("Salário: ");
        scanf("%f", &funcionarios[i].salario);

        printf("Data de Nascimento (dia mes ano): ");
        scanf("%d %s %d", &funcionarios[i].dataNascimento.dia, funcionarios[i].dataNascimento.mes, 
        &funcionarios[i].dataNascimento.ano);

        printf("Código do Setor: ");
        scanf("%d", &funcionarios[i].codigoSetor);

        getchar(); // Limpar o buffer do \n deixado pelo scanf
        printf("\n");
    }

    // Impressão de Dados

    for (int i = 0; i < NUM_FUNCIONARIOS; i++)
    {
        printf("Dados do funcionário %d:\n", i + 1);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Idade: %d\n", funcionarios[i].idade);
        printf("Sexo: %c\n", funcionarios[i].sexo);
        printf("CPF: %s\n", funcionarios[i].cpf);
        printf("Cargo: %s\n", funcionarios[i].cargo);
        printf("Salário: %.2f\n", funcionarios[i].salario);
        printf("Data de Nascimento: %d %s %d\n", funcionarios[i].dataNascimento.dia, 
        funcionarios[i].dataNascimento.mes, funcionarios[i].dataNascimento.ano);
        printf("Código do Setor: %d\n\n", funcionarios[i].codigoSetor);
    }

    return 0;
}
