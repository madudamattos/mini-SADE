#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tBiopsia.h"

typedef struct tPessoa tPessoa;

typedef struct tPaciente tPaciente;

tPessoa* CriaPessoa();

void CadastraSecretario(char* caminhoConfig);

void CadastraMedico(char* caminhoConfig);

void CadastraPaciente(char* caminhoConfig);

char RetornaCPFPaciente(tPessoa*);

char RetornaCRMMedico(tPessoa*);

char RetornaNivelAcesso(tPessoa*);

char RetornaNomePaciente(tPessoa*);

char RetornaDataNascimentoPaciente(tPessoa*);