#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tBiopsia.h"
#include "tMenu.h"

struct tPessoa{
    ATOR classeAtor;
    NIVELACESSO nivelAcesso;
    char nome[100];
    char cpf[12];
    char dataNascimento[13];
    char telefone[15];
    char genero[10];
    char user[20];
    char senha[20];
    char CRM[11];
    int diabetes;
    int fumante;
    int alergias;
    int histCancer;
    char tipoPele[4];
    int qntdLesoes;
    tLesao** lesoes;
};

tPessoa* CriaPessoa(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    tPessoa* p = (tPessoa*) calloc(1, sizeof(tPessoa));

    p->lesoes= NULL;

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

    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", secretario->user);
    printf("SENHA: ");
    scanf("%[^\n]%*c", secretario->senha);
    printf("NIVEL DE ACESSO: ");
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
    medico->nivelAcesso = MED;

    printf("CRM: ");
    scanf("%[^\n]%*c", medico->CRM);
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", medico->user);
    printf("SENHA: ");
    scanf("%[^\n]%*c", medico->senha);

    CadastroRealizado();

    scanf("%*c");

    return medico;
}

tPessoa* CadastraPaciente(){
    printf("#################### CADASTRO PACIENTE #######################\n");

    tPessoa* paciente = CadastraPessoa();

    paciente->classeAtor = PACIENTE;
    paciente->nivelAcesso = NADA;

    paciente->lesoes = NULL;

    CadastroRealizado();

    scanf("%*c");

    return paciente;
}

tPessoa* ClonaPessoa(tPessoa*p){
    if (p == NULL) {
        printf("p is NULL\n");
        return NULL;
    }

    tPessoa* clone = (tPessoa*) calloc(1, sizeof(tPessoa));
    if (clone == NULL) {
        printf("Failed to allocate memory for clone\n");
        return NULL;
    }

    clone->lesoes= NULL;

    printf("%s\n", p->nome);
    strcpy(clone->nome, p->nome);
    strcpy(clone->cpf, p->cpf);
    strcpy(clone->dataNascimento, p->dataNascimento);
    strcpy(clone->telefone, p->telefone);
    strcpy(clone->genero, p->genero);
    strcpy(clone->user, p->user);
    strcpy(clone->senha, p->senha);
    strcpy(clone->CRM, p->CRM);
    strcpy(clone->tipoPele, p->tipoPele);
    clone->diabetes = p->diabetes;
    clone->fumante = p->fumante;
    clone->alergias = p->alergias;
    clone->histCancer = p->histCancer;
    clone->qntdLesoes = p->qntdLesoes;

    if(p->lesoes != NULL){
        clone->lesoes = ClonaVetorLesoes(p->lesoes, p->qntdLesoes);
    }
    else{
        clone->lesoes = NULL;
    }

    return clone;

}

void DesalocaPessoa(tPessoa* p){
    if(p != NULL){
        if(p->lesoes != NULL){
            DesalocaLesoes(p->lesoes, p->qntdLesoes);
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

int RetornaQtdLesoesPaciente(tPessoa* p){
    return p->qntdLesoes;
}

tLesao** RetornaLesoesPaciente(tPessoa* p){
    return p->lesoes;
}

void SetaPacienteParaDiabetico(tPessoa* p){
    if(p != NULL){
        p->diabetes = 1;
    }
}

void SetaPacienteParaFumante(tPessoa* p){
    if(p != NULL){
        p->fumante = 1;
    }
}

void SetaPacienteParaAlergico(tPessoa* p){
    if(p != NULL){
        p->alergias = 1;
    }
}

void SetaPacienteParaHistoricoCancer(tPessoa* p){
    if(p != NULL){
        p->histCancer = 1;
    }
}

void SetaPacienteTipoPele(tPessoa* p, char tipoPele[]){
    if(p != NULL){
        strcpy(p->tipoPele, tipoPele);
    }
}

void AumentaQtdLesoesPaciente(tPessoa* p){
    if(p != NULL){
        p->qntdLesoes++;
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