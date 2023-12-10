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

    printf("a\n");

    printf("b\n");

    busca-> pacientesEncontrados = (tPessoa **)calloc(qtdPessoasEncontradas, sizeof(tPessoa *));

    printf("c\n");

    for(int i=0; i<qtdPessoasEncontradas; i++){
        printf("qtdPessoasEncontradas: %d\n", qtdPessoasEncontradas);
        busca->pacientesEncontrados[i] = ClonaPessoa(pessoasEncontradas[i]);
        printf("d\n");
    }
    busca->qtdPacientesEncontrados = qtdPessoasEncontradas;

    return busca;
}

void desalocaBusca(void *dado){
    if(dado != NULL){
        tBusca *busca = (tBusca *)dado;
        for(int i=0; i<busca->qtdPacientesEncontrados; i++){
            DesalocaPessoa(busca->pacientesEncontrados[i]);
        }
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
    
    if(dado != NULL){
        for(int i=0; i<busca->qtdPacientesEncontrados; i++){
            fprintf(pBusca, "%d - %s (%s)\n\n", i+1, RetornaNomePessoa(busca->pacientesEncontrados[i]), RetornaCPFPessoa(busca->pacientesEncontrados[i]));
        }
    }

    fclose(pBusca);
}


void imprimeNaTelaListaBusca(void *dado){
    tBusca *busca = (tBusca *)dado;

    printf("#################### BUSCAR PACIENTES #######################\n");

    if(busca->qtdPacientesEncontrados == 0){
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        return;
    }
    else{
        printf("PACIENTES ENCONTRADOS:\n");
        for(int i=0; i<busca->qtdPacientesEncontrados; i++){
            printf("%d - %s (%s)\n", i+1, RetornaNomePessoa(busca->pacientesEncontrados[i]), RetornaCPFPessoa(busca->pacientesEncontrados[i]));
        }
    }

    printf("\nSELECIONE UMA OPÇÃO:\n\t(1) ENVIAR LISTA PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n"); 
    printf("############################################################\n");
    
}
