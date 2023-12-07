#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"

typedef enum{
    PACIENTE = 0,
    MEDICO = 1,
    SECRETARIO = 2
}ATOR;

typedef struct tPessoa tPessoa;

typedef struct tPaciente tPaciente;

tPessoa* CriaPessoa();

tPessoa* CadastraPessoa();

void CadastraSecretario();

void CadastraMedico();

void CadastraPaciente();

void DesalocaPessoa(tPessoa*);

char* RetornaCPFPaciente(tPessoa*);

char* RetornaCRMMedico(tPessoa*);

char* RetornaNivelAcesso(tPessoa*);

char* RetornaNomePaciente(tPessoa*);

char* RetornaDataNascimentoPaciente(tPessoa*);

ATOR RetornaClasseAtor(tPessoa* p);