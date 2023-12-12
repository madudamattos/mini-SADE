#ifndef TRELATORIO_H
#define TRELATORIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tSade.h"

#define NOME_ARQUIVO_RELATORIO "relatorio_geral.txt"

typedef struct tRelatorio tRelatorio;

tRelatorio *CriaRelatorio(int totalPacientes, int mediaIdade, int totalFeminino, int totalMasculino, int totalOutros, int mediaTamLesoes, int totalLesoes, int totalCirurgias, int totalCrioterapias);

void DesalocaRelatorio(void *dado);

void ImprimeNaTelaRelatorio(void *dado);

void ImprimeEmArquivoRelatorio(void *dado, char *path);

#endif