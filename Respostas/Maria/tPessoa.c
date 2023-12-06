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
    tPessoa *paciente;  
    char diabetes[4];
    char fumante[4];
    char alergias[4];
    char histCancer[4];
    int tipoPele;
    int qntdLesoes;
    tLesao** lesoes;
};

tPessoa* CriaPessoa(){
    tPessoa* pessoa = calloc(1, sizeof(tPessoa));
    
    return pessoa;
}

void CadastraSecretario(char* caminhoConfig){
    tPessoa* secretario = CriaPessoa();
}

void CadastraMedico(char* caminhoConfig){

}

void CadastraPaciente(char* caminhoConfig){

}

void DesalocaPessoa(tPessoa*){

}