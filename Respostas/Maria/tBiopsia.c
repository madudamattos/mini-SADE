#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"
#include "tLesao.h"

struct tBiopsia{
    char nomePaciente[100];
    char CPF[15];
    tLesao **lesoes;
    int qntdLesoes;
    char nomeMedico[100];
    char CRM[11];
    char dataStr[13];
};

tBiopsia *CriaBiopsia(char *nomePaciente, char *CPF,
                      tLesao** lesoes, int qntdLesoes,
                      char *nomeMedico, char *CRM, char *dataStr){
    printf("b\n");
    tBiopsia *biopsia = (tBiopsia *)calloc(1, sizeof(tBiopsia));
    printf("C\n");

    strncpy(biopsia->nomePaciente, nomePaciente, sizeof(biopsia->nomePaciente) - 1);
    strncpy(biopsia->CPF, CPF, sizeof(biopsia->CPF) - 1);
    strncpy(biopsia->nomeMedico, nomeMedico, sizeof(biopsia->nomeMedico) - 1);
    strncpy(biopsia->CRM, CRM, sizeof(biopsia->CRM) - 1);
    strncpy(biopsia->dataStr, dataStr, sizeof(biopsia->dataStr) - 1);
    printf("d\n");

    biopsia->qntdLesoes = qntdLesoes;
    biopsia->lesoes = (tLesao **)calloc(qntdLesoes, sizeof(tLesao *));
    printf("e\n");
    biopsia->lesoes = ClonaVetorLesoes(lesoes, qntdLesoes);
    printf("f\n");
    RetornaQtdLesoesParaCirurgia(biopsia->lesoes, biopsia->qntdLesoes);
    printf("g\n");

    printf("vetor lesoes: "); 
    ImprimeVetorLesoes(biopsia->lesoes, biopsia->qntdLesoes);

    if(RetornaQtdLesoesParaCirurgia(biopsia->lesoes, biopsia->qntdLesoes) <= 0){
        return NULL;
    }
    printf("h\n");
    return biopsia;
}

/**
 * Função que recebe o ponteiro genérico (que deve conter uma biopsia) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void DesalocaBiopsia(void *dado){
    if(dado != NULL){
        tBiopsia *biopsia = (tBiopsia *)dado;
        DesalocaLesoes(biopsia->lesoes, biopsia->qntdLesoes);
        free(biopsia);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void ImprimeNaTelaBiopsia(void *dado){
    if(dado == NULL){
        printf("não foi possivel imprimir a biopsia\n");
        exit(1);
    }

    tBiopsia *biopsia = (tBiopsia *)dado;

    printf("PACIENTE: %s\n", biopsia->nomePaciente);
    printf("CPF: %s\n\n", biopsia->CPF);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    
    for(int i=0; i<biopsia->qntdLesoes; i++){
        if(RetornaCirurgia(biopsia->lesoes[i])){
            ImprimeLesao(biopsia->lesoes[i]);
        }
    }

    printf("%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);

    printf("%s\n", biopsia->dataStr);

}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void ImprimeEmArquivoBiopsia(void *dado, char *path){
    if(dado == NULL){
        printf("não foi possivel imprimir a biopsia em arquivo\n");
        return;
    }

    if(dado != NULL){
        char caminhoArquivo[100];
        FILE *pArquivo = NULL;

        sprintf(caminhoArquivo, "%s/%s", path, NOME_ARQUIVO_BIOPSIA);

        pArquivo = fopen(caminhoArquivo, "a");
    
        if (pArquivo == NULL) {
            printf("Não foi possível abrir o arquivo\n");
            exit(1);
        }

        tBiopsia *biopsia = (tBiopsia *)dado;

        fprintf(pArquivo,"PACIENTE: %s\n", biopsia->nomePaciente);
        fprintf(pArquivo,"CPF: %s\n\n", biopsia->CPF);
        fprintf(pArquivo,"SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
        
        for(int i=0; i<biopsia->qntdLesoes; i++){
            if(RetornaCirurgia(biopsia->lesoes[i])){
                ImprimeLesaoArquivo(pArquivo, biopsia->lesoes[i]);
            }
        }

        fprintf(pArquivo,"%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);

        fprintf(pArquivo,"%s\n", biopsia->dataStr);
        }

}
