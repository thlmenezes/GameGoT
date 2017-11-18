//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   fila.h
 * @author Thales Lima Menezes
 * @date   16/11/2017
 * @brief  Contém a definição de uma
 * fila baseada em uma lista duplamente encadeada
 * e suas funções auxiliares.
 */

#ifndef __FILA_H__
#define __FILA_H__


#include "informacoes_uso_geral.h"
#include "lista_dupla.h"


typedef var_lista var_fila;


//Funções de Fila
var_fila*   aloca_fila  (void);

void        free_fila   (var_fila* fila);

bool        fila_vazia  (var_fila* fila);

void        entrar_fila (void* info, int size_of_memory, var_fila* fila);

void*       sair_fila   (var_fila* fila);

void        print_fila  (var_fila* fila, int codigo);


#endif

/**
 * @typedef var_fila A organização dos elementos enfileirados será feita usando
 * uma lista duplamente encadeada, fato que chega a ser trivial ao compararmos
 * ambas estruturas, já que uma fila pode ser vista como uma lista com padrões
 * de inserção mais rígidos.
 */
