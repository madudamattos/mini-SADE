#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSade.h"
#include "tPessoa.h"

typedef struct tPessoa tPessoa;

typedef struct tPaciente tPaciente;

typedef struct tSade tSade;

#define TAM_NOME_CAMINHO 300

// Função para verificar se um arquivo existe
int fileExists(const char * filename){
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]){
    char *caminhoConfig = argv[1];
    char caminhoPastaSaida[TAM_NOME_CAMINHO];
    char caminhoBancoDados[TAM_NOME_CAMINHO];
    
    if(argc < 2){
        printf("ERRO: Pasta de saída não foi informada\n");
        return 0;
    }

    sprintf(caminhoPastaSaida, "%s/saida/", caminhoConfig);

    //LE O BANCO DE DADOS ------------------------------------
    printf("################################################\nDIGITE O CAMINHO DO BANCO DE DADOS:");


    // lê o caminho do banco de dados
    scanf("%[^\n]%*c", caminhoBancoDados);

    printf("################################################\n");

    // Lista dos arquivos do banco de dados
    char* arquivos[] = {"secretarios.bin", "medicos.bin", "pacientes.bin", "consultas.bin", "lesoes.bin", "fila_impressao.bin"};
    int numArquivos = 6;

    // Verifica se cada arquivo existe. Se não existir, cria o arquivo
    for (int i = 0; i < numArquivos; i++) {
        char arquivo[TAM_NOME_CAMINHO + 1];
        sprintf(arquivo, "%s/%s", caminhoBancoDados, arquivos[i]);

        if (!fileExists(arquivo)) {
            FILE *file = fopen(arquivo, "wb");
            if (file == NULL) {
                printf("Não foi possível criar o arquivo %s\n", arquivo);
                return 1;
            }
            fclose(file);
        }
    }

    // Aqui você pode continuar com o restante do seu programa...

    tSade* sade = CriaSADE();

    InicializaSADE(sade, caminhoBancoDados);

    ExecutaSADE(sade, caminhoBancoDados);

    FinalizaSADE(sade, caminhoBancoDados);

    return 0;
}

