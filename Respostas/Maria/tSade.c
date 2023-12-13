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
    int qtdLesoes;
    int *qtdLesoesPacientes;
    tPessoa **pacientes;
    tPessoa **medicos;
    tPessoa **secretarios;
    tPessoa *usuarioLogado;
    tLesao *** lesoes;
    tFila *fila;
    int primeiroUso;
};

tSade* CriaSADE(){
    tSade* sade = (tSade*) calloc(1, sizeof(tSade));

    sade->qtdPacientes = 0;
    sade->qtdMedicos = 0;
    sade->qtdSecretarios = 0;
    sade->qtdLesoes = 0;
    sade->pacientes = NULL;
    sade->medicos = NULL;
    sade->secretarios = NULL;
    sade->usuarioLogado = NULL;
    sade->lesoes = NULL;
    sade->qtdLesoesPacientes = NULL;
    sade->primeiroUso = 0;

    sade->fila = criaFila();

    return sade;
}

void InicializaSADE(tSade* sade, char* caminhoBancoDados){

    // Lista dos arquivos do banco de dados
    char* arquivos[] = {"secretarios.bin", "medicos.bin", "pacientes.bin", "consultas.bin", "lesoes.bin", "fila_impressao.bin"};
    int numArquivos = 6;

    // Verifica se cada arquivo existe. Se não existir, cria o arquivo
    for (int i = 0; i < numArquivos; i++) {
        char arquivo[TAM_NOME_CAMINHO + 1];
        sprintf(arquivo, "%s/%s", caminhoBancoDados, arquivos[i]);

        if (!fileExists(arquivo)){
            FILE *file = fopen(arquivo, "wb");
            //verifica o primeiro uso do programa;
            if (file == NULL) {
                printf("Não foi possível criar o arquivo %s\n", arquivo);
                exit(1);
            }
            fclose(file);

            sade->primeiroUso = 1;
        }
    }
    printf("primeiro uso: %d\n", sade->primeiroUso);

    if(sade->primeiroUso == 1){
        
        return;
    }
    else{
        //le os arquivos binarios caso nao seja o primeiro uso
        printf("1\n");
        LeBinarioPacientes(sade, caminhoBancoDados);

        printf("2\n");
        LeBinarioLesoes(sade, caminhoBancoDados);

        printf("3\n");
        LeBinarioSecretarios(sade, caminhoBancoDados);

        LeBinarioMedicos(sade, caminhoBancoDados);

        //LeBinarioConsulta(sade, caminhoBancoDados);
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
    NIVELACESSO acesso;
    
    printf("\nimprime SADE:------------------------\n");
    printf("qtdPacientes: %d\n", sade->qtdPacientes);
    printf("qtdMedicos: %d\n", sade->qtdMedicos);
    printf("qtdSecretarios: %d\n", sade->qtdSecretarios);
    printf("primeiroUso: %d\n", sade->primeiroUso);

    printf("vetores sade:\n");

    for(int i=0 ; i<sade->qtdPacientes; i++){
        printf("--- paciente %d:\n", i);
        ImprimePessoa(sade->pacientes[i]);
    }

    for(int i=0 ; i<sade->qtdSecretarios; i++){
        printf("--- secretario %d:\n", i);
        ImprimePessoa(sade->secretarios[i]);
    }

    for(int i=0 ; i<sade->qtdMedicos; i++){
        printf("--- medico %d:\n", i);
        ImprimePessoa(sade->medicos[i]);
    }

    printf("vetores lesoes:\n");
    //imprimeLesoes
    for(int i=0; i<sade->qtdPacientes; i++){
        ImprimeVetorLesoes(sade->lesoes[i], sade->qtdLesoesPacientes[i]);
    }

    printf("INICIA PROGRAMA ------------------------:\n\n");

    //EM CASO DE PRIMEIRO USO CADASTRA SECRETARIO
    if(sade->primeiroUso == 1){
        sade->qtdSecretarios++;
        sade->secretarios = realloc(sade->secretarios, sizeof(tPessoa *) * sade->qtdSecretarios); 
        sade->secretarios[sade->qtdSecretarios-1] = CadastraSecretario();
    }
    
    sade->usuarioLogado = RealizaLogin(sade);

    if(RetornaUsuarioLogado(sade) == NULL){
        printf("USUARIO NAO ENCONTRADO\n");
        exit(1);
    }

    acesso = RetornaNivelAcessoPessoa(sade->usuarioLogado);
    
    int opcao = -1;
    //imprimir menu principal

    switch (acesso){
    case ADMIN:
        while(opcao != 8){
            //while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalAdmin();
        
            scanf("%d", &opcao);

            if(opcao == 1) AddSecretarioSADE(sade);
            else if(opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            else if(opcao == 4) RealizaConsulta(sade);
            else if(opcao == 5) BuscaPacientes(sade);
            else if(opcao == 6) ExibeRelatorioGeral(sade);
            else if(opcao == 7) ExecutaFilaImpressao(sade, caminhoPastaSaida);
        }
        break;
    
    case USER:
        while(opcao != 8){
            //while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalUser();

            scanf("%d", &opcao);
            if (opcao == 2) AddMedicoSADE(sade);
            else if(opcao == 3) AddPacienteSADE(sade);
            else if(opcao == 5){
                BuscaPacientes(sade);
                break;
            }
            else if(opcao == 6) ExibeRelatorioGeral(sade);
            else if(opcao == 7) ExecutaFilaImpressao(sade, caminhoPastaSaida);
        }
        break;
        
    case MED:
        while(opcao != 8){
            //while(c=getchar() != '\n' && c != EOF);
            MenuPrincipalMedico();

            scanf("%d", &opcao);
            if(opcao == 4) RealizaConsulta(sade);
            else if(opcao == 5){
                BuscaPacientes(sade);
                break;
            }
            else if(opcao == 6) ExibeRelatorioGeral(sade);
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

    CriaLesoesSade(sade);

    // passa as informações todas pros arquivos
    
    EscreveBinarioPacientes(sade, caminhoBancoDados);

    EscreveBinarioLesoes(sade, caminhoBancoDados);

    EscreveBinarioSecretarios(sade, caminhoBancoDados);

    EscreveBinarioMedicos(sade, caminhoBancoDados);

    //EscreveBinarioConsulta(sade, caminhoBancoDados);

    //desaloca os vetores 

    //desaloca lesoes
    for(int i=0; i<sade->qtdPacientes; i++){
        DesalocaLesoes(sade->lesoes[i], sade->qtdLesoesPacientes[i]);
    }
    free(sade->lesoes);
    free(sade->qtdLesoesPacientes);

    //desaloca secretarios
    for(int i = 0; i < sade->qtdSecretarios; i++){
        DesalocaPessoa(sade->secretarios[i]);
    }
    free(sade->secretarios);

    //desaloca medicos
    for(int i = 0; i < sade->qtdMedicos; i++){
        DesalocaPessoa(sade->medicos[i]);
    }
    free(sade->medicos);

    //desaloca pacientes
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

tPessoa* LocalizaPacienteCPF(tSade* sade, char cpf[]){
   
    for(int i=0; i<sade->qtdPacientes; i++){
        if(strcmp(RetornaCPFPessoa(sade->pacientes[i]), cpf) == 0){
            return sade->pacientes[i];
        }
    }

    return NULL;
}

tPessoa* RealizaLogin(tSade* sade){
    char senha[20];
    char login[20];

    printf("######################## ACESSO MINI-SADE ######################\nDIGITE SEU LOGIN:");
    scanf("%[^\n]%*c", login);
    printf("DIGITE SUA SENHA:");
    scanf("%[^\n]%*c", senha);
    printf("###############################################################\n");

    int encontrou = 0;

    for(int i=0; i<sade->qtdSecretarios; i++){
        if(strcmp(RetornaLoginPessoa(sade->secretarios[i]), login) == 0 && strcmp(RetornaSenhaPessoa(sade->secretarios[i]), senha) == 0){
            encontrou = 1;
            return sade->secretarios[i];
        }
    }

    for(int i=0; i<sade->qtdMedicos; i++){
        if(strcmp(RetornaLoginPessoa(sade->medicos[i]), login) == 0 && strcmp(RetornaSenhaPessoa(sade->medicos[i]), senha) == 0){
            encontrou = 1;
            return sade->medicos[i];
        }
    }

    if(encontrou == 0){
        printf("LOGIN OU SENHA INCORRETOS\n");
        return NULL;
    }
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
    int c;
    while(c=getchar() != '\n' && c != EOF);
    sade->qtdSecretarios++;
    
    sade->secretarios = realloc(sade->secretarios, sizeof(tPessoa *) * sade->qtdSecretarios);
    
    sade->secretarios[sade->qtdSecretarios-1] = CadastraSecretario();

    scanf("%*c");
}

void AddMedicoSADE(tSade* sade){
    int c;
    while(c=getchar() != '\n' && c != EOF);

    sade->qtdMedicos++;

    sade->medicos = realloc(sade->medicos, sizeof(tPessoa *) * sade->qtdMedicos);

    sade->medicos[sade->qtdMedicos-1] = CadastraMedico();
}

void AddPacienteSADE(tSade* sade){
    int c;
    while(c=getchar() != '\n' && c != EOF);

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

void ExibeRelatorioGeral(tSade* sade){
    int totalPacientes = sade->qtdPacientes;
    int mediaIdade = 0;
    int totalFeminino = 0;
    int totalMasculino = 0;
    int totalOutros = 0;
    int mediaTamLesoes = 0;
    int totalLesoes = 0;
    int totalCirurgias = 0;
    int totalCrioterapias = 0;
    int totalPacientesAtendidos = 0;
    char genero[20];

    for(int i=0; i<sade->qtdPacientes; i++){
    
        if(RetornaAtendidoPaciente(sade->pacientes[i]) == 1){
            totalPacientesAtendidos++;

            if(RetornaLesoesPaciente(sade->pacientes[i]) != NULL){
                mediaTamLesoes += RetornaSomaTamanhoLesoesPessoa(sade->pacientes[i]);
                totalLesoes += RetornaQtdLesoesPaciente(sade->pacientes[i]);
                totalCirurgias += RetornaQtdLesoesParaCirurgia(sade->pacientes[i]);
                totalCrioterapias += RetornaQtdLesoesParaCrioterapia(sade->pacientes[i]);
            }
        }
        
        mediaIdade += RetornaIdadePessoa(sade->pacientes[i]);

        strcpy(genero, RetornaGeneroPessoa(sade->pacientes[i]));

        if(strcmp(genero, "FEMININO") == 0) totalFeminino++;
        else if(strcmp(genero, "MASCULINO") == 0) totalMasculino++;
        else totalOutros++;
    }
    
    sade->qtdLesoes = totalLesoes;

    if(totalLesoes != 0){
        mediaTamLesoes = mediaTamLesoes / totalLesoes;
    }

    if(totalPacientes != 0){
        mediaIdade = mediaIdade / totalPacientes;
    }
    
    printf("i\n");
    tRelatorio *relatorio = CriaRelatorio(totalPacientesAtendidos, mediaIdade, totalFeminino, totalMasculino, totalOutros, mediaTamLesoes, totalLesoes, totalCirurgias, totalCrioterapias);

    printf("#################### RELATORIO GERAL #######################\n");
    
    ImprimeNaTelaRelatorio(relatorio);
    
    printf("SELECIONE UMA OPÇÃO:\n\t(1) ENVIAR PARA IMPRESSAO\n\t(2) RETORNAR AO MENU PRINCIPAL\n###########################################################\n");
    
    int opcao = 0;
    scanf("%d%*c", &opcao); 

    if(opcao == 1){
        insereDocumentoFila(sade->fila, relatorio, ImprimeNaTelaRelatorio, ImprimeEmArquivoRelatorio, DesalocaRelatorio);

        printf("#################### RELATORIO GERAL #######################\nRELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        scanf("%*c");
    }

    //DesalocaRelatorio(relatorio);

    //free(genero);
    
    return;
}

void ExecutaFilaImpressao(tSade* sade, char *caminhoPastaSaida){

    int opcao = 0;
    int c;

    while(1){
        MenuFilaImpressao();
        scanf("%d", &opcao);

        if(opcao == 1){
            imprimeFila(sade->fila, caminhoPastaSaida);
            while(c=getchar() != '\n' && c != EOF);
            scanf("%*c");
        }
        else if(opcao == 2){
            break;
        }

    }

}

void SetaPrimeiroUsoSade(tSade* sade){
    sade->primeiroUso = 1;
}

void EscreveBinarioPacientes(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/pacientes.bin", caminhoBancoDados);
    
    //printf("caminho arquivo pacientes: %s\n", caminhoArquivo);

    FILE *pArquivo = fopen(caminhoArquivo, "wb");

    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario pacientes\n");
        return;
    }
    
    fwrite(&sade->qtdPacientes, sizeof(int), 1, pArquivo);

    for(int i=0; i<sade->qtdPacientes; i++){
        tPessoa *paciente = sade->pacientes[i];
        EscreveBinarioPessoa(pArquivo, paciente);
        //EscreveBinarioLesoesPessoa(pArquivo, paciente);
    }

    fclose(pArquivo);
}

void EscreveBinarioLesoes(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/lesoes.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "wb");

    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario lesoes\n");
        return;
    }

    fwrite(&sade->qtdLesoes, sizeof(int), 1, pArquivo);

    for(int i=0; i<sade->qtdPacientes; i++){
        fwrite(&sade->qtdLesoesPacientes[i], sizeof(int), 1, pArquivo);
    }

    for(int i=0; i<sade->qtdPacientes; i++){
        tPessoa *paciente = sade->pacientes[i];
        EscreveBinarioLesoesPessoa(pArquivo, paciente);
    }

    fclose(pArquivo);
}

void EscreveBinarioSecretarios(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[500];
    sprintf(caminhoArquivo, "%s/secretarios.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "wb");

    //printf("caminho arquivo: %s\n", caminhoArquivo);
    
    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario secretario\n");
        return;
    }

    fwrite(&sade->qtdSecretarios, sizeof(int), 1, pArquivo);

    for(int i=0; i<sade->qtdSecretarios; i++){
        tPessoa *secretario = sade->secretarios[i];
        EscreveBinarioPessoa(pArquivo, secretario);
    }

    fclose(pArquivo);
}

void EscreveBinarioMedicos(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/medicos.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "wb");

    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario secretario\n");
        return;
    }

    fwrite(&sade->qtdMedicos, sizeof(int), 1, pArquivo);

    for(int i=0; i<sade->qtdMedicos; i++){
        tPessoa *medico = sade->medicos[i];
        EscreveBinarioPessoa(pArquivo, medico);
    }

    fclose(pArquivo);
}

void LeBinarioPacientes(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/pacientes.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "rb");

    if (pArquivo == NULL) {
        printf("Erro ao abrir arquivo binario pacientes\n");
        return;
    }
    //printf("camino arquivo pacientes: %s\n", caminhoArquivo);

    fread(&sade->qtdPacientes, sizeof(int), 1, pArquivo);

    sade->pacientes = calloc(sade->qtdPacientes, sizeof(tPessoa*) * sade->qtdPacientes);

    for(int i=0; i<sade->qtdPacientes; i++){
        tPessoa *paciente = CriaPessoa();
        LeBinarioPessoa(pArquivo, paciente);
        sade->pacientes[i] = paciente; 
    }

    //imprime pacientes
    // printf("SADE qtd pacientes: %d\n", sade->qtdPacientes);
    // for(int i=0; i<sade->qtdPacientes; i++){
    //     printf("paciente %d:\n", i);
    //     ImprimePessoa(sade->pacientes[i]);
    // }

    fclose(pArquivo);
}

void LeBinarioSecretarios(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/secretarios.bin", caminhoBancoDados);

    //printf("caminho arquivo secretario: %s\n", caminhoArquivo);
    
    FILE *pArquivo = fopen(caminhoArquivo, "rb");
    
    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario secretario\n");
        return;
    }

    fread(&sade->qtdSecretarios, sizeof(int), 1, pArquivo);

    sade->secretarios = calloc(sade->qtdSecretarios, sizeof(tPessoa*) * sade->qtdSecretarios);
    
    for(int i=0; i<sade->qtdSecretarios; i++){
        tPessoa *secretario = CriaPessoa();
        LeBinarioPessoa(pArquivo, secretario);
        sade->secretarios[i] = secretario;
    }

    //imprime secretarios
    // printf("SADE qtd secretarios: %d\n", sade->qtdSecretarios);
    // for(int i=0; i<sade->qtdSecretarios; i++){
    //     printf("secretario %d:\n", i);
    //     ImprimePessoa(sade->secretarios[i]);
    // }

    fclose(pArquivo);
}

void LeBinarioMedicos(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/medicos.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "rb");

    if (pArquivo == NULL) {
        printf("Erro ao escrever arquivo binario secretario\n");
        return;
    }

    fread(&sade->qtdMedicos, sizeof(int), 1, pArquivo);

    sade->medicos = calloc(sade->qtdMedicos, sizeof(tPessoa*) * sade->qtdMedicos);

    for(int i=0; i<sade->qtdMedicos; i++){
        tPessoa *medico = CriaPessoa();
        LeBinarioPessoa(pArquivo, medico);
        sade->medicos[i] = medico;
    }

    fclose(pArquivo);
}

void LeBinarioLesoes(tSade* sade, char* caminhoBancoDados){
    char caminhoArquivo[TAM_NOME_CAMINHO + 1];
    sprintf(caminhoArquivo, "%s/lesoes.bin", caminhoBancoDados);
    
    FILE *pArquivo = fopen(caminhoArquivo, "rb");

    if (pArquivo == NULL) {
        printf("Erro ao ler arquivo binario lesoes\n");
        return;
    }

    fread(&sade->qtdLesoes, sizeof(int), 1, pArquivo);

    sade->qtdLesoesPacientes = (int *) calloc(sade->qtdPacientes, sizeof(int));

    for(int i=0; i<sade->qtdPacientes; i++){
        fread(&sade->qtdLesoesPacientes[i], sizeof(int), 1, pArquivo);
    }

    sade->lesoes = (tLesao ***) calloc(sade->qtdPacientes, sizeof(tLesao**));

    for(int i=0; i<sade->qtdPacientes; i++){
        sade->lesoes[i] = (tLesao **) calloc(sade->qtdLesoesPacientes[i], sizeof(tLesao*));

        for(int j=0; j<sade->qtdLesoesPacientes[i]; j++){
            tLesao *lesao = AlocaLesao();
            LeBinarioLesao(pArquivo, lesao);
            sade->lesoes[i][j] = lesao;
        }
    }

    //imprime as informaç~eos lidas

    // for(int i=0; i<sade->qtdPacientes; i++){
    //     printf("paciente %d:\n", i);
    //     ImprimeVetorLesoes(sade->lesoes[i], sade->qtdLesoesPacientes[i]);
    // }

    fclose(pArquivo);
}

void CriaLesoesSade(tSade* sade){
    int totalLesoes = 0;
    sade->lesoes = (tLesao ***) calloc(sade->qtdPacientes, sizeof(tLesao**));
    sade->qtdLesoesPacientes = (int *) calloc(sade->qtdPacientes, sizeof(int));

    for(int i=0; i<sade->qtdPacientes; i++){
        int totalLesoesPaciente = 0;
        int qtdLesoesPaciente = 0;

        totalLesoes += RetornaQtdLesoesPaciente(sade->pacientes[i]);
        qtdLesoesPaciente = RetornaQtdLesoesPaciente(sade->pacientes[i]);
        
        sade->qtdLesoesPacientes[i] = qtdLesoesPaciente;	

        if(RetornaLesoesPaciente(sade->pacientes[i]) != NULL){

            tLesao ** lesoesPaciente = RetornaLesoesPaciente(sade->pacientes[i]);
            sade->lesoes[i] = ClonaVetorLesoes(lesoesPaciente, qtdLesoesPaciente);
        }
        else{
            sade->lesoes[i] = NULL;
        }
        
    }

    sade->qtdLesoes = totalLesoes;


}