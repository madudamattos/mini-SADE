#ifndef TPESSOA_H
#define TPESSOA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"

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

NIVELACESSO RetornaNivelAcessoPessoa(tPessoa* p);

char* RetornaNomePessoa(tPessoa*);

char* RetornaDataNascimetoPessoa(tPessoa*);


void SetaPacienteParaDiabetico(tPessoa* p);

void SetaPacienteParaFumante(tPessoa* p);

void SetaPacienteParaAlergico(tPessoa* p);

void SetaPacienteParaHistoricoCancer(tPessoa* p);

void SetaPacienteTipoPele(tPessoa* p, char tipoPele[]);

ATOR RetornaClasseAtor(tPessoa* p);

NIVELACESSO ConverteStringNivelAcesso(const char nivelAcessoStr[]);

void ImprimePessoa(tPessoa* p);

#endif