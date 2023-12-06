#include "tDocumento.h"
#include <stdio.h>
#include <stdlib.h>

struct tDocumento{
    void *dado;
    func_ptr_imprimeNaTela imprimeNaTela;
    func_ptr_imprimeEmArquivo imprimeEmArquivo;
    func_ptr_desaloca desaloca;
};


tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,
                          func_ptr_desaloca desaloca){

    tDocumento *doc = (tDocumento *)calloc(1, sizeof(tDocumento));
    
    if(doc == NULL){
        printf("ERRO: falha na alocação do documento\n");
        exit(1);
    }

    doc->dado = dado;
    doc->imprimeNaTela = imprimeNaTela;
    doc->imprimeEmArquivo = ImprimeEmArquivo;
    doc->desaloca = desaloca;

    return doc;
}

void desalocaDocumento(tDocumento *doc){
    if(doc != NULL){
        doc->desaloca(doc->dado);
        free(doc);
    }
}

void imprimeNaTelaDocumento(tDocumento *doc){
    doc->imprimeNaTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path){
    doc->imprimeEmArquivo(doc->dado, path);
}
