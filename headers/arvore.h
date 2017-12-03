//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   arvore.h
 * @author Thales Lima Menezes
 * @date   12/11/2017
 * @brief  Contém a definição de uma árvore binária
 * e suas funções auxiliares.
 */

#ifndef __ARVORE_H__
#define __ARVORE_H__

#include "character.h"

#include "fila.h"

//Funções de Árvore
t_node*     node_create        (void);

t_node*     tree_create        (void);

t_node*     aloca_arvore       (int total_de_nos);

void        tree_free          (t_node* tree);

t_node*     busca_pai          (t_node* root, t_node* son);

t_node*     busca_no           (t_node* root, Character* focus);

var_fila*   enfileira_folhas   (t_node* root);

void        tree_print_preorder(t_node* root);

#endif
