#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[50];
    char telefone[20];
    char curso[50];
    float nota1;
    float nota2;
} Aluno;

// Função para calcular a media de notas dos alunos.
float calcularMedia(float nota1, float nota2)
{
    return (nota1 + nota2) / 2.0;
}

// Função para determinar se o aluno esta aprovado ou reprovado baseado nas notas.
char *SituacaoFinal(float media)
{
    if (media >= 7.0){
        return "APROVADO";
    }    
    else{
        return "REPROVADO";
    }
}

void CalculoFinal(Aluno *alunos, int TotalAlunos)
{
    FILE *arquivoSaida = fopen("SituacaoFinal.csv.txt", "w");
    if (arquivoSaida == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo de saida.\n");
        exit(1);
    }

    // Modificação feita para não incluir na no arquivo final o curso e o telefone.
    fprintf(arquivoSaida, "Nome,Nota Media,Situacao\n");

    for (int i = 0; i < TotalAlunos; i++)
    {
        float media = calcularMedia(alunos[i].nota1, alunos[i].nota2);
        const char *situacao = SituacaoFinal(media);
        fprintf(arquivoSaida, "%s,%.2f,%s\n", alunos[i].nome, media, situacao);
    }

    fclose(arquivoSaida);
}

int main()
{
    FILE *arquivoEntrada;
    Aluno alunos[100]; // total de alunos.
    int TotalAlunos = 0;

    arquivoEntrada = fopen("DadosEntrada.csv.txt", "r");
    if (arquivoEntrada == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    while (fscanf(arquivoEntrada, "%[^,],%[^,],%[^,],%f,%f\n", alunos[TotalAlunos].nome, alunos[TotalAlunos].telefone, alunos[TotalAlunos].curso, &alunos[TotalAlunos].nota1, &alunos[TotalAlunos].nota2) != EOF)
    {
        TotalAlunos++;
    }

    fclose(arquivoEntrada);

    CalculoFinal(alunos, TotalAlunos);

    printf("O Arquivo SituacaoFinal.csv foi criado com sucesso.\n");

    return 0;
}