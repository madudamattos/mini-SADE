#define TAM_NOME_CAMINHO 300

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tSade.h"
#include "tMenu.h"
#include "tFila.h"
#include "tConsulta.h"
#include "tBusca.h"
#include "tRelatorio.h"

struct tSade{
    int qtdPacientes;
    int qtdMedicos;
    int qtdSecretarios;
    tPessoa **pacientes;
    tPessoa **medicos;
    tPessoa **secretarios;
    tPessoa *usuarioLogado;
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
    sade->usuarioLogado = NULL;

    sade->fila = criaFila();

    return sade;
}

void InicializaSADE(tSade* sade, char* caminhoBancoDados){
    //LE O BANCO DE DADOS ------------------------------------
    printf("################################################\nDIGITE O CAMINHO DO BANCO DE DADOS:");


    // lê o caminho do banco de dados
    //scanf("%[^\n]%*c", caminhoBancoDados);
    caminhoBancoDados = "/home/madudamattos/prog2/2_trabalho/Respostas/Maria/Banco";

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
                exit(1);
            }
            fclose(file);
        }
    }

}

int fileExists(const char * filename){
    FILE *file;
    if ((file = fopen(filename, "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}

void ExecutaSADE(tSade* sade, char *caminhoPastaSaida){
    char c;
    // sade->usuarioLogado = RealizaLogin(sade);
    // NIVELACESSO acesso = usuarioLogado->nivelAcesso;
    
    NIVELACESSO acesso = RealizaLogin(sade);
    int opcao = -1;
    //imprimir menu principal

    switch (acesso){
    case ADMIN:
        while(opcao != 8){
            while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalAdmin();
        
            scanf("%d", &opcao);

            if(opcao == 1) AddSecretarioSADE(sade);
            else if(opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            else if(opcao == 4) RealizaConsulta(sade);
            else if(opcao == 5) BuscaPacientes(sade);
            //else if(opcao == 6) ExibeRelatorioGeral();
            else if(opcao == 7) ExecutaFilaImpressao(sade, caminhoPastaSaida);
        }
        break;
    
    case USER:
        while(opcao != 8){
            while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalUser();

            scanf("%d", &opcao);
            if (opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            else if(opcao == 5){
                BuscaPacientes(sade);
                break;
            }
            //else if(opcao == 6) ExibeRelatorioGeral();
            else if(opcao == 7) ExecutaFilaImpressao(sade, caminhoPastaSaida);
        }
        break;
        
    case MED:
        while(opcao != 8){
            while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalMedico();

            scanf("%d", &opcao);
            if(opcao == 4) RealizaConsulta(sade);
            else if(opcao == 5){
                BuscaPacientes(sade);
                break;
            }
            //else if(opcao == 6) ExibeRelatorioGeral();
            else if(opcao == 7) ExecutaFilaImpressao(sade, caminhoPastaSaida);
        }
        break;
    
    default:
        printf("user não identificado\n");
        exit(1);
        break;
    }

}

void FinalizaSADE(tSade* sade, char *caminhoBancoDados){

    // passa as informações todas pros arquivos
    

    //desaloca os vetores 
    for(int i = 0; i < sade->qtdSecretarios; i++){
        DesalocaPessoa(sade->secretarios[i]);
    }
    free(sade->secretarios);

    for(int i = 0; i < sade->qtdMedicos; i++){
        DesalocaPessoa(sade->medicos[i]);
    }
    free(sade->medicos);

    for(int i = 0; i < sade->qtdPacientes; i++){
        DesalocaPessoa(sade->pacientes[i]);
    }
    free(sade->pacientes);

    desalocaFila(sade->fila); 

    free(sade);
}

tFila* RetornaFilaSADE(tSade* sade){
    return sade->fila;
}

tPessoa* RetornaUsuarioLogado(tSade* sade){
    return sade->usuarioLogado;
}

int RealizaLogin(tSade* sade){
    int login;

    printf("######################## ACESSO MINI-SADE ######################\nDIGITE SEU LOGIN:");
    scanf("%d", &login);
    printf("DIGITE SUA SENHA:");
    scanf("%*d");
    printf("###############################################################\n");
    
    return login;
}

tPessoa* LocalizaPacienteCPF(tSade* sade, char cpf[]){
   
    for(int i=0; i<sade->qtdPacientes; i++){
        if(strcmp(RetornaCPFPessoa(sade->pacientes[i]), cpf) == 0){
            return sade->pacientes[i];
        }
    }

    return NULL;
}

tPessoa* LocalizaSecretarioCPF(tSade* sade, char cpf[]){
   
    for(int i=0; i<sade->qtdSecretarios; i++){
        if(strcmp(RetornaCPFPessoa(sade->secretarios[i]), cpf) == 0){
            return sade->secretarios[i];
        }
    }

    return NULL;
}

tPessoa* LocalizaMedicoCPF(tSade* sade, char cpf[]){
   
    for(int i=0; i<sade->qtdMedicos; i++){
        if(strcmp(RetornaCPFPessoa(sade->medicos[i]), cpf) == 0){
            return sade->medicos[i];
        }
    }

    return NULL;
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

void BuscaPacientes(tSade* sade){
    char nomePaciente[100];
    int qtdPacientesEncontrados = 0;
    tPessoa **pacientesEncontrados = NULL;
    int i;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("#################### BUSCAR PACIENTES #######################\nNOME DO PACIENTE:");

    scanf("%[^\n]%*c", nomePaciente);

    //localiza os pacientes e armazena num vetor clone
    for(i=0; i<sade->qtdPacientes; i++){
        if(strcmp(RetornaNomePessoa(sade->pacientes[i]), nomePaciente) == 0){
            qtdPacientesEncontrados++;

            pacientesEncontrados = realloc(pacientesEncontrados, sizeof(tPessoa *) * qtdPacientesEncontrados);
            pacientesEncontrados[qtdPacientesEncontrados-1] = sade->pacientes[i];
        }
    }

    tBusca* busca = criaListaBusca(pacientesEncontrados, qtdPacientesEncontrados);

    free(pacientesEncontrados);

    printf("#################### BUSCAR PACIENTES #######################\n");

    if(qtdPacientesEncontrados == 0){
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        return;
    }
    else{
        printf("PACIENTES ENCONTRADOS:\n");
        imprimeNaTelaListaBusca(busca);

        printf("\nSELECIONE UMA OPÇÃO:\n\t(1) ENVIAR LISTA PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n############################################################\n"); 
    }

    int opcao = 0;

    scanf("%d", &opcao); 

    if(qtdPacientesEncontrados == 0){
        return;
    }
    else{
        switch (opcao){
        case 1:
            //envia busca para a fila de impressão
            insereDocumentoFila(sade->fila, busca, imprimeNaTelaListaBusca, imprimeEmArquivoListaBusca, desalocaBusca);

            while(getchar() != '\n');
            printf("#################### BUSCAR PACIENTES #######################\nLISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n############################################################\n");
            scanf("%*c");
            break;
        case 2:
            //retorna ao menu principal
            return;
        default:
            break;
        }
    }

}

void ExecutaFilaImpressao(tSade* sade, char *caminhoPastaSaida){

    printf("################### FILA DE IMPRESSAO MEDICA #####################\nESCOLHA UMA OPCAO:\n\t(1) EXECUTAR FILA DE IMPRESSAO\n\t(2) RETORNAR AO MENU ANTERIOR\n############################################################\n");

    int opcao = 0;

    scanf("%d", &opcao);

    if(opcao == 1){
        imprimeFila(sade->fila, caminhoPastaSaida);
    }
    else if(opcao == 2){
        return;
    }
    
}