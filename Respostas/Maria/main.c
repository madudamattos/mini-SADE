#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSade.h"
#include "tPessoa.h"

#define TAM_NOME_CAMINHO 300

int main(int argc, char *argv[]){
    char *caminhoConfig = argv[1];
    char caminhoPastaSaida[TAM_NOME_CAMINHO];
    char caminhoBancoDados[TAM_NOME_CAMINHO];
    char banco[100];
    
    if(argc < 2){
        printf("ERRO: Pasta de saída não foi informada\n");
        return 0;
    }    

    //LE O BANCO DE DADOS ------------------------------------
    printf("################################################\nDIGITE O CAMINHO DO BANCO DE DADOS:");
    // lê o caminho do banco de dados
    scanf("%[^\n]%*c", banco);
    printf("################################################\n");
    //caminhoBancoDados = "/home/madudamattos/prog2/2_trabalho/Respostas/Maria/Banco";

    sprintf(caminhoPastaSaida, "%s/saida/", caminhoConfig);
    sprintf(caminhoBancoDados, "%s/%s", caminhoConfig, banco);

    printf("CaminhoPastaSaida: %s\n", caminhoPastaSaida);
    printf("CaminhoBancoDados: %s\n", caminhoBancoDados);

    tSade* sade = CriaSADE();

    //caminhoBancoDados = InicializaSADE(sade, caminhoPastaSaida);

    InicializaSADE(sade, caminhoBancoDados);

    printf("INICIALIZOU SADE\n");

    ExecutaSADE(sade, caminhoPastaSaida);

    printf("EXECUTOU SADE\n");

    FinalizaSADE(sade, caminhoBancoDados);

    printf("FINALIZOU SADE\n");

    return 0;
}

