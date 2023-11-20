#include <stdio.h>
#include <stdlib.h>
#include "tEncaminhamento.h"

struct tEncaminhamento{
    char *nomePaciente;
    char *CPF;
    char *nomeEspecialidade;
    char *motivo;
    char *nomeMedico;
    char *CRM;
    char *dataStr;
};

tEncaminhamento *criaEncaminhamento(char *nomePaciente, char* CPF, 
                                    char *nomeEspecialidade, char *motivo, char *nomeMedico, char *CRM, char *dataStr){
    
    tEncaminhamento *e = (tEncaminhamento *)calloc(1, sizeof(tEncaminhamento));

    e->nomePaciente = nomePaciente;
    e->CPF = CPF;
    e->nomeEspecialidade = nomeEspecialidade;
    e->motivo = motivo;
    e->nomeMedico = nomeMedico;
    e->CRM = CRM;
    e->dataStr = dataStr;

    return e;
}


void desalocaEncaminhamento(void *dado){
    if(dado != NULL){
        free(dado);
    }

}

void imprimeNaTelaEncaminhamento(void *dado){
    
    if(dado != NULL){
        tEncaminhamento *e = (tEncaminhamento *)dado;

        printf("PACIENTE: %s\n", e->nomePaciente);
        printf("CPF: %s\n\n", e->CPF);
        printf("ESPECIALIDADE ENCAMINHADA: %s\n\n", e->nomeEspecialidade);
        printf("MOTIVO: %s\n\n", e->motivo);
        printf("%s (%s)\n", e->nomeMedico, e->CRM);
        printf("%s\n", e->dataStr);
    
    }
}

void imprimeEmArquivoEncaminhamento(void *dado, char *path){

}

#endif