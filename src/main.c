/**
 * @file   main.c
 * @author Thales Lima Menezes
 * @date   01/11/2017
 * @brief  executa funções das bibliotecas criadas
 *
 * @mainpage Segundo Trabalho da Disciplina Estrutura de Dados
 * @section intro_sec Introdução
 * Disciplina CIC 116319 - Estruturas de Dados - Turma A do Professor Marcos F. Caetano.
 * @section dev_team_sec Desenvolvedores
 * Projeto desenvolvido em conjunto pelos alunos:\n
	• Fernanda Macedo de Sousa - 17/0010058\n
	• Thales Lima Menezes - 17/0045919
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include "../headers/arvore.h"
#include "../headers/fila.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



//TODO: atualizar funções de liberação para retornar ponteiro NULL
int main (void)
{
	var_lista* data =  LoadFromFile("personagens.txt");

	var_lista* personagens_jogaveis = random_roullete(2, sizeof(Character), data);

	free_listaCharacter(data);

	char nomeArquivoRounds[] = "rounds.txt";
	remove(nomeArquivoRounds);

	FILE* rounds;
	int roundNumero = 1;
	rounds = fopen(nomeArquivoRounds,"a");

	fprintf(rounds,"Round %d:\r\n", roundNumero++);

	fclose(rounds);

	update_rounds(  (Character*) personagens_jogaveis->primeiro->dados,
					(Character*) personagens_jogaveis->ultimo->dados,
					2, nomeArquivoRounds);

	print_file(nomeArquivoRounds);

	free_listaCharacter(personagens_jogaveis);

/*	t_node* torneio = tree_create();

	LoadFighters(torneio, personagens_jogaveis);

	var_fila* print = enfileira_folhas(torneio);

	t_node** cursor = (t_node**)sair_fila(print);

	while(cursor != NULL)
	{
		print_character((*cursor)->character,NULL);
		printf("\n");
		free(cursor);
		cursor = (t_node**)sair_fila(print);
	}
	free_fila(print);

	free_listaCharacter(personagens_jogaveis);

	tree_free(torneio);
*/
	return 0;
}
/*var_elemento* cursor = personagens_jogaveis->primeiro;

while(cursor != NULL)
{
	print_character(cursor->dados,NULL);
	printf("\n");
	cursor = cursor->proximo;
}*/
