/**
 * @file   menu.c
 * @author Thales Lima Menezes
 * @date   03/12/2017
 * @brief  Contém a implementação de todas as funções
 * referentes a menus e seu gerenciamento.
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/battle.h"
#include "../headers/menu.h"
#include <stdlib.h>
#include <stdio.h>


//TOD:
//--------------------------------------------------------------
void  main_menu (char* background)
{

	/**
	 * @brief Centro da execução do programa como um todo,
	 * gerenciando as principais interações com o usuário,
	 * fora do gameloop() em si.
	 */

	print_file(background);

	int input = 0;
	bool valido = false;

	do{
		if(scanf("%d", &input) < 1)
		{
			printf("ERROR INVALID USER INPUT ERROR\n");
			limpa_buffer();
		}
		else
		{
			if(input == 1)
				valido = true;
			else if(input == 2)
			{
				print_file("src_files/help.txt");
				printf("\nPressione 'Enter' para prosseguir");
				limpa_buffer();getchar();
				system_comands(RESET);
				main_menu(background);
			}
			else if(input == 3)
				exit(0);
		}
	}while(!valido);

	switch(gameloop())
	{
		case-1: printf("Character data corrupted or non-existent\n");
				exit(-1);
				break;
		case-2: printf("Insuficient character data\n");
				exit(-2);
				break;
		default:break;
	}

	printf("\n\n[1] Back to Main Menu\n[2] Quit Game\n");
	valido = false;
	do{
		if(scanf("%d", &input) < 1)
		{
			printf("ERROR INVALID USER INPUT ERROR\n");
			limpa_buffer();
		}
		else
		{
			if(input == 1)
			{
				system_comands(RESET);
				main_menu(background);
			}else if(input == 2)
				exit(0);
		}
	}while(!valido);

}//End main_menu()


//--------------------------------------------------------------
int  gameloop (void)
{

	/**
	 * @brief Centro da execução do Jogo como um todo.
	 */

	var_lista* data = loadFromFile("src_files/personagens.txt");

	if(data == NULL)
		return -1;

	t_node* torneio = tree_create();

	var_fila* vagas = enfileira_folhas(torneio);

	var_lista* personagensJogaveis = random_roullete(vagas->tamanho, sizeof(Character), data);

	free_listaCharacter(data);

	free_fila(vagas);

	if(personagensJogaveis == NULL)
	{
		tree_free(torneio);
		return-2;
	}

	loadFighters(torneio, personagensJogaveis);

	system_comands(RESET);
	printf("\t\tEscolha seu personagem\n");

	Character* users_choice = character_selection(personagensJogaveis);

	var_lista* steroids = aloca_lista();
	insere_steroids(steroids,users_choice,0,0);

	var_lista* torneio_status = round_anterior(torneio);
	// lembre-se cada elemento::dados é um t_node**

	char nomeArquivoRounds[] = "src_files/rounds.txt";
	remove(nomeArquivoRounds);

	FILE* rounds;
	int roundNumero = 1;

	while(torneio->character == NULL && esta_vivo(users_choice,torneio_status))
	{
		system_comands(RESET);

		rounds = fopen(nomeArquivoRounds,"a");
		printf("Round %d\n\n",roundNumero);
		fprintf(rounds,"\r\nRound %d\r\n", roundNumero);
		fclose(rounds);

		battle_round(users_choice, steroids, torneio, roundNumero++, nomeArquivoRounds);

		free_lista(torneio_status);
		torneio_status = round_anterior(torneio);
	}

	if(torneio->character != users_choice)
	{
		printf("Lutas do torneio: \n");
		print_file(nomeArquivoRounds);
	}
	exit_game(torneio, personagensJogaveis, steroids, torneio_status);

	return 0;

}//End gameloop()


//--------------------------------------------------------------
Character*  character_selection (var_lista* personagensJogaveis)
{

	/**
	 * @brief Imprime na tela todos os personagensJogaveis(PC's)
	 * ocultando seus nomes e suas casas, e mostrando ao usuário
	 * somente 1 de seus 4 atributos, decisão esta que é
	 * aleatória; e permite que o usuário selecione o seu
	 * campeão para o torneio.
	 * @return Retorna um Character* para o
	 * personagem escolhido pelo usuário.
	 */

	var_elemento* cursor = personagensJogaveis->primeiro;
	int indice = 1;
	while(cursor != NULL)
	{
		printf("Personagem %d:\n", indice++);
		print_character( (Character*)cursor->dados, ONE_LINE, NULL );
		cursor = cursor->proximo;
		printf("\n");
	}

	printf("Escolha um personagem dentre os listados acima: ");
	int escolha = -1;
	bool valido = false;

	do{
		if(scanf("%d", &escolha) < 1)
		{
			printf("ERROR INVALID USER INPUT ERROR\n");
			limpa_buffer();
		}
		else
		{
			if(escolha <= personagensJogaveis->tamanho && escolha > 0)
				valido = true;
			else
				printf("ERROR USER INPUT OUT OF RANGE ERROR\n");
		}
	}while(!valido);

	return (Character*) busca_lista(personagensJogaveis, &escolha, POSICAO);

}//End character_selection()


//--------------------------------------------------------------
void  exit_game (t_node* arvore, var_lista* participantes,
var_lista* modificadores, var_lista* torneio_status)
{

	/**
	 * @brief Gerencia a liberação de memória das principais
	 * estruturas usadas durante a execução do programa.
	 */

	if(arvore != NULL)
		tree_free(arvore);

	if (participantes != NULL)
	{
		esvazia_lista(participantes, false);
		free_lista(participantes);
	}

	if (modificadores != NULL)
		free_lista(modificadores);

	if (torneio_status != NULL)
		free_lista(torneio_status);

}//End exit_game()
