#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBusca.h"
#include "tPessoa.h"

struct tBusca{
    tPessoa** pacientesEncontrados;
    int qtdPacientesEncontrados;
};


tBusca* criaListaBusca(tPessoa** pessoasEncontradas, int qtdPessoasEncontradas){
    tBusca *busca = (tBusca *)calloc(1, sizeof(tBusca));

    busca-> pacientesEncontrados = (tPessoa **)calloc(qtdPessoasEncontradas, sizeof(tPessoa *));

    for(int i=0; i<qtdPessoasEncontradas; i++){
        printf("qtdPessoasEncontradas: %d\n", qtdPessoasEncontradas);
        busca->pacientesEncontrados[i] = pessoasEncontradas[i];
    
    }
    busca->qtdPacientesEncontrados = qtdPessoasEncontradas;

    return busca;
}

void desalocaBusca(void *dado){
    if(dado != NULL){
        tBusca *busca = (tBusca *)dado;
        free(busca->pacientesEncontrados);
        free(busca);
    }

}


void imprimeEmArquivoListaBusca(void *dado, char* path){
    tBusca *busca = (tBusca *)dado;
    FILE *pBusca = NULL;
    char caminho[100];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_BUSCA);

    pBusca = fopen(caminho, "a");
    
    if(pBusca == NULL){
        printf("ERRO: Não foi possível abrir o arquivo de busca\n");
        return;
    }

    if(dado != NULL){
        for(int i=0; i<busca->qtdPacientesEncontrados; i++){
            fprintf(pBusca, "%d - %s (%s)\n\n", i+1, RetornaNomePessoa(busca->pacientesEncontrados[i]), RetornaCPFPessoa(busca->pacientesEncontrados[i]));
        }
    }

    fclose(pBusca);
}


void imprimeNaTelaListaBusca(void *dado){
    tBusca *busca = (tBusca *)dado;

    for(int i=0; i<busca->qtdPacientesEncontrados; i++){
        printf("%d - %s (%s)\n\n", i+1, RetornaNomePessoa(busca->pacientesEncontrados[i]), RetornaCPFPessoa(busca->pacientesEncontrados[i]));
    }
    
}
