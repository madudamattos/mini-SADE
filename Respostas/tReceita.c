#include "tReceita.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TAM_NOME_MEDICAMENTO 50
#define MAX_TAM_TIPO_MEDICAMENTO 50
#define MAX_TAM_INSTRUCOES 300
#define NOME_ARQUIVO_RECEITA "receita.txt"

typedef enum
{
    ORAL,
    TOPICO
} eTipoUso;

struct tReceita{
    char *nomePaciente;
    eTipoUso tipoUso;
    char *nomeMedicamento;
    char *tipoMedicamento;
    char *instrucoes;
    int qntd;
    char *nomeMedico;
    char *CRM;
    char *dataStr;
};


tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr){
    
    tReceita *receita = (tReceita *)calloc(1, sizeof(tReceita));

    receita->nomePaciente = nomePaciente;
    receita->nomeMedicamento = nomeMedicamento;
    receita->tipoMedicamento = tipoMedicamento;
    receita->instrucoes = instrucoes;
    receita->nomeMedico = nomeMedico;
    receita->CRM = CRM;
    receita->dataStr = dataStr;

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

}
