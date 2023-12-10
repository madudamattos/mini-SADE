#ifndef _TSADE_H_
#define _TSADE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tPessoa.h"

typedef struct tSade tSade;

tSade* CriaSADE();

void InicializaSADE(tSade* sade, char *MenuCaminhoBancoDados);

void ExecutaSADE(tSade* sade, char *caminhoBancoDados);

void FinalizaSADE(tSade* sade, char *caminhoBancoDados);

int RealizaLogin(char *caminhoBancaDados);

void AddSecretarioSADE(tSade* sade);

void AddMedicoSADE(tSade* sade);

void AddPacienteSADE(tSade* sade);

void BuscaPacientes(tSade* sade);

void ImprimeEmArquivoBusca(tPessoa** pacientesEncontrados, int qtdPacientesEncontrados, char*path);

void ImprimeNaTelaBusca(tPessoa **pacientesEncontrados, int qtdPacientesEncontrados);

#endif