#ifndef _TSADE_H_
#define _TSADE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"
#include "tFila.h"

typedef struct tSade tSade;

tSade* CriaSADE();

void InicializaSADE(tSade* sade, char *MenuCaminhoBancoDados);

void ExecutaSADE(tSade* sade, char *caminhoBancoDados);

void FinalizaSADE(tSade* sade, char *caminhoBancoDados);

int fileExists(const char * filename);

tFila* RetornaFilaSADE(tSade* sade);

tPessoa* RealizaLogin(tSade* sade);

tPessoa* RetornaUsuarioLogado(tSade* sade);

tPessoa* LocalizaPacienteCPF(tSade* sade, char cpf[]);

tPessoa* LocalizaSecretarioCPF(tSade* sade, char cpf[]);

tPessoa* LocalizaMedicoCPF(tSade* sade, char cpf[]);

void AddSecretarioSADE(tSade* sade);

void AddMedicoSADE(tSade* sade);

void AddPacienteSADE(tSade* sade);

void BuscaPacientes(tSade* sade);

void ExibeRelatorioGeral(tSade* sade);

void ExecutaFilaImpressao(tSade* sade, char *caminhoPastaSaida);

void SetaPrimeiroUsoSade(tSade* sade);

#endif