#ifndef _TBUSCA_H_
#define _TBUSCA_H_

#include "tPessoa.h"

#define NOME_ARQUIVO_BUSCA "lista_busca.txt"

typedef struct tBusca tBusca;

tBusca *criaListaBusca(tPessoa** pessoasEncontradas, int qtdPessoasEncontradas);

void desalocaBusca(void *dado);

void imprimeNaTelaListaBusca(void *dado);

void imprimeEmArquivoListaBusca(void *dado, char *path);

#endif