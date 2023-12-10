#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tSade.h"
#include "tMenu.h"
#include "tFila.h"
#include "tConsulta.h"

struct tSade{
    int qtdPacientes;
    int qtdMedicos;
    int qtdSecretarios;
    tPessoa **pacientes;
    tPessoa **medicos;
    tPessoa **secretarios;
    tFila *fila;
};


tSade* CriaSADE(){
    tSade* sade = (tSade*) calloc(1, sizeof(tSade));

    sade->qtdPacientes = 0;
    sade->qtdMedicos = 0;
    sade->qtdSecretarios = 0;
    sade->pacientes = NULL;
    sade->medicos = NULL;
    sade->secretarios = NULL;

    sade->fila = criaFila();

    return sade;
}

void InicializaSADE(tSade* sade, char *MenuCaminhoBancoDados){

}

void ExecutaSADE(tSade* sade, char *caminhoBancoDados){

    NIVELACESSO acesso = RealizaLogin(caminhoBancoDados);
    int opcao = -1;
    //imprimir menu principal

    switch (acesso){
    case ADMIN:
        while(opcao != 8){
            MenuPrincipalAdmin();
        
            scanf("%d", &opcao);

            if(opcao == 1) AddSecretarioSADE(sade);
            else if(opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            //else if(opcao == 4) RealizaConsulta();
            //else if(opcao == 5) BuscaPacientes();
            //else if(opcao == 6) ExibeRelatorioGeral();
            //else if(opcao == 7) ImprimeFilaImpressao();

        }
        break;
    
    case USER:
        while(opcao != 8){
            MenuPrincipalUser();

            scanf("%d", &opcao);
            if (opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            //else if(opcao == 5) BuscaPacientes(sade);
            //else if(opcao == 6) ExibeRelatorioGeral();
            //else if(opcao == 7) ImprimeFilaImpressao();
        }
        break;
        
    case MED:
        while(opcao != 8){
            MenuPrincipalMedico();

            scanf("%d", &opcao);
            //if(opcao == 4) RealizaConsulta();
            //else if(opcao == 5) BuscaPacientes();
            //else if(opcao == 6) ExibeRelatorioGeral();
            //else if(opcao == 7) ImprimeFilaImpressao();
        }
        break;
    
    default:
        printf("user não identificado\n");
        exit(1);
        break;
    }

    //imprime os pacientes de teste

    for(int i=0; i<sade->qtdPacientes; i++){
        printf("PACIENTE %d\nNOME:%s, CPF:%s\n", i, sade->pacientes[i]->nome, sade->pacientes[i]->cpf);
    }
    //imprime os secretarios
    //imprime os medicos

}

void FinalizaSADE(tSade* sade, char *caminhoBancoDados){

    // passa as informações todas pros arquivos

    //desaloca os vetores 
    for(int i = 0; i < sade->qtdSecretarios; i++){
        DesalocaPessoa(sade->secretarios[i]);
        free(sade->secretarios[i]);
    }
    free(sade->secretarios);

    for(int i = 0; i < sade->qtdMedicos; i++){
        DesalocaPessoa(sade->medicos[i]);
        free(sade->medicos[i]);
    }
    free(sade->medicos);

    for(int i = 0; i < sade->qtdPacientes; i++){
        DesalocaPessoa(sade->pacientes[i]);
        free(sade->pacientes[i]);
    }
    free(sade->pacientes);

    desalocaFila(sade->fila); 

    free(sade);
}

int RealizaLogin(char *caminhoBancaDados){
    int login;

    printf("######################## ACESSO MINI-SADE ######################\nDIGITE SEU LOGIN:");
    scanf("%d", &login);
    printf("DIGITE SUA SENHA:");
    scanf("%*d");
    printf("###############################################################\n");
    
    return login;
}

void AddSecretarioSADE(tSade* sade){
    sade->qtdSecretarios++;
    
    sade->secretarios = realloc(sade->secretarios, sizeof(tPessoa *) * sade->qtdSecretarios);
    
    sade->secretarios[sade->qtdSecretarios-1] = CadastraSecretario();

}

void AddMedicoSADE(tSade* sade){
    sade->qtdMedicos++;

    sade->medicos = realloc(sade->medicos, sizeof(tPessoa *) * sade->qtdMedicos);

    sade->medicos[sade->qtdMedicos-1] = CadastraMedico();
}

void AddPacienteSADE(tSade* sade){
    sade->qtdPacientes++;

    sade->pacientes = realloc(sade->pacientes, sizeof(tPessoa *) * sade->qtdPacientes);

    sade->pacientes[sade->qtdPacientes-1] = CadastraPaciente();
} 

// void BuscaPacientes(tSade* sade){
//     char nomePaciente[100];
//     int qtdPacientesEncontrados = 0;
//     tPessoa **pacientesEncontrados = NULL;
//     int i;

//     printf("#################### BUSCAR PACIENTES #######################\nNOME DO PACIENTE:");

//     scanf("%[^\n]%*c", nomePaciente);

//     printf("############################################################\n");

//     printf("#################### BUSCAR PACIENTES #######################\n");

//     for(i=0; i<sade->qtdPacientes; i++){
//         if(strcmp(sade->pacientes[i]->nome, nomePaciente) == 0){
//             qtdPacientesEncontrados = 1;
//             if(qtdPacientesEncontrados == 1){
//                 printf("PACIENTES ENCONTRADOS:\n");
//             }
//             pacientesEncontrados = realloc(pacientesEncontrados, sizeof(tPessoa *) * qtdPacientesEncontrados);
//             pacientesEncontrados[qtdPacientesEncontrados] = sade->pacientes[i];
//         }
//     }

//     ImprimeNaTelaBusca(pacientesEncontrados, qtdPacientesEncontrados);

//     if(qtdPacientesEncontrados == 0){
//         printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
//     }

//     else{
//         printf("SELECIONE UMA OPÇÃO:\t(1) ENVIAR LISTA PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n");
//     }

//     printf("############################################################\n");

//     int opcao = 0;

//     scanf("%d", &opcao); 

//     if(opcao == 2){
//         return;
//     }

//     else{
         
//     }
//     //executa as outras funções do menu
// }

// void ImprimeNaTelaBusca(tPessoa **pacientesEncontrados, int qtdPacientesEncontrados){

//     if(qtdPacientesEncontrados == 0) return;
    
//     int i=0; 
//     for(i=0; i<qtdPacientesEncontrados; i++){
//         printf("%d - %s (%s)\n", i, pacientesEncontrados[i]->nome, pacientesEncontrados[i]->cpf);
//     }
// }

// void ImprimeEmArquivoBusca(tPessoa** pacientesEncontrados, int qtdPacientesEncontrados, char*path){
//     int i=0; 
//     for(i=0; i<qtdPacientesEncontrados; i++){
//         printf("%d - %s (%s)\n", i, pacientesEncontrados[i]->nome, pacientesEncontrados[i]->cpf);
//     }
// }