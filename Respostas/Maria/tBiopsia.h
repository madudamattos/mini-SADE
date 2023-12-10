#ifndef _TBIOPSIA_H_
#define _TBIOPSIA_H_

#define MAX_TAM_NOME_LESAO 50
#define NOME_ARQUIVO_BIOPSIA "biopsia.txt"

typedef struct tBiopsia tBiopsia;
typedef struct tLesao tLesao;


/**
 * Função que recebe todas as informações pertinentes a uma Biopsia e retorna
 * um ponteiro com a Biopsia criada.
 *
 */
tBiopsia *criaBiopsia(char *nomePaciente, char *CPF,
                      tLesao** lesoes, int qntdLesoes,
                      char *nomeMedico, char *CRM, char *dataStr);

/**
 * Função que recebe o ponteiro genérico (que deve conter uma Biopsia) e o desaloca da memória.
 * Essa função primeiro verifica se o ponteiro é NULL antes de desalocar.
 */
void desalocaBiopsia(void *dado);

/**
 * Função que recebe um ponteiro genérico (que deve conter uma Biopsia) e imprime os dados na tela
 * de acordo com o especificado na descrição do trabalho.
 */
void imprimeNaTelaBiopsia(void *dado);

void DesalocaLesoes(tLesao** lesoes, int qntdLesoes);
/**
 * Função que recebe um ponteiro genérico (que deve conter uma Biopsia) e imprime os dados no arquivo
 * específico de acordo com a descrição do trabalho.
 * Essa função também recebe o path da pasta onde o arquivo deve ser criado ou editado.
 * Ex: /home/usuario/Documentos
 * O nome do arquivo e a maneira de escrita é definido dentro da função
 */
void imprimeEmArquivoBiopsia(void *dado, char *path);

#endif