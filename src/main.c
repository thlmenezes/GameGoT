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

	print_file("main_menu.txt");
	while(getchar() != '\n');

	var_lista* data = loadFromFile("personagens.txt");

	t_node* torneio = tree_create();

	var_fila* vagas = enfileira_folhas(torneio);

	var_lista* personagensJogaveis = random_roullete(vagas->tamanho, sizeof(Character), data);

	free_listaCharacter(data);

	free_fila(vagas);

	loadFighters(torneio, personagensJogaveis);


	system("reset");
	printf("\t\tEscolha seu personagem\n");

	Character* users_choice = character_selection(personagensJogaveis);

	var_lista* esteroids = aloca_lista();
	insere_steroids(esteroids,users_choice,0,0);

	var_lista* torneio_status = round_anterior(torneio);
	// lembre-se cada elemento::dados é um t_node**

	char nomeArquivoRounds[] = "rounds.txt";
	remove(nomeArquivoRounds);

	FILE* rounds;
	int roundNumero = 1;

	while(torneio->character == NULL && esta_vivo(users_choice,torneio_status))
	{
		system("reset");

		rounds = fopen(nomeArquivoRounds,"a");
		printf("Round %d\n\n",roundNumero);
		fprintf(rounds,"\r\nRound %d\r\n", roundNumero);
		fclose(rounds);

		battle_round(users_choice, esteroids, torneio, roundNumero++, nomeArquivoRounds);

		free_lista(torneio_status);
		torneio_status = round_anterior(torneio);
	}

	//tree_print_preorder(torneio);

	print_file(nomeArquivoRounds);

	free_listaCharacter(personagensJogaveis);

	free_lista(esteroids);

	free_lista(torneio_status);

	tree_free(torneio);

/*	var_elemento* cursor = roundAnterior->primeiro;

	while(cursor != NULL)
	{
		print_character((*(t_node**)cursor->dados)->character ,NULL);
		printf("\n");
		cursor = cursor->proximo;
	}

	print_file(nomeArquivoRounds);
*/

	return 0;
}
