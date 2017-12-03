/**
 * @file   arvore.c
 * @author Thales Lima Menezes
 * @date   12/11/2017
 * @brief  Contém a implementação de uma
 * árvore binária e suas funções auxiliares.
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/arvore.h"
#include "../headers/fila.h"
#include <stdlib.h>
#include <math.h>



//TOD
//--------------------------------------------------------------
t_node*  node_create (void)
{

	/**
	 * @brief Aloca um nó baseado na estrutura t_node segundo
	 * alguns parâmetros de inicialização:\nTodos os ponteiros
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
	 * segundo alguns parâmetros de inicialização:\n Todos os
	 * nós da árvore apresentam o atributo Character::character
	 * apontado para NULL.\n
	 * Observação pessoal: Poderia ser melhor; talvez fazer uso
	 * de um algoritmo mais focado em criação por níveis.
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

	/**
	 * @brief Libera, recursivamente, uma árvore binária que
	 * outrora fora alocada dinamicamente de acordo com os
	 * padrões definidos por aloca_arvore().
	 * @param tree Endereço para a raiz da árvore binária.
	 */

	if(tree == NULL)
 		return;

	//Caso não seja uma folha o ponteiro character deve ser NULL
	if(tree->left != NULL && tree->right != NULL)
		tree->character = NULL;

 	tree_free(tree->left);

 	tree_free(tree->right);

 	if(tree->left == NULL && tree->right == NULL)
 	{
		if(tree->character != NULL)
		{
			character_free(tree->character);
			tree->character = NULL;
		}
		free(tree);
 		return;
 	}

	free(tree);

}//End tree_free()


//--------------------------------------------------------------
t_node*  busca_pai (t_node* node, t_node* son)
{

	/**
	 * @brief Busca, em uma árvore binária, o no_pai de um nó.
	 * @param node Possível no_pai.
	 * @param son No_filho à procura do no_pai.
	 * @return Endereço para o no_pai ou, caso não exista, NULL.
	 */

	if( son != NULL )
	{
		if( node == NULL || node->left == son || node->right == son )
			return node;

		t_node* node_return = busca_pai( node->left, son );

		if( node_return == NULL )
			node_return = busca_pai( node->right, son );

		return node_return;
	}

	return son;

}//End busca_pai()


//--------------------------------------------------------------
t_node* busca_no( t_node* tree, Character* target )
{

	/**
	 * @brief Busca, em uma árvore binária, o endereço de um nó
	 * que possue em sua composição um Character* informado.
	 * @param tree Árvore aonde serão conduzidas as buscas.
	 * @param target Character* que buscamos.
	 * @return Endereço para o no que corresponde ao perfil ou,
	 * caso não exista, NULL.
	 */

	if( target  != NULL )
	{
		if( tree == NULL || tree->character == target  )
			return tree;

		t_node* node_return = busca_no( tree->left, target  );

		if( node_return == NULL )
			node_return = busca_no( tree->right, target  );

		return node_return;
	}

	return target;

}//End busca_no()


//--------------------------------------------------------------
var_fila*  enfileira_folhas (t_node* root)
{

	/**
	 * Retorna uma fila com elemento::dados do tipo t_node**
	 * em que cada um de seus ponteiros, quando desreferenciados,
	 * apontam para as folhas da árvore de raiz t_node* root.
	 */

	var_fila* resultado = aloca_fila();

	bool chegou_nas_folhas = false;

	bool excita_no = false;

	int numero_de_folhas = 0;

	entrar_fila(&root, sizeof(t_node *), resultado);

	while( !fila_vazia(resultado) )
	{
		if(excita_no)
			if(resultado->tamanho == numero_de_folhas/2)
			{
				chegou_nas_folhas = true;
				excita_no = false;
			}
			//Tudo que será enfileirado à partir de agora
			//são as folhas da arvore

		if(chegou_nas_folhas)
			if(resultado->tamanho == numero_de_folhas)
				break;

		t_node** pop_fila = (t_node**) sair_fila(resultado);

		t_node* no_destacado = *pop_fila;

		if( !excita_no && no_destacado->left == NULL && no_destacado->right == NULL )
		{
			excita_no = true;
			numero_de_folhas = resultado->tamanho + 1;
		}

		if(excita_no)
		{
			if( no_destacado != NULL )
			{
				t_node* pai_no_destacado = busca_pai(root, no_destacado);
				entrar_fila(&pai_no_destacado, sizeof(t_node *), resultado);
			}

			free(sair_fila(resultado));
			// 1 pai para cada 2 filhos
		}
		else
		{
			if( no_destacado->left != NULL )
				entrar_fila(&no_destacado->left, sizeof(t_node *), resultado);

			if( no_destacado->right != NULL )
				entrar_fila(&no_destacado->right, sizeof(t_node *), resultado);
		}

		free(pop_fila);
	}

	return resultado;

}//End enfileira_folhas()


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

	print_character(root->character, FULL, NULL);

	tree_print_preorder(root->left);

	tree_print_preorder(root->right);

}//End tree_print_preorder()
