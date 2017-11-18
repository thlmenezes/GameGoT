/**
 * @file   arvore.c
 * @author Thales Lima Menezes
 * @date   12/11/2017
 * @brief  Contém a implementação de uma
 * árvore binária e suas funções auxiliares.
 */

#include "../headers/arvore.h"
#include <stdlib.h>
#include <math.h>



//TOD
//--------------------------------------------------------------
t_node*  node_create (void)
{
	/**
	 * @brief Aloca um nó baseado na estrutura t_node segundo
	 * alguns parâmetros de inicialização: Todos os ponteiros
	 * (character, left e right) são inicializados com o valor
	 * NULL.
	 * @return Endereço para nó alocado dinamicamente.
	 */

	t_node* novo_no = (t_node*) malloc(sizeof(t_node));

	novo_no->character  = NULL;// }
	novo_no->left       = NULL;// } Padrões de inicialização
	novo_no->right      = NULL;// }

	return novo_no;

}//End node_create()


//--------------------------------------------------------------
t_node*  tree_create (void)
{
	/**
	 * @brief Aloca uma arvore binária completa de 4 níveis
	 * segundo alguns parâmetros de inicialização: Todos os
	 * nós da árvore apresentam o atributo Character::character
	 * apontado para NULL.
	 * @return Endereço para o nó raiz da árvore binária.
	 */

	int nivel = 4, indice = nivel, total_de_nos = 0;
	/*O cálculo abaixo retorna quantos nós uma árvore tem
	baseado em seu número de níveis*/
	while(indice > -1)
		total_de_nos += pow(2,indice--);
	return aloca_arvore(total_de_nos);

}//End tree_create()


//--------------------------------------------------------------
t_node*  aloca_arvore (int total_de_nos)
{
	/**
	 * @brief Aloca dinamicamente uma árvore binária de nós criados por
	 * node_create().
	 * @param total_de_nos Número de nós que irão compor a árvore binária.
	 * @return Endereço para a raiz da árvore binária.
	 */

	if(total_de_nos == 0)
		return NULL;

	int nos_a_esquerda = total_de_nos/2;
	int nos_a_direita  = total_de_nos -nos_a_esquerda -1;

	/*Temos que subtrair 1 no cálculo acima porque o nó raíz
	também está incluído na contagem de nós de "total_de_no"*/

	t_node* novo_no = node_create();

	novo_no->left = aloca_arvore(nos_a_esquerda);

	novo_no->right = aloca_arvore(nos_a_direita);

	return novo_no;

}//End aloca_arvore()


//--------------------------------------------------------------
void  tree_free (t_node* tree)
{
	//TODO: IMPLEMENTAR a funcionalidade de limpar os 'character' das folhas primeiro
	/**
	 * @brief Libera uma árvore binária que outrora fora aloca dinamicamente
	 * de acordo com os padrões definidos por aloca_arvore().
	 * @param tree Endereço para a raiz da árvore binária.
	 */

	if(tree == NULL)
		return;
	tree_free(tree->left);
	tree_free(tree->right);
	free(tree);

}//End tree_free()


//--------------------------------------------------------------
void  tree_print_preorder (t_node* root)
{
	/**
	 * @brief Percorre uma árvore binária, que outrora fora aloca dinamicamente
	 * de acordo com os padrões definidos por aloca_arvore(); em pré-ordem,
	 * imprimindo os personagens referenciados em Character::character.
	 * @param root Endereço para a raiz da árvore binária.
	 */

	if(root == NULL)
			return;

	//print_character(root);

	tree_print_preorder(root->left);

	tree_print_preorder(root->right);

}//End tree_print_preorder()
