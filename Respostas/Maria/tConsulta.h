#ifndef TCONSULTA_H
#define TCONSULTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tMenu.h"
#include "tFila.h"
#include "tSade.h"
#include "tReceita.h"

void RealizaConsulta();

tPessoa* LocalizaPaciente(tSade* sade, char cpf[]);

void GeraReceita(tPaciente* paciente, tSade* sade);

#endif