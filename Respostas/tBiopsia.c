#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"

struct tBiopsia{
    char nomePaciente[100];
    char CPF[15];
    tLesao **lesoes;
    int qntdLesoes;
    char nomeMedico[100];
    char CRM[11];
    char dataStr[13];
};

struct tLesao{
    char rotulo[3];
    char diagnostico[50];
    char regiao[50];
    int tamanho;
};

tBiopsia *criaBiopsia(char *nomePaciente, char *CPF,
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

    for(int i=0; i<biopsia->qntdLesoes; i++){
        biopsia->lesoes[i] = (tLesao *)calloc(1, sizeof(tLesao));
        strncpy(biopsia->lesoes[i]->rotulo, lesoes[i]->rotulo, 3*sizeof(char));
        strncpy(biopsia->lesoes[i]->diagnostico, lesoes[i]->diagnostico, 50*sizeof(char));
        strncpy(biopsia->lesoes[i]->regiao, lesoes[i]->regiao, 50*sizeof(char));
        biopsia->lesoes[i]->tamanho = lesoes[i]->tamanho;
    }

    return biopsia;
}

/**
 * Função que recebe o ponteiro genérico (que deve conter uma biopsia) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaBiopsia(void *dado){
    if(dado != NULL){
        tBiopsia *biopsia = (tBiopsia *)dado;
        for(int i=0; i<biopsia->qntdLesoes; i++){
            free(biopsia->lesoes[i]);
        }
        free(biopsia);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma biopsia) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaBiopsia(void *dado){
    if(dado == NULL){
        printf("biopsia não encontrada\n");
        exit(1);
    }

    tBiopsia *biopsia = (tBiopsia *)dado;

    printf("PACIENTE: %s\n", biopsia->nomePaciente);
    printf("CPF: %s\n\n", biopsia->CPF);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for(int i=0; i<biopsia->qntdLesoes; i++){
        printf("%s - %s - %s - %dMM\n\n", biopsia->lesoes[i]->rotulo, biopsia->lesoes[i]->diagnostico, biopsia->lesoes[i]->regiao, biopsia->lesoes[i]->tamanho);
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
void imprimeEmArquivoBiopsia(void *dado, char *path){

    if(dado != NULL){
        char caminhoArquivo[100];
        FILE *pArquivo = NULL;

        sprintf(caminhoArquivo, "%s/%s", path, NOME_ARQUIVO_BIOPSIA);

        pArquivo = fopen(caminhoArquivo, "wb");
    
        if (pArquivo == NULL) {
            printf("Não foi possível abrir o arquivo\n");
            exit(1);
        }

        tBiopsia *biopsia = (tBiopsia *)dado;

        fwrite(biopsia, sizeof(tBiopsia), 1, pArquivo);

        for(int i=0; i<biopsia->qntdLesoes; i++){
            fwrite(biopsia->lesoes[i], sizeof(tLesao), 1, pArquivo);
        }
        
        fclose(pArquivo);
    }

}
