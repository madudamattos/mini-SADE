#include "tFila.h"
#include "tDocumento.h"
#include <stdlib.h>
#include <stdio.h>

struct tFila{
    int qtdDocumentos;
    tDocumento **documentos;
};

tFila *criaFila(){
    tFila *f = (tFila *)calloc(1, sizeof(tFila));
    
    if(f == NULL){
        printf("Erro ao alocar memoria para a fila\n");
        exit(1);
    }

    f->documentos = NULL;
    f->qtdDocumentos = 0;

    return f;
}

void desalocaFila(tFila *f){
    if(f != NULL){
        for(int i = 0; i < f->qtdDocumentos; i++){
            desalocaDocumento(f->documentos[i]);
        }
        free(f->documentos);
        free(f);
    }
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                         func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                         func_ptr_desaloca desaloca){
    if(f == NULL){
        printf("fila recebida invalida");
    }

    tDocumento * doc = criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);

    (f->qtdDocumentos)++;

    f->documentos = (tDocumento **)realloc(f->documentos, f->qtdDocumentos * sizeof(tDocumento *));

    f->documentos[f->qtdDocumentos - 1] = doc;
}

int quantidadeDocumentosNaFila(tFila *f){
    return f->qtdDocumentos;
}

void imprimeFila(tFila *f, char *path){
    printf("################### FILA DE IMPRESSAO MEDICA #####################\nEXECUTANDO FILA DE IMPRESSÃO:\n");

    for(int i = 0; i< f->qtdDocumentos; i++){
        imprimeNaTelaDocumento(f->documentos[i]);
        
        imprimeEmArquivoDocumento(f->documentos[i], path);
    }
    
    printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU PRINCIPAL\n###########################################################\n");

    scanf("%*c");
}
