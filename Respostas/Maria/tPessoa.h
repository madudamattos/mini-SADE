#ifndef TPESSOA_H
#define TPESSOA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tLesao.h"

typedef enum{
    PACIENTE,
    MEDICO,
    SECRETARIO
}ATOR;

typedef enum{
    NADA = 0,
    MED = 1,
    USER = 2,
    ADMIN = 3
}NIVELACESSO;

typedef struct tPessoa tPessoa;

typedef struct tPaciente tPaciente;

tPessoa* CriaPessoa();

tPessoa* CadastraPessoa();

tPessoa* CadastraSecretario();

tPessoa* CadastraMedico();

tPessoa* CadastraPaciente();

tPessoa* ClonaPessoa(tPessoa*p);

void DesalocaPessoa(tPessoa*);

void DesalocaPaciente(tPaciente*);

char* RetornaCPFPessoa(tPessoa*);

char* RetornaCRMMedico(tPessoa*);

char* RetornaLoginPessoa(tPessoa* p);

char* RetornaSenhaPessoa(tPessoa* p);

NIVELACESSO RetornaNivelAcessoPessoa(tPessoa* p);

char* RetornaNomePessoa(tPessoa*);

char* RetornaDataNascimetoPessoa(tPessoa*);

int RetornaQtdLesoesPaciente(tPessoa* p);

tLesao** RetornaLesoesPaciente(tPessoa* p);

int RetornaIdadePessoa(tPessoa* p);

void SetaPacienteParaDiabetico(tPessoa* p);

void SetaPacienteParaFumante(tPessoa* p);

void SetaPacienteParaAlergico(tPessoa* p);

void SetaPacienteParaHistoricoCancer(tPessoa* p);

void SetaPacienteTipoPele(tPessoa* p, char tipoPele[]);

void AumentaQtdLesoesPaciente(tPessoa* p);

ATOR RetornaClasseAtor(tPessoa* p);

NIVELACESSO ConverteStringNivelAcesso(const char nivelAcessoStr[]);

void ImprimePessoa(tPessoa* p);

int RetornaSomaTamanhoLesoesPessoa(tPessoa* p);

int RetornaQtdLesoesParaCirurgia(tPessoa* p);

int RetornaQtdLesoesParaCrioterapia(tPessoa* p);

char* RetornaGeneroPessoa(tPessoa* p);

void AdicionaLesao(tLesao* lesao, tPessoa* p);

void SetaPacienteParaAtendido(tPessoa* p);

int RetornaAtendidoPaciente(tPessoa* p);

#endif