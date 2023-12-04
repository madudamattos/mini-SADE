#ifndef _TENCAMINHAMENTO_H_
#define _TENCAMINHAMENTO_H_

#define MAX_TAM_NOME_ESPECIALIDADE 50
#define MAX_TAM_MOTIVO 300
#define NOME_ARQUIVO_ENCAMINHAMENTO "encaminhamento.txt"

typedef struct tEncaminhamento tEncaminhamento;

/**
 * Função que recebe todas as informações pertinentes a um encaminhamento e retorna
 * um ponteiro com o encaminhamento criado.
 *
 */
tEncaminhamento *criaEncaminhamento(char *nomePaciente, char* CPF, 
                                    char *nomeEspecialidade, char *motivo, char *nomeMedico, char *CRM, char *dataStr);

/**
 * Função que recebe o ponteiro genérico (que deve conter um encaminhamento) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaEncaminhamento(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter um encaminhamento) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaEncaminhamento(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter um encaminhamento) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoEncaminhamento(void *dado, char *path);

#endif