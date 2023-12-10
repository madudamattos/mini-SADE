#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tConsulta.h"
#include "tPessoa.h"
#include "tMenu.h"
#include "tFila.h"
#include "tSade.h"
#include "tReceita.h"

typedef struct tPessoa tPessoa;

void RealizaConsulta(tSade* sade){
    char dataConsulta[11], cpf[12], tipoPele[3];
    int diabetes, fumante, alergia, histCancer;

    printf("#################### CONSULTA MEDICA #######################\nCPF DO PACIENTE:");
    
    scanf("%[^\n]%*c", cpf);
    
    tPessoa * paciente = LocalizaPaciente(sade, cpf);

    if(paciente == NULL){
        printf("PACIENTE SEM CADASTRO\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n############################################################\n");
        return;
    }

    printf("CPF DO PACIENTE: %s\n", RetornaCPFPessoa(paciente));
    printf("---\n");
    printf("-NOME: %s\n", RetornaNomePessoa(paciente));
    printf("-DATA DE NASCIMENTO: %s\n", RetornaDataNascimetoPessoa(paciente));
    printf("DATA DA CONSULTA: ");
    scanf("%[^\n]%*c", dataConsulta);
    printf("POSSUI DIABETES: ");
    scanf("%d%*c", &diabetes);
    printf("FUMANTE: ");
    scanf("%d%*c", &fumante);
    printf("ALERGIA A MEDICAMENTO: ");
    scanf("%d%*c", &alergia);
    printf("HISTORICO DE CANCER: ");
    scanf("%d%*c", &histCancer);
    printf("TIPO DE PELE: ");
    scanf("%[^\n]%*c", tipoPele);

    if(alergia == 1) SetaPacienteParaAlergico(paciente);
    if(fumante == 1) SetaPacienteParaFumante(paciente);
    if(diabetes == 1) SetaPacienteParaDiabetico(paciente);
    if(histCancer == 1) SetaPacienteParaHistoricoCancer(paciente);
    SetaPacienteTipoPele(paciente, tipoPele);

    printf("############################################################\n");

    //continua a consulta
    int opcao = 0; 

    while(opcao != 5){
        MenuConsultaMedica();
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            //CadastraLesao(paciente);
            break;
        case 2:
            //gera receita
            break;
        case 3:
            //solicitação de biopsia
            break;
        case 4:
            //encaminhamento;
        case 5:
            //retorna ao menu principal
            break;
        default:
            break;
        }
    }
}

tPessoa* LocalizaPaciente(tSade* sade, char cpf[]){
   
    // for(int i=0; i<sade->qtdPacientes; i++){
    //     if(strcmp(sade->pacientes[i]->cpf, cpf) == 0){
    //         return sade->pacientes[i];
    //     }
    // }

    return NULL;
}

void GeraReceita(tPaciente* paciente, tSade* sade){
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO], tipoMedicamento[MAX_TAM_NOME_MEDICAMENTO], instrucoes[MAX_TAM_INSTRUCOES], nomeMedico[100], CRM[11], dataStr[13], Uso[10], nomePaciente[100];
    eTipoUso tipoUso;
    int qtd;

    printf("#################### CONSULTA MEDICA #######################\nRECEITA MEDICA:\nTIPO DE USO: ");
    scanf("%[^\n]%*c", Uso);
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nomeMedicamento);
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%d%*c", &qtd);
    printf("INSTRUÇÕES DE USO: ");
    scanf("%[^\n]%*c", instrucoes);


    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");

    if (strcmp(Uso, "ORAL") == 0) tipoUso = ORAL;
    else if (strcmp(Uso, "TOPICO") == 0) tipoUso = TOPICO;

    //tReceita *receita = criaReceita()
    return;
}