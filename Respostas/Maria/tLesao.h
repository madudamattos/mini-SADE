#ifndef TLESAO_H
#define TLESAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tLesao tLesao;

tLesao* AlocaLesao();

tLesao* CriaLesao(int qtdLesoes);

void ImprimeLesao(tLesao* lesao);

void ImprimeLesaoArquivo(FILE* arquivo, tLesao* lesao);

void ImprimeVetorLesoes(tLesao** lesoes, int qntdLesoes);

int RetornaCirurgia(tLesao* lesao);

int RetornaCrioterapia(tLesao* lesao);

int RetornaTamanhoLesao(tLesao* lesao);

tLesao** ClonaVetorLesoes(tLesao** lesoes, int qntdLesoes);

tLesao* ClonaLesao(tLesao* lesao);

void DesalocaLesao(tLesao *lesao);

void DesalocaLesoes(tLesao** lesoes, int qntdLesoes);

void EscreveBinarioLesao(FILE* arquivo, tLesao* lesao);

void LeBinarioLesao(FILE* arquivo, tLesao* lesao);

void SetaConsultaLesao(tLesao* lesao);

void ResetaConsultaLesao(tLesao* lesao);

int RetornaConsultaLesao(tLesao* lesao);

#endif