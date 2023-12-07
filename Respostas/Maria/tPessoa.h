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

void CadastraSecretario(char* caminhoConfig);

void CadastraMedico(char* caminhoConfig);

void CadastraPaciente(char* caminhoConfig);

void DesalocaPessoa(tPessoa*);

char RetornaCPFPaciente(tPessoa*);

char RetornaCRMMedico(tPessoa*);

char RetornaNivelAcesso(tPessoa*);

char RetornaNomePaciente(tPessoa*);

char RetornaDataNascimentoPaciente(tPessoa*);

