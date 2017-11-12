/**
 * @file   estruturas.h
 * @author Thales Lima Menezes
 * @date   12/11/2017
 * @brief  Arquivo que contém a definição de uma
 * árvore binária e suas funções auxiliares.
 */

#ifndef __ARVORE_H__
#define __ARVORE_H__
#include "character.h"

typedef struct node{
	Character* character;
	struct node* left;
	struct node* right;
} t_node;

//Funções de Arvore
t_node*     node_create(void);

t_node*     tree_create(void);

t_node*     aloca_arvore(int total_de_nos);

void        tree_free(t_node* tree);

void        tree_print_preorder(t_node* root);

#endif

/*
 * Área para cometário sobre as definições e estruturas do cabeçalho
 */
