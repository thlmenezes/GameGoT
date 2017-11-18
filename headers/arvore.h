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

typedef struct node{
	Character* character;
	struct node* left;
	struct node* right;
} t_node;

//Funções de Árvore
t_node*     node_create(void);

t_node*     tree_create(void);

t_node*     aloca_arvore(int total_de_nos);

void        tree_free(t_node* tree);

void        tree_print_preorder(t_node* root);

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
