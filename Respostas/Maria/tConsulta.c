#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tConsulta.h"
#include "tPessoa.h"
#include "tMenu.h"
#include "tFila.h"
#include "tSade.h"
#include "tReceita.h"
#include "tLesao.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

void RealizaConsulta(tSade* sade){
    char dataConsulta[20], cpf[20], tipoPele[10];
    int diabetes, fumante, alergia, histCancer;

    tPessoa* medico = RetornaUsuarioLogado(sade);

    printf("#################### CONSULTA MEDICA #######################\nCPF DO PACIENTE:");

    //limpa o buffer do teclado
    int c;
    while(c = getchar() != '\n' && c != EOF);
    
    scanf("%[^\n]%*c", cpf);
    
    tPessoa * paciente = LocalizaPacienteCPF(sade, cpf);

    if(paciente == NULL){
        printf("PACIENTE SEM CADASTRO\n\nPRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n############################################################\n");
        scanf("%*c");
        return;
    }

    //printf("CPF DO PACIENTE: %s\n", RetornaCPFPessoa(paciente));
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

    SetaPacienteParaAtendido(paciente);

    printf("############################################################\n");
    
    //continua a consulta
    int opcao = 0; 

    while(opcao != 5){
        MenuConsultaMedica();

        scanf("%d", &opcao);

        switch (opcao){
        case 1:
            CadastraLesao(paciente);
            break;
        case 2:
            GeraReceita(sade, paciente, medico, dataConsulta);
            break;
        case 3:
            SolicitaBiopsia(sade, paciente, medico, dataConsulta);
            break;
        case 4:
            GeraEncaminhamento(sade, paciente, medico, dataConsulta);
        case 5:
            //retorna ao menu principal
            break;
        default:
            break;
        }
    }
}

void CadastraLesao(tPessoa* paciente){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    AumentaQtdLesoesPaciente(paciente);
    tLesao* lesao = CriaLesao(RetornaQtdLesoesPaciente(paciente));
    AdicionaLesao(lesao, paciente);
    while ((c = getchar()) != '\n' && c != EOF);    
    scanf("%*c");
}

void GeraReceita(tSade* sade, tPessoa* paciente, tPessoa* medico, char* dataStr){
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO], tipoMedicamento[MAX_TAM_NOME_MEDICAMENTO], instrucoes[MAX_TAM_INSTRUCOES], nomeMedico[100], CRM[20], Uso[20], nomePaciente[100];
    eTipoUso tipoUso;
    int qtd;

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("#################### CONSULTA MEDICA #######################\nRECEITA MEDICA:\nTIPO DE USO: ");
    scanf("%[^\n]%*c", Uso);
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nomeMedicamento);
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]%*c", tipoMedicamento);
    printf("QUANTIDADE: ");
    scanf("%d%*c", &qtd);
    printf("INSTRUÇÕES DE USO: ");
    scanf("%[^\n]%*c", instrucoes);

    if (strcmp(Uso, "ORAL") == 0) tipoUso = ORAL;
    else if (strcmp(Uso, "TOPICO") == 0) tipoUso = TOPICO;
    
    tReceita* receita = NULL;

    if(RetornaNivelAcessoPessoa(medico) == ADMIN){
        receita = criaReceita(RetornaNomePessoa(paciente), tipoUso, nomeMedicamento, tipoMedicamento, instrucoes, qtd, "\0", "\0", dataStr);
    }
    else{
        receita = criaReceita(RetornaNomePessoa(paciente), tipoUso, nomeMedicamento, tipoMedicamento, instrucoes, qtd, RetornaNomePessoa(medico), RetornaCRMMedico(medico), dataStr);
    }

    insereDocumentoFila(RetornaFilaSADE(sade), receita, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    
    printf("\nRECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
    
    scanf("%*c");
    
    return;
}

void SolicitaBiopsia(tSade* sade, tPessoa* pessoa, tPessoa* medico, char* dataStr){
    int qtdLesoes = RetornaQtdLesoesPaciente(pessoa);
    tLesao** lesoes = RetornaLesoesPaciente(pessoa);
    
    tBiopsia* biopsia = NULL;

    if(RetornaNivelAcessoPessoa(medico) == ADMIN){
        biopsia = CriaBiopsia(RetornaNomePessoa(pessoa), RetornaCPFPessoa(pessoa), lesoes, qtdLesoes, "\0", "\0", dataStr);
    }
    else{
        biopsia = CriaBiopsia(RetornaNomePessoa(pessoa), RetornaCPFPessoa(pessoa), lesoes, qtdLesoes, RetornaNomePessoa(medico), RetornaCRMMedico(medico), dataStr);
    }

    if(biopsia == NULL){
        printf("#################### CONSULTA MEDICA #######################\nNAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
        return;
    }

    insereDocumentoFila(RetornaFilaSADE(sade), biopsia, ImprimeNaTelaBiopsia, ImprimeEmArquivoBiopsia, DesalocaBiopsia);
    
    printf("#################### CONSULTA MEDICA #######################\nSOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    scanf("%*c");
}

void GeraEncaminhamento(tSade* sade, tPessoa* paciente, tPessoa* medico, char* dataStr){
    char especialidade[50], motivo[300];

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("#################### CONSULTA MEDICA #######################\nENCAMINHAMENTO: \nESPECIALIDADE ENCAMINHADA: ");
    scanf("%[^\n]%*c", especialidade);
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", motivo);

    tEncaminhamento* encaminhamento = NULL;

    if(RetornaNivelAcessoPessoa(medico) == ADMIN){
        encaminhamento = criaEncaminhamento(RetornaNomePessoa(paciente), RetornaCPFPessoa(paciente), especialidade, motivo, "\0", "\0", dataStr);
    }
    else{
        encaminhamento = criaEncaminhamento(RetornaNomePessoa(paciente), RetornaCPFPessoa(paciente), especialidade, motivo, RetornaNomePessoa(medico), RetornaCRMMedico(medico), dataStr);
    }
   
    insereDocumentoFila(RetornaFilaSADE(sade), encaminhamento, imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);

    printf("\nENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n############################################################\n");
    scanf("%*c");   

}