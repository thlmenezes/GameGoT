//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   lista_dupla.h
 * @author Thales Lima Menezes
 * @date   31/10/2017
 * @brief  Arquivo que contém a definição de uma
 * lista duplamente encadeada e suas funções auxiliares.
 */

#ifndef __LISTA_DUPLA_H__
#define __LISTA_DUPLA_H__


#include "informacoes_uso_geral.h"


typedef struct elemento{
	void* dados;
	struct elemento* anterior;
    struct elemento* proximo;
} var_elemento;


typedef struct{
	int tamanho;
	var_elemento* primeiro;
	var_elemento* ultimo;
} var_lista;

//Funções de Lista Duplamente Encadeada
var_elemento*  aloca_elemento(void);

var_lista*     aloca_lista   (void);

void           free_lista    (var_lista* lista);

bool           lista_vazia   (var_lista* lista);

void           insere_lista  (int finalouinicio, void* info, int size_of_memory, var_lista* lista, int codigo);

void           deleta_ultimo (var_lista* lista);

void           print_lista   (var_lista* lista, int codigo);

#endif

/*
 * Área para comentário sobre as definições e estruturas do cabeçalho
 */
