#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar informações do aluno
struct Aluno {
    char nome[50];
    float notas[3]; // Assumindo que há duas notas por aluno
};

// Função para calcular a média das notas de um aluno
float calcularMedia(float *notas) {
    return (notas[0] + notas[1]) / 2.0;
}

// Função para determinar a situação do aluno
char *SituacaodoAluno(float media) {
    if (media >= 7.0)
        return "APROVADO";
    else
        return "REPROVADO";
}

int main() {
    FILE *arquivoDeEntrada, *arquivoDeSaida;
    char entrada[] = "DadosEntrada.csv.txt";
    char saida[] = "SituacaoFinal.csv.txt";
    char linha[100];
    struct Aluno aluno;

    // Abrir arquivo de entrada
    arquivoDeEntrada = fopen(entrada, "r");
    if (arquivoDeEntrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Abrir arquivo de saída
    arquivoDeSaida = fopen(saida, "w");
    if (arquivoDeSaida == NULL) {
        perror("Erro ao abrir o arquivo de saída.\n");
        fclose(arquivoDeEntrada);
        return 1;
    }

    // Ler dados do arquivo de entrada, calcular média e escrever no arquivo de saída
    while (fgets(linha, sizeof(linha), arquivoDeEntrada) != NULL) {
        sscanf(linha, "%[^,],%f,%f", aluno.nome, &aluno.notas[0], &aluno.notas[1]);
        
        float media = calcularMedia(aluno.notas);
        char *situacaoFinal = SituacaodoAluno(media);
        
        // Escrever no arquivo de saída
        fprintf(arquivoDeSaida, "%s,%.2f,%s\n", aluno.nome, media,situacaoFinal );
    }

    // Fechar arquivos
    fclose(arquivoDeEntrada);
    fclose(arquivoDeSaida);

    printf("Processo concluido. Verifique o arquivo SituacaoFinal.csv.\n");

    return 0;
}