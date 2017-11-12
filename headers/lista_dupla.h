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


typedef enum { false,	true } bool;


typedef struct elemento{
	void* dados;
	struct elemento* anterior;
    struct elemento* proximo;
} var_elemento;


typedef struct{
	int tamanho;
	var_elemento* primeiro;
	var_elemento* ultimo;
} var_lista, var_fila;


enum lista_defines
{INSERE_DADO_HEAP,
 INSERE_VAR_ELEMENTO,
 INSERE_INICIO,
 INSERE_FINAL,
 INT, CHAR, FLOAT };

//Funções de Lista Duplamente Encadeada
var_elemento*  aloca_elemento(void);

var_lista*     aloca_lista   (void);

void           free_lista    (var_lista* lista);

bool           lista_vazia   (var_lista* lista);

void           insere        (int finalouinicio, void* info, var_lista* lista, int codigo);

void           deleta_ultimo (var_lista* lista);

void           print_lista   (var_lista* lista, int codigo);

/*
//Funções de Fila
var_fila*   aloca_fila  (void);

void        free_fila   (var_fila* fila);

bool        fila_vazia  (var_fila* fila);

void        entrar_fila (void* info, var_fila* fila);

void*       sair_fila   (var_fila* fila);
//FUNÇÕES DE USO PRIVADO PARA Fila
*/

#endif

/*
 * Área para cometário sobre as definições e estruturas do cabeçalho
 */
