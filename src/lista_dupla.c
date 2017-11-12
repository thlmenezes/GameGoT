#include "../headers/lista_dupla.h"
#include <stdlib.h>
#include <stdio.h>



//TODO:Verificar insere()
//--------------------------------------------------------------
var_elemento*  aloca_elemento (void)
{

	/**
	 * @brief Função que aloca, dinamicamente, um 'var_elemento'
	 * seguindo alguns padrões: ponteiros são iniciados
	 * com valor NULL.
	 * @return Endereço do elemento alocado
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
	 * Função que aloca, dinamicamente, uma lista duplamente
	 * encadeda de 'var_elemento's, que por sua vez também
	 * serão alocados dinamicamente, seguindo alguns padrões:
	 * "primeiro" e "ultimo" são inicializados com o valor
	 * NULL.
	 * @return Endereço da lista alocada
	 */

	var_lista* lista = (var_lista*) malloc(sizeof(var_lista));

	lista->primeiro  = NULL;// }
	lista->ultimo    = NULL;// } Indicações que a lista está vazia
	lista->tamanho   = 0;	// }

	return lista;

}//End aloca_lista()


//--------------------------------------------------------------
void  free_lista (var_lista* lista)
{

	/**
	 * Libera a memória que outrora fora alocada dinamicamente
	 * para uma lista encadeada seguindo os parametros de
	 * aloca_lista() e aloca_elemento()
	 */

	var_elemento* cursor = lista->primeiro;

	while(cursor != NULL)
	{
		lista->primeiro = cursor->proximo;
		/*Desvinculamos o primeiro elemento da lista para evitar
		ponteiros para áreas de memória que não controlamos mais*/
		free(cursor->dados);
		/*Liberamos quaisquer memoria dependente do var_elemento*/
		free(cursor);
		//Liberamos a área de memória em destaque
		cursor = lista->primeiro;
		//Atualizamos o cursor para a próxima vítima
	}//end while(cursor != NULL)

	free(lista);
	//Após liberarmos todos os compenentes liberamos a "var_lista"

}//End free_lista()


//--------------------------------------------------------------
bool  lista_vazia (var_lista* lista)
{

	/**
	 * Função que retorna 'true', ou seja, não zero,
	 * caso a lista esteja vazia. Também poderia ter
	 * sido usada a variável 'lista->tamanho'.
	 * @return Booleano com a resposta da pergunta
	 * "a lista está vazia ?"
	 */

	return (lista->primeiro == NULL && lista->ultimo == NULL);

}//End lista_vazia()


//--------------------------------------------------------------
void  insere (int finalouinicio, void* info, var_lista* lista, int codigo)
{
	//NOTE: Essa função toma para si a área de memória recebida pelo parâmetro info
	/*TODO: usar função (memcpy - copy memory area) para generalizar uso de insere
	SYNOPSIS
	       #include <string.h>

	       void *memcpy(void *dest, const void *src, size_t n);

	DESCRIPTION
	       The  memcpy()  function  copies  n bytes from memory area src to memory
	       area dest.
	*/
	/**    Função PRIVADA, para uso interno da função 'push'
	 * @param info é IMPORTANTE que info tenha sido alocado dinamicamente previamente.
	 * @brief Função que insere um dado ao final de uma lista encadeada
	 * previamente alocada dinamicamente.
	 */

	var_elemento* elemento;

	if(codigo == INSERE_DADO_HEAP)
	{
		//Caso tenhamos recebido um "dado" como parâmetro "info"
		elemento = aloca_elemento();
		//Alocamos o elemento dinamicamente
		elemento->dados = info;
		//Fazemos o link da informação recebida
	}
	else if(codigo == INSERE_VAR_ELEMENTO)
		//Caso tenhamos recebido um 'var_elemento' pronto
		elemento = info;
		//Passamos o endereço do 'var_elemento' recebido

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
	 * Função que apaga o ultimo elemento de uma lista; e
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
	 * @brief Função que imprime a lista armazenada.
	 * @param codigo Diz como deverá ser tratada a lista para impressão.
	 */

	if(lista_vazia(lista))
		printf("Lista Vazia\n");
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
