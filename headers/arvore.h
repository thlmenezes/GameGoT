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

t_node*     freeTreeAutumn     (t_node* root);

void        tree_print_preorder(t_node* root);

t_node*     busca_pai          (t_node* root, t_node* son);

t_node*     busca_no           (t_node* root, Character* focus);

var_fila*   enfileira_folhas   (t_node* root);

#endif

/**
 * @struct node
 * @var node::character ponteiro para variável do
 * tipo Character que armazena toda a ficha de um
 * personagem.
 * @var node::left ponteiro para o nó à esquerda
 * do nó atual dentro da árvore.
 * @var node::right ponteiro para o nó à direita
 * do nó atual dentro da árvore.
 */
