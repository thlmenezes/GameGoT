/**
 * @file   fila.c
 * @author Thales Lima Menezes
 * @date   16/11/2017
 * @brief  Contém a implementação de uma
 * fila baseada em uma lista duplamente encadeada
 * e suas funções auxiliares.
 */

#include "../headers/lista_dupla.h"
#include "../headers/fila.h"
#include <stdlib.h>



//TOD
//--------------------------------------------------------------
var_fila*  aloca_fila (void)
{

	/**
	 * Aloca, dinamicamente, uma fila, que será
	 * representada como uma lista duplamente encadeda de
	 * var_elemento, que será alocada usando aloca_lista().
	 * @return Endereço da fila alocada.
	 */

	return aloca_lista();

}//End aloca_fila()


//--------------------------------------------------------------
void  free_fila (var_fila* fila)
{

	/**
	 * Libera a memória que outrora fora alocada dinamicamente
	 * para uma fila seguindo os parâmetros de aloca_fila()
	 */

	free_lista(fila);

}//End free_fila()


//--------------------------------------------------------------
bool  fila_vazia (var_fila* fila)
{

	/**
	 * @brief Retorna booleano com a resposta à pergunta:
	 * A fila está vazia?
	 * @return Retorna 'true', ou seja, não zero,
	 * caso a fila esteja vazia. Também poderia ter
	 * sido usada a variável 'fila->tamanho'.
	 */

	return lista_vazia(fila);

}//End fila_vazia()


//--------------------------------------------------------------
void  entrar_fila (void* info, int size_of_memory, var_fila* fila)
{

	/**
	 * @brief Insere no final da fila uma informação, podendo ser
	 * um elemento::dados ou var_elemento.
	 * @param size_of_memory Tamanho em bytes da área de memória
	 * apontada pelo ponteiro genérico "info".
	 */

	insere_lista (INSERE_FINAL, info, size_of_memory, fila, INSERE_DADO_HEAP);

}//End entrar_fila()


//--------------------------------------------------------------
void*  sair_fila (var_fila* fila)
{

	/**
	 * Retira do início da fila um elemento::dados.
	 */

	if(fila_vazia(fila))
		return NULL;

	var_elemento* elemento = fila->primeiro;

	fila->primeiro = elemento->proximo;

	if(fila->primeiro == NULL)
		fila->ultimo = fila->primeiro;
	else
		fila->primeiro->anterior = NULL;

	fila->tamanho--;

	void* dados = elemento->dados;

	free(elemento);

	return dados;

}//End sair_fila()


//--------------------------------------------------------------
void  print_fila (var_fila* fila, int codigo)
{

	/**
	 * @brief Imprime a fila armazenada segundo aloca_fila().
	 * @param codigo Diz como deverão ser interpretados cada elemento da fila para impressão.
	 */

	print_lista(fila, codigo);

}//End entrar_fila()
