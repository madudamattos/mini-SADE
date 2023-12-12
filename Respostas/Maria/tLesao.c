#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLesao.h"

struct tLesao{
    char rotulo[3];
    char diagnostico[50];
    char regiao[50];
    int tamanho;
    int cirurgia;
    int crioterapia;
};

tLesao* CriaLesao(int qtdLesoes){
    tLesao *lesao = (tLesao *)calloc(1, sizeof(tLesao));

    printf("#################### CONSULTA MEDICA #######################\nCADASTRO DE LESAO: \nDIAGNOSTICO CLINICO: ");
    scanf("%[^\n]%*c", lesao->diagnostico);
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]%*c", lesao->regiao);
    printf("TAMANHO: ");
    scanf("%d", &lesao->tamanho);
    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d", &lesao->cirurgia);
    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d", &lesao->crioterapia);
    lesao->rotulo[0] = 'L';
    lesao->rotulo[1] = '0' + qtdLesoes;
    lesao->rotulo[2] = '\0';

    return lesao;
}

void ImprimeLesao(tLesao* lesao){
    printf("%s - %s - %s - %dMM\n", lesao->rotulo, lesao->diagnostico, lesao->regiao, lesao->tamanho);
}

void ImprimeLesaoArquivo(FILE* arquivo, tLesao* lesao){
    fprintf(arquivo, "%s - %s - %s - %dMM\n", lesao->rotulo, lesao->diagnostico, lesao->regiao, lesao->tamanho);
}

void ImprimeVetorLesoes(tLesao** lesoes, int qntdLesoes){
    for(int i=0; i<qntdLesoes; i++){
        ImprimeLesao(lesoes[i]);
    }
};

int RetornaTamanhoLesao(tLesao* lesao){
    return lesao->tamanho;
}

int RetornaCirurgia(tLesao* lesao){
    return lesao->cirurgia;
}

int RetornaCrioterapia(tLesao* lesao){
    return lesao->crioterapia;
}

tLesao** ClonaVetorLesoes(tLesao** lesoes, int qntdLesoes){
    tLesao** lesoesClonadas = calloc(qntdLesoes, sizeof(tLesao*));
    for(int i=0; i<qntdLesoes; i++){
        lesoesClonadas[i] = ClonaLesao(lesoes[i]);
    }
    return lesoesClonadas;
}

tLesao* ClonaLesao(tLesao* lesao){
    tLesao* lesaoClonada = calloc(1, sizeof(tLesao));
    strcpy(lesaoClonada->rotulo, lesao->rotulo);
    strcpy(lesaoClonada->diagnostico, lesao->diagnostico);
    strcpy(lesaoClonada->regiao, lesao->regiao);
    lesaoClonada->tamanho = lesao->tamanho;
    lesaoClonada->cirurgia = lesao->cirurgia;
    lesaoClonada->crioterapia = lesao->crioterapia;
    
    return lesaoClonada;
}

void DesalocaLesao(tLesao *lesao){
    if(lesao != NULL){
        free(lesao);
    }
}

void DesalocaLesoes(tLesao** lesoes, int qntdLesoes){
    if(lesoes != NULL){
        for(int i=0; i<qntdLesoes; i++){
            DesalocaLesao(lesoes[i]);
        }
        free(lesoes);
    }
}
