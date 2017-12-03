/**
 * @file   lista_dupla.c
 * @author Thales Lima Menezes
 * @date   31/10/2017
 * @brief  Contém a implementação de uma
 * lista duplamente encadeada e suas funções auxiliares.
 */
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>



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
	/**
	 * Libera memória previamente alocada para um var_elemento
	 * de acordo com os padrões de aloca_elemento().
	 */

	if(elemento != NULL)
	{
		if(elemento->dados != NULL)
			free(elemento->dados);
		/*Liberamos quaisquer memoria dependente do var_elemento*/
		free(elemento);
		//Liberamos a área de memória em destaque
	}

	return NULL;

}//End free_elemento()


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

	if(codigo == DADO_HEAP)
	{
		//Caso tenhamos recebido um "dado" como parâmetro "info"
		elemento = aloca_elemento();
		//Alocamos o elemento dinamicamente
		elemento->dados = (void*) malloc(size_of_memory);
		//Alocamos uma área de memória para dados de acordo com input
		memcpy(elemento->dados, info, size_of_memory);
		//Fazemos uma cópia da informação recebida
	}
	else if(codigo == VAR_ELEMENTO)
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

	if (finalouinicio == INICIO)
	{
		//Senão somente fazemos o link com a "cabeça" da lista
		elemento->proximo = lista->primeiro;
		lista->primeiro->anterior = elemento;
		lista->primeiro = elemento;
		lista->tamanho++;
	}
	else if(finalouinicio == FINAL)
	{
		//Senão somente fazemos o link com a "cauda" da lista
		lista->ultimo->proximo = elemento;
		elemento->anterior = lista->ultimo;
		lista->ultimo = elemento;
		lista->tamanho++;
	}

	if( !(finalouinicio == INICIO || finalouinicio == FINAL) )
		if(codigo == DADO_HEAP)
			free(elemento);

}//End insere_inicio()


//--------------------------------------------------------------
void*  pop_lista (var_lista* lista, int indice)
{
	/**
	 * Retira um elemento da lista da posição indice.
	 * @param indice Número entre 0 e (var_lista::tamanho -1).
	 */

	if(lista_vazia(lista) || indice < 0)
 		return NULL;

	int posicao = indice+1;

	var_elemento* pop_return;

	if(posicao == 1)
	{
		pop_return = lista->primeiro;
		lista->primeiro = pop_return->proximo;

		if(lista->primeiro == NULL)
			lista->ultimo = lista->primeiro;
		else
			lista->primeiro->anterior = NULL;
	}
	else
	{
		var_elemento* atual = lista->primeiro;
		int iindice;

		for(iindice = 0; iindice < (posicao-2) && atual != NULL; iindice++ )
			atual = atual->proximo;

		if(atual != NULL)
		{
			pop_return = atual->proximo;

			atual->proximo = pop_return->proximo;

			if(pop_return == lista->ultimo)
				lista->ultimo = atual;
			else
				pop_return->proximo->anterior = atual;
		}
	}

	/*Neste momento a lista deve estar completamente
	linkada separada do elemento apontado por pop_return*/

 	lista->tamanho--;

 	void* dados = pop_return->dados;

 	free(pop_return);

 	return dados;

}//End pop_lista()


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
void  apaga_elemento (var_lista* lista, int posicao){
	/**
	 * @autor Fernanda Macedo de Sousa
	 * @brief Apaga um elemento em uma certa posicao da lista
	 */

	if(posicao == 1){
		var_elemento* lixeira     = lista->primeiro;
		lista->primeiro           = lixeira->proximo;
		lista->primeiro->anterior = NULL;
		free(lixeira->dados);
		free(lixeira);
	}else if(posicao > 1){
		var_elemento* atual = lista->primeiro;
		int i;

		for(i = 0; i < (posicao-2) && atual != NULL; i++ )
			atual = atual->proximo;

		if(atual != NULL){
			var_elemento* lixeira = atual->proximo;

			atual->proximo = lixeira->proximo;

			if(lixeira == lista->ultimo){
				lista->ultimo = atual;
				atual->proximo = NULL; // Thales: Redundante mas ok
			}else{
				lixeira->proximo->anterior = atual;
			}

			free(lixeira->dados);
			free(lixeira);

		}//end if

	}//end else

}//end apaga_elemento


//--------------------------------------------------------------
void  esvazia_lista (var_lista* lista, bool devo_liberar_memoria)
{
	/**
	 * @brief Exclui todos os var_elementos de uma var_lista,
	 * ou seja, ao final lista_vazia(var_lista* lista) retorna true.
	 * @param devo_liberar_memoria Booleano que informa se devemos
	 * liberar a memória de elemento::dados.
	 */

	var_elemento* cursor = lista->primeiro;

	while( cursor != NULL )
	{
		lista->primeiro = cursor->proximo;
		/*Desvinculamos o primeiro elemento da lista para evitar
		ponteiros para áreas de memória que não controlamos mais*/
		lista->tamanho--;
		//Decrementamos o tamanho da lista;
		if(devo_liberar_memoria)
			free_elemento(cursor);
		//Caso possamos liberar a memória associada a elemento::dados
		else
			free(cursor);
		//E sempre liberamos a memória do elemento
		cursor = lista->primeiro;
	}

	lista->primeiro = lista->ultimo = NULL;

}//End esvazia_lista()


//--------------------------------------------------------------
void*  busca_lista (var_lista* lista, void* info, int codigo_busca)
{
	if(lista != NULL && info != NULL)
	{
		if( codigo_busca == POSICAO)
		{
			int indice = *(int*)info -1;
			var_elemento* cursor = lista->primeiro;

			while(indice-- > 0 && cursor != NULL)
				cursor = cursor->proximo;

			if(cursor != NULL)
				return cursor->dados;
			else
				return cursor;
		}
		if( codigo_busca == INFORMACAO_MODS)
		{
			Character* dado = info;

			var_elemento* cursor = lista->primeiro;

			Character* informacao = ((Steroids*)cursor->dados)->character;

			while( cursor != NULL )
			{
				if( informacao == dado)
					break;
				else
				{
					cursor = cursor->proximo;
					if(cursor != NULL)
						informacao = ((Steroids*)cursor->dados)->character;
				}
			}

			if(informacao == dado)
				return cursor->dados;
			else
				return NULL;
		}
		if( codigo_busca == INFORMACAO_ROUND)
		{
			Character* dado = info;

			var_elemento* cursor = lista->primeiro;

			Character* informacao = (*(t_node**)cursor->dados)->character;

			while( cursor != NULL )
			{
				if( informacao == dado)
					break;
				else
				{
					cursor = cursor->proximo;
					if(cursor != NULL)
						informacao = (*(t_node**)cursor->dados)->character;
				}
			}

			if(informacao == dado)
				return informacao;
			else
				return NULL;
		}
		if( codigo_busca == SEARCH )
		{
			t_node* dado = (t_node*) info;

			int* indice = (int*) malloc(sizeof(int));

			*indice = 0;

			var_elemento* cursor = lista->primeiro;

			t_node* informacao = *(t_node**)cursor->dados;

			while( cursor != NULL )
			{
				if( informacao == dado)
					break;
				else
				{
					*indice += 1;
					cursor = cursor->proximo;
					if(cursor != NULL)
						informacao = *(t_node**)cursor->dados;
				}
			}

			if(informacao == dado)
				return indice;
			else
				return NULL;
		}
	}
	return NULL;
}//End busca_lista()


//--------------------------------------------------------------
var_lista*  random_roullete(int quantidade, int size_of_memory, var_lista* src_lista)
{
	/**
	 * @brief Seleciona um número X, 1º param, de elementos de uma
	 * lista Y, 2º param, entregando os resultados em uma lista. O
	 * processo de seleção é randômico.
	 * @param quantidade Quantidade de elementos que serão selecionados
	 * @param src_lista  Lista da qual serão retirados os elementos
	 * @return var_lista *resultado
	 */

	if(quantidade >= src_lista->tamanho)
		return NULL;
		//Insira aqui posteriormente opção de avisar quantos elementos faltam
		//Ajudar o usuário
	var_lista* resultado = aloca_lista();

	time_t t;
	srand((unsigned) time(&t));

	while(quantidade-- > 0)
	{
		void* elemento = pop_lista(src_lista, rand() % (src_lista->tamanho - 1));

		insere_lista   (FINAL,
						elemento,
						size_of_memory,
						resultado,
						DADO_HEAP);

		free(elemento);
	}
	// rand() % (src_lista->tamanho - 1)
	// Gera número entre 0 e (var_lista::tamanho -1)
	return resultado;

}//End random_roullete();


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
