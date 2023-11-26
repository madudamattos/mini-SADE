#include <stdio.h>
#include <stdlib.h>

#define TAM_NOME_ARQUIVO 300

// Função para verificar se um arquivo existe
int fileExists(const char * filename){
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

int main(){
    char caminho[TAM_NOME_ARQUIVO];

    printf("################################################\nDIGITE O CAMINHO DO BANCO DE DADOS:\n################################################\n");

    fgets(caminho, sizeof(caminho), stdin); // lê o caminho do banco de dados

    // remove o '\n' do final da string
    caminho[strcspn(caminho, "\n")] = 0;

    // Lista dos arquivos do banco de dados
    char* arquivos[] = {"secretarios.bin", "medicos.bin", "pacientes.bin", "consultas.bin", "lesoes.bin", "fila_impressao.bin"};
    int numArquivos = 6;

    // Verifica se cada arquivo existe. Se não existir, cria o arquivo.
    for (int i = 0; i < numArquivos; i++) {
        char arquivo[TAM_NOME_ARQUIVO];
        snprintf(arquivo, sizeof(arquivo), "%s/%s", caminho, arquivos[i]);

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

    return 0;
}