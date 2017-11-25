/**
 * @file   lista_dupla.c
 * @author Thales Lima Menezes
 * @date   31/10/2017
 * @brief  Contém a implementação de uma
 * lista duplamente encadeada e suas funções auxiliares.
 */

#include "../headers/lista_dupla.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



//TOD:
//--------------------------------------------------------------
var_elemento*  aloca_elemento (void)
{

	/**
	 * @brief Aloca, dinamicamente, um var_elemento
	 * seguindo alguns padrões: ponteiros são iniciados
	 * com valor NULL.
	 * @return Endereço do elemento alocado.
	 */

	var_elemento* elemento = (var_elemento*) malloc(sizeof(var_elemento));

	elemento->dados     = NULL;// }
	elemento->anterior  = NULL;// } Padrões de inicialização de um elemento*/
	elemento->proximo   = NULL;// }

	return elemento;

}//End aloca_elemento()


//--------------------------------------------------------------
var_lista*  aloca_lista (void)
{

	/**
	 * Aloca, dinamicamente, uma lista duplamente
	 * encadeda de var_elemento, que por sua vez também
	 * serão alocados dinamicamente, seguindo alguns padrões:
	 * var_lista::primeiro e var_lista::ultimo são
	 * inicializados com o valor NULL.
	 * @return Endereço da lista alocada.
	 */

	var_lista* lista = (var_lista*) malloc(sizeof(var_lista));

	lista->primeiro  = NULL;// }
	lista->ultimo    = NULL;// } Indicações que a lista está vazia
	lista->tamanho   = 0;	// }

	return lista;

}//End aloca_lista()

//--------------------------------------------------------------
void*  free_elemento (var_elemento* elemento)
{
	if(elemento != NULL)
	{
		if(elemento->dados != NULL)
			free(elemento->dados);
		/*Liberamos quaisquer memoria dependente do var_elemento*/
		free(elemento);
		//Liberamos a área de memória em destaque
	}

	return NULL;

}//end free_elemento()


//--------------------------------------------------------------
void*  free_lista (var_lista* lista)
{

	/**
	 * Libera a memória que outrora fora alocada dinamicamente
	 * para uma lista encadeada seguindo os parâmetros de
	 * aloca_lista() e aloca_elemento()
	 */

	var_elemento* cursor = lista->primeiro;

	while(cursor != NULL)
	{
		lista->primeiro = cursor->proximo;
		/*Desvinculamos o primeiro elemento da lista para evitar
		ponteiros para áreas de memória que não controlamos mais*/
		cursor = free_elemento(cursor);
		//Liberamos o elemento
		cursor = lista->primeiro;
		//Atualizamos o cursor para a próxima vítima
	}//end while(cursor != NULL)

	free(lista);
	//Após liberarmos todos os compenentes liberamos a "var_lista"
	return NULL;

}//End free_lista()


//--------------------------------------------------------------
bool  lista_vazia (var_lista* lista)
{

	/**
	 * @brief Retorna booleano com a resposta à pergunta:
	 * A lista está vazia?
	 * @return Retorna 'true', ou seja, não zero,
	 * caso a lista esteja vazia. Também poderia ter
	 * sido usada a variável 'lista->tamanho'.
	 */

	return (lista->primeiro == NULL && lista->ultimo == NULL);

}//End lista_vazia()


//--------------------------------------------------------------
void  insere_lista (int finalouinicio, void* info, int size_of_memory, var_lista* lista, int codigo)
{

	/**
	 * @brief Insere um dado em uma lista duplamente encadeada
	 * previamente alocada dinamicamente. Recomendado observar
	 * a composição de um var_elemento.
	 * @param finalouinicio Define se o elemento/dado será inserido ao final ou
	 * ao início da lista.
	 * @param info Ponteiro genérico para um elemento::dados ou
	 * var_elemento previamente montado.
	 * @param size_of_memory Tamanho da informação, em bytes, a ser inserida na
	 * lista.
	 * @param lista Ponteiro para uma var_lista na qual será inserida a informa
	 * ção.
	 * @param codigo Informa se o ponteiro genérico aponta para uma informação
	 * do tipo elemento::dados ou se é um var_elemento previamente
	 * montado.
	 */

	var_elemento* elemento;

	if(codigo == INSERE_DADO_HEAP)
	{
		//Caso tenhamos recebido um "dado" como parâmetro "info"
		elemento = aloca_elemento();
		//Alocamos o elemento dinamicamente
		elemento->dados = (void*) malloc(size_of_memory);
		//Alocamos uma área de memória para dados de acordo com input
		memcpy(elemento->dados, info, size_of_memory);
		//Fazemos uma cópia da informação recebida
	}
	else if(codigo == INSERE_VAR_ELEMENTO)
	{
		//Caso tenhamos recebido um 'var_elemento' pronto
		elemento  = (void*) malloc(size_of_memory);
		//Alocamos uma área de memória para dados de acordo com input
		memcpy(elemento, info, size_of_memory);
		//Passamos o endereço do 'var_elemento' recebido
	}

	if(lista_vazia(lista))
	{
		//Caso a lista estivesse vazia anteriormente
		lista->primeiro = lista->ultimo = elemento;
		//Ambos ponteiros informarão o mesmo endereço
		lista->tamanho++;
		return;
	}

	if (finalouinicio == INSERE_INICIO)
	{
		//Senão somente fazemos o link com a "cabeça" da lista
		elemento->proximo = lista->primeiro;
		lista->primeiro->anterior = elemento;
		lista->primeiro = elemento;
		lista->tamanho++;
	}
	else if(finalouinicio == INSERE_FINAL)
	{
		//Senão somente fazemos o link com a "cauda" da lista
		lista->ultimo->proximo = elemento;
		elemento->anterior = lista->ultimo;
		lista->ultimo = elemento;
		lista->tamanho++;
	}

	if( !(finalouinicio == INSERE_INICIO || finalouinicio == INSERE_FINAL) )
		if(codigo == INSERE_DADO_HEAP)
			free(elemento);

}//End insere_inicio()


//--------------------------------------------------------------
void  deleta_ultimo (var_lista* lista)
{

	/**
	 * Apaga o último var_elemento de uma lista; e
	 * caso a lista esteja vazia não faz nada.
	 */

	if(lista_vazia(lista))	//Caso tenha 0 elementos
		return;

	if(lista->primeiro == lista->ultimo) //Caso tenha 1 elemento
	{
		if(lista->ultimo->dados != NULL)
			free(lista->ultimo->dados);
		free(lista->ultimo);
		lista->primeiro = lista->ultimo = NULL;
	}
	else //Caso tenha 2 ou mais elementos
	{
		var_elemento* cursor = lista->primeiro;
		while(cursor->proximo != lista->ultimo)
				cursor = cursor->proximo;

		cursor->proximo = NULL;

		if(lista->ultimo->dados != NULL)
			free(lista->ultimo->dados);
		free(lista->ultimo);

		lista->ultimo = cursor;
 	}

	lista->tamanho--;

}//End erase_ultimo()


//--------------------------------------------------------------
void  print_lista (var_lista* lista, int codigo)
{

	/**
	 * @brief Imprime a lista armazenada segundo aloca_lista().
	 * @param codigo Diz como deverão ser interpretados cada elemento::dados da lista para impressão.
	 */

	if(lista_vazia(lista))
		printf("Vazia\n");
	else
	{
		var_elemento* cursor = lista->primeiro;
		int indice = 0;
		while(cursor != NULL)
		{

			switch(codigo)
			{
				case INT:
					printf("%d. %d\n", ++indice, *(int*)cursor->dados);
					break;
				case CHAR:
					printf("%d. %c\n", ++indice, *(char*)cursor->dados);
					break;
				case FLOAT:
					printf("%d. %f\n", ++indice, *(float*)cursor->dados);
					break;
				default:
					break;
			}//end switch(codigo)

			cursor = cursor->proximo;

		}//end while(cursor != NULL)

	}//end else

}//End imprime_lista()
