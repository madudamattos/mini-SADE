#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tBiopsia.h"

struct tPessoa{
    ATOR classeAtor;
    char nome[100];
    char cpf[12];
    char dataNascimento[13];
    char telefone[15];
    char genero[10];
    char user[20];
    char senha[20];
    char CRM[11];
    char nivelAcesso[10];
    tPaciente *paciente;
};

struct tPaciente{
    char diabetes[4];
    char fumante[4];
    char alergias[4];
    char histCancer[4];
    int tipoPele;
    int qntdLesoes;
    tLesao** lesoes;
};

tPessoa* CriaPessoa(){
    tPessoa* p = (tPessoa*) calloc(1, sizeof(tPessoa));
    
    p->paciente = NULL;

    return p;
};

tPessoa* CadastraPessoa(){
    tPessoa* pessoa = CriaPessoa();

    printf("NOME COMPLETO:");
    scanf("%[^\n]%*c", pessoa->nome);
    printf("CPF:");
    scanf("%[^\n]%*c", pessoa->cpf);
    printf("DATA DE NASCIMENTO:");
    scanf("%[^\n]%*c", pessoa->dataNascimento);
    printf("TELEFONE:");
    scanf("%[^\n]%*c", pessoa->telefone);
    printf("GENERO:");
    scanf("%[^\n]%*c", pessoa->genero);
    
    return pessoa;
}

void CadastraSecretario(){
    printf("#################### CADASTRO SECRETARIO #######################\n");

    tPessoa* secretario = CadastraPessoa();

    secretario->classeAtor = SECRETARIO;

    printf("NOME DE USUARIO:");
    scanf("%[^\n]%*c", secretario->user);
    printf("SENHA:");
    scanf("%[^\n]%*c", secretario->senha);
    printf("NIVEL DE ACESSO:");
    scanf("%[^\n]%*c", secretario->nivelAcesso);
    
    //ESCREVE EM ARQUIVO

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n###############################################################\n");
}

void CadastraMedico(){
    printf("#################### CADASTRO MEDICO #######################\n");

    tPessoa* medico = CadastraPessoa();

    medico->classeAtor = MEDICO;

    printf("CRM");
    scanf("%[^\n]%*c", medico->CRM);
    printf("NOME DE USUARIO:");
    scanf("%[^\n]%*c", medico->user);
    printf("SENHA:");
    scanf("%[^\n]%*c", medico->senha);

    //ESCREVE EM ARQUIVO

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n###############################################################\n");
}

void CadastraPaciente(){
    printf("#################### CADASTRO PACIENTE #######################\n");

    tPessoa* paciente = CadastraPessoa();

    paciente->classeAtor = PACIENTE;

    paciente->paciente = calloc(1, sizeof(tPaciente));

    //ESCREVE EM ARQUIVO

    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n###############################################################\n");
}

void DesalocaPessoa(tPessoa* p){
    if(p != NULL){
        if(p->paciente != NULL){
            if(p->paciente->lesoes != NULL){
                //DesalocaLesoes(p->paciente->lesoes);
                free(p->paciente->lesoes);
            }
            free(p->paciente);
        }

        free(p);
    }
    
}

char* RetornaCPFPessoa(tPessoa* p){
    return p->cpf;
}

char* RetornaCRMMedico(tPessoa* p){
    if(p->classeAtor == MEDICO){
        return p->CRM;
    }

    return NULL;
}

char* RetornaNivelAcessoPessoa(tPessoa* p){
    return p->nivelAcesso;
}

char* RetornaNomePessoa(tPessoa* p){
    return p->nome;
} 

char* RetornaDataNascimetoPessoa(tPessoa* p){
    return p->dataNascimento;
}

ATOR RetornaClasseAtor(tPessoa* p){
    return p->classeAtor;
}