#ifndef TCONSULTA_H
#define TCONSULTA_H

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

void RealizaConsulta(tSade* sade);

tPessoa* LocalizaPaciente(tSade* sade, char cpf[]);

void CadastraLesao(tPessoa* paciente);

void GeraReceita(tSade* sade, tPessoa* paciente, tPessoa* medico, char* dataStr);

void SolicitaBiopsia(tSade* sade, tPessoa* pessoa, tPessoa* medico, char* dataStr);

void GeraEncaminhamento(tSade* sade, tPessoa* paciente, tPessoa* medico, char* dataStr);

#endif