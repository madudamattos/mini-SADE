#include "tRelatorio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tRelatorio{
    int totalPacientes;
    int mediaIdade;
    int totalFeminino;
    int totalMasculino;
    int totalOutros;
    int mediaTamLesoes;
    int totalLesoes;
    int totalCirurgias;
    int totalCrioterapias;
};

tRelatorio *CriaRelatorio(int totalPacientes, int mediaIdade, int totalFeminino, int totalMasculino, int totalOutros, int mediaTamLesoes, int totalLesoes, int totalCirurgias, int totalCrioterapias){
    
    tRelatorio *Relatorio = (tRelatorio *)calloc(1, sizeof(tRelatorio));
    if(Relatorio == NULL){
        printf("Erro ao alocar memória para Relatorio\n");
        exit(1);
    }

    Relatorio->totalPacientes = totalPacientes;
    Relatorio->mediaIdade = mediaIdade;
    Relatorio->totalFeminino = totalFeminino;
    Relatorio->totalMasculino = totalMasculino;
    Relatorio->totalOutros = totalOutros;
    Relatorio->mediaTamLesoes = mediaTamLesoes;
    Relatorio->totalLesoes = totalLesoes;
    Relatorio->totalCirurgias = totalCirurgias;
    Relatorio->totalCrioterapias = totalCrioterapias;
    
    return Relatorio;                    
}

void DesalocaRelatorio(void *dado){
    if(dado != NULL){
        free(dado);
    }
}

void ImprimeNaTelaRelatorio(void *dado){
    if(dado != NULL){
        tRelatorio *Relatorio = (tRelatorio *)dado;
        printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", Relatorio->totalPacientes);
        printf("IDADE MEDIA: %d\n", Relatorio->mediaIdade);
        printf("DISTRIBUICAO POR GENERO:\n");
        printf("- FEMININO: %d\n", Relatorio->totalFeminino);
        printf("- MASCULINO: %d\n", Relatorio->totalMasculino);
        printf("- OUTROS: %d\n", Relatorio->totalOutros);
        printf("TAMANHO MEDIO DAS LESOES: %d\n", Relatorio->mediaTamLesoes);
        printf("NUMERO TOTAL DE LESOES: %d\n", Relatorio->totalLesoes);
        printf("NUMERO TOTAL DE CIRURGIAS: %d\n", Relatorio->totalCirurgias);
        printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n\n", Relatorio->totalCrioterapias);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma Relatorio) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void ImprimeEmArquivoRelatorio(void *dado, char *path){
    FILE *pRelatorio = NULL;
    char caminho[100];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_RELATORIO);

    pRelatorio = fopen(caminho, "a");
    
    if(dado != NULL){
        tRelatorio *Relatorio = (tRelatorio *) dado;
        fprintf(pRelatorio, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", Relatorio->totalPacientes);
        fprintf(pRelatorio, "IDADE MEDIA: %d\n", Relatorio->mediaIdade);
        fprintf(pRelatorio, "DISTRIBUICAO POR GENERO:\n");
        fprintf(pRelatorio, "- FEMININO: %d\n", Relatorio->totalFeminino);
        fprintf(pRelatorio, "- MASCULINO: %d\n", Relatorio->totalMasculino);
        fprintf(pRelatorio, "- OUTROS: %d\n", Relatorio->totalOutros);
        fprintf(pRelatorio, "TAMANHO MEDIO DAS LESOES: %d\n", Relatorio->mediaTamLesoes);
        fprintf(pRelatorio, "NUMERO TOTAL DE LESOES: %d\n", Relatorio->totalLesoes);
        fprintf(pRelatorio, "NUMERO TOTAL DE CIRURGIAS: %d\n", Relatorio->totalCirurgias);
        fprintf(pRelatorio, "NUMERO TOTAL DE CRIOTERAPIA: %d\n\n", Relatorio->totalCrioterapias);
    }

    fclose(pRelatorio);

}
