#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tBiopsia.h"
#include "tMenu.h"

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
    NIVELACESSO nivelAcesso;
    tPaciente *paciente;
};

struct tPaciente{
    int diabetes;
    int fumante;
    int alergias;
    int histCancer;
    char tipoPele[3];
    int qntdLesoes;
    tLesao** lesoes;
};

tPessoa* CriaPessoa(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    tPessoa* p = (tPessoa*) calloc(1, sizeof(tPessoa));

    p->paciente = NULL;

    return p;
};

tPessoa* CadastraPessoa(){
    int c;
    
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

tPessoa* CadastraSecretario(){
    char acesso[10];

    printf("#################### CADASTRO SECRETARIO #######################\n");

    tPessoa* secretario = CadastraPessoa();

    secretario->classeAtor = SECRETARIO;

    printf("NOME DE USUARIO:");
    scanf("%[^\n]%*c", secretario->user);
    printf("SENHA:");
    scanf("%[^\n]%*c", secretario->senha);
    printf("NIVEL DE ACESSO:");
    scanf("%[^\n]%*c", acesso);
    secretario->nivelAcesso = ConverteStringNivelAcesso(acesso);
    
    CadastroRealizado();

    scanf("%*c");

    return secretario;
}

tPessoa* CadastraMedico(){
    printf("#################### CADASTRO MEDICO #######################\n");

    tPessoa* medico = CadastraPessoa();

    medico->classeAtor = MEDICO;

    printf("CRM");
    scanf("%[^\n]%*c", medico->CRM);
    printf("NOME DE USUARIO:");
    scanf("%[^\n]%*c", medico->user);
    printf("SENHA:");
    scanf("%[^\n]%*c", medico->senha);

    CadastroRealizado();

    scanf("%*c");

    return medico;
}

tPessoa* CadastraPaciente(){
    printf("#################### CADASTRO PACIENTE #######################\n");

    tPessoa* paciente = CadastraPessoa();

    paciente->classeAtor = PACIENTE;

    paciente->paciente = calloc(1, sizeof(tPaciente));
    paciente->paciente->lesoes = NULL;

    CadastroRealizado();

    scanf("%*c");

    return paciente;
}

void DesalocaPessoa(tPessoa* p){
    if(p != NULL){
        if(p->paciente != NULL){
            DesalocaPaciente(p->paciente);
        }
        free(p);
    }
}

void DesalocaPaciente(tPaciente* p){
    if(p != NULL){
        if(p->lesoes != NULL){
            DesalocaLesoes(p->lesoes, p->qntdLesoes);
            free(p->lesoes);
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

char* RetornaNomePessoa(tPessoa* p){
    return p->nome;
} 

char* RetornaDataNascimetoPessoa(tPessoa* p){
    return p->dataNascimento;
}

void SetaPacienteParaDiabetico(tPessoa* p){
    if(p->paciente != NULL){
        p->paciente->diabetes = 1;
    }
}

void SetaPacienteParaFumante(tPessoa* p){
    if(p->paciente != NULL){
        p->paciente->fumante = 1;
    }
}

void SetaPacienteParaAlergico(tPessoa* p){
    if(p->paciente != NULL){
        p->paciente->alergias = 1;
    }
}

void SetaPacienteParaHistoricoCancer(tPessoa* p){
    if(p->paciente != NULL){
        p->paciente->histCancer = 1;
    }
}

void SetaPacienteTipoPele(tPessoa* p, char tipoPele[]){
    if(p->paciente != NULL){
        strcpy(p->paciente->tipoPele, tipoPele);
    }
}

ATOR RetornaClasseAtor(tPessoa* p){
    return p->classeAtor;
}

NIVELACESSO ConverteStringNivelAcesso(const char nivelAcessoStr[]) {
    if (strcmp(nivelAcessoStr, "ADMIN") == 0) {
        return ADMIN;
    } else if (strcmp(nivelAcessoStr, "USER") == 0) {
        return USER;
    } else {
        return NADA;
    }
}

NIVELACESSO RetornaNivelAcessoPessoa(tPessoa* p){
    return p->nivelAcesso;
}

void ImprimePessoa(tPessoa* p){
    printf("#################### DADOS PESSOA #######################\n");
    printf("NOME: %s\n", p->nome);
    printf("CPF: %s\n", p->cpf);
    printf("DATA DE NASCIMENTO: %s\n", p->dataNascimento);
    printf("TELEFONE: %s\n", p->telefone);
    printf("GENERO: %s\n", p->genero);
    printf("#################### DADOS PESSOA #######################\n");
}