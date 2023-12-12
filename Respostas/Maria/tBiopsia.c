#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"
#include "tLesao.h"
#include "tPessoa.h"

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
    tBiopsia *biopsia = (tBiopsia *)calloc(1, sizeof(tBiopsia));

    strncpy(biopsia->nomePaciente, nomePaciente, sizeof(biopsia->nomePaciente) - 1);
    strncpy(biopsia->CPF, CPF, sizeof(biopsia->CPF) - 1);
    strncpy(biopsia->nomeMedico, nomeMedico, sizeof(biopsia->nomeMedico) - 1);
    strncpy(biopsia->CRM, CRM, sizeof(biopsia->CRM) - 1);
    strncpy(biopsia->dataStr, dataStr, sizeof(biopsia->dataStr) - 1);

    biopsia->qntdLesoes = qntdLesoes;
    biopsia->lesoes = (tLesao **)calloc(qntdLesoes, sizeof(tLesao *));

    biopsia->lesoes = ClonaVetorLesoes(lesoes, qntdLesoes);

    int qtdLesoesParaCirurgia = 0;

    for(int i=0; i<biopsia->qntdLesoes; i++){
        if(RetornaCirurgia(biopsia->lesoes[i])){
            qtdLesoesParaCirurgia++;
        }
    }

    if(qtdLesoesParaCirurgia <= 0){
        return NULL;
    }

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
    FILE *pBiopsia = NULL;
    char caminho[100];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_BIOPSIA);

    pBiopsia = fopen(caminho, "a");
    
    if(dado != NULL){
        tBiopsia *biopsia = (tBiopsia *)dado;
        fprintf(pBiopsia, "PACIENTE: %s\n", biopsia->nomePaciente);
        fprintf(pBiopsia, "NOME: %s\n\n", biopsia->nomePaciente);
        
        fprintf(pBiopsia, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");

        for(int i=0; i<biopsia->qntdLesoes; i++){
            if(RetornaCirurgia(biopsia->lesoes[i])){
                ImprimeLesaoArquivo(pBiopsia, biopsia->lesoes[i]);
            }
        }

        fprintf(pBiopsia, "%s (%s)\n", biopsia->nomeMedico, biopsia->CRM);

        fprintf(pBiopsia, "%s\n\n", biopsia->dataStr);
    }

    fclose(pBiopsia);
}
