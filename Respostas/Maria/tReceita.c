#include "tReceita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tReceita{
    char nomePaciente[100];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char instrucoes[MAX_TAM_INSTRUCOES];
    int qntd;
    char nomeMedico[100];
    char CRM[20];
    char dataStr[20];
};


tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr){
    
    tReceita *receita = (tReceita *)calloc(1, sizeof(tReceita));

    strncpy(receita->nomePaciente, nomePaciente, sizeof(receita->nomePaciente) - 1);
    receita->tipoUso = tipoUso;
    strncpy(receita->nomeMedicamento, nomeMedicamento, sizeof(receita->nomeMedicamento) - 1);
    strncpy(receita->tipoMedicamento, tipoMedicamento, sizeof(receita->tipoMedicamento) - 1);
    strncpy(receita->instrucoes, instrucoes, sizeof(receita->instrucoes) - 1);
    receita->qntd = qntd;
    strncpy(receita->nomeMedico, nomeMedico, sizeof(receita->nomeMedico) - 1);
    strncpy(receita->CRM, CRM, sizeof(receita->CRM) - 1);
    strncpy(receita->dataStr, dataStr, sizeof(receita->dataStr) - 1);

    return receita;                    
}

void desalocaReceita(void *dado){
    if(dado != NULL){
        free(dado);
    }
}

void imprimeNaTelaReceita(void *dado){
    if(dado != NULL){
        tReceita *receita = (tReceita *)dado;
        printf("RECEITUARIO\n");
        printf("NOME: %s\n\n", receita->nomePaciente);
        printf("USO ");
            if(receita->tipoUso == ORAL) printf("ORAL\n\n");
            else if(receita->tipoUso == TOPICO) printf("TOPICO\n\n");
        printf("%s\n\n", receita->nomeMedicamento);
        printf("%d %s\n\n", receita->qntd, receita->tipoMedicamento);

        printf("%s\n\n", receita->instrucoes);
       
        printf("%s (%s)\n", receita->nomeMedico, receita->CRM);
        
        printf("%s\n", receita->dataStr);
    }
}

/**
 * Função que recebe um ponteiro genérico (que deve conter uma receita) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoReceita(void *dado, char *path){
    FILE *pReceita = NULL;
    char caminho[100];

    sprintf(caminho, "%s/%s", path, NOME_ARQUIVO_RECEITA);

    pReceita = fopen(caminho, "a");
    
    if(dado != NULL){
        tReceita *receita = (tReceita *)dado;
        fprintf(pReceita, "RECEITUARIO\n");
        fprintf(pReceita, "NOME: %s\n\n", receita->nomePaciente);
        fprintf(pReceita, "USO ");
            if(receita->tipoUso == ORAL) fprintf(pReceita, "ORAL\n\n");
            else if(receita->tipoUso == TOPICO) fprintf(pReceita, "TOPICO\n\n");
        fprintf(pReceita, "%s\n", receita->nomeMedicamento);
        fprintf(pReceita, "%d %s\n\n", receita->qntd, receita->tipoMedicamento);

        fprintf(pReceita, "%s\n\n", receita->instrucoes);
       
        fprintf(pReceita, "%s (%s)\n", receita->nomeMedico, receita->CRM);

        fprintf(pReceita, "%s\n\n", receita->dataStr);
    }

    fclose(pReceita);

    // if(dado != NULL){
    //     char *caminhoArquivo[100];
    //     FILE *pArquivo = NULL;

    //     sprintf(caminhoArquivo, "%s/%s", path, NOME_ARQUIVO_RECEITA);

    //     pArquivo = fopen(caminhoArquivo, "wb");
    
    //     if (pArquivo == NULL) {
    //         printf("Não foi possível abrir o arquivo\n");
    //         exit(1);
    //     }

    //     tReceita *receita = (tReceita *)dado;

    //     fwrite(receita, sizeof(tReceita), 1, pArquivo);
        
    //     fclose(pArquivo);
    // }

}
