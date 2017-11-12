//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   estruturas.h
 * @author Thales Lima Menezes
 * @date   31/10/2017
 * @brief  Arquivo que contém a definição de todas as estruturas de dados essenciais para o desenvolvimento da solução do problema.
 */

#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__


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

#include "character.h"
typedef struct elemento_no{
	Character* info;
	struct elemento_no* esquerda;
	struct elemento_no* direita;
} t_node;


typedef enum { PRE_ORDEM, ORDEM, POS_ORDEM } print_arvore_code;

/*
//Funções de Arvore
var_no*     aloca_arvore(var_tipo tipo);
• t_node* node_create();
	–retorna endereço para estrutura do tipo t_node alocada dinami-
camente. Os ponteiros character, left e right são inicializados
com o valor NULL;
• t_node* tree_create();
	– retorna o endereço para o nó raiz de uma da árvore binária com-
pleta de quatro nı́veis (Figura 1). TODOS os nós das árvores
apresentam o atributo character apontado para NULL.
• void tree_free(t_node* tree);
	– remove de forma recursiva todos os nós presentes da árvore. A
memória referente ao atributo character também deve ser libe-
rada;
• void tree_print_preorder(t_node* root);
	– percore a árvore binária em pré-ordem, imprimindo os persona-
gens referenciados em character;

//Funções de Fila
var_fila*   aloca_fila  (void);

void        free_fila   (var_fila* fila);

bool        fila_vazia  (var_fila* fila);

void        entrar_fila (void* info, var_fila* fila);

void*       sair_fila   (var_fila* fila);
//FUNÇÕES DE USO PRIVADO PARA Fila
*/
            //Funções de Lista Simplesmente Encadeada
						var_elemento*  aloca_elemento(void);

						var_lista*     aloca_lista   (void);

						void           free_lista    (var_lista* lista);

						bool           lista_vazia   (var_lista* lista);

						void           insere        (int finalouinicio, void* info, var_lista* lista, int codigo);

						void           deleta_ultimo (var_lista* lista);

						void           print_lista   (var_lista* lista, int codigo);

#endif

/**
 * @var bool::false
 *     Um teste.
 *
 * @struct  elemento_no
 * @brief   Define os componentes essenciais para um elemento da estrutura de árvore, podendo ser uma raiz, um galho/nó ou uma folha.
 * @var elemento_no::dado
 *     Uma variável do tipo elemento, podendo armazenar a informação como int, char ou float.
 * @var elemento_no::esquerda
 *     Qualquer coisa para testes1.
 * @var elemento_no::direita
 *     Qualquer coisa para testes2.
 */
