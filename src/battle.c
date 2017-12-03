/**
 * @file   battle.c
 * @author Thales Lima Menezes
 * @date   03/12/2017
 * @brief  Contém a implementação de todas as funções
 * referentes as lutas e seus gerenciamento.
 */
#include "../headers/battle.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


//TOD:
//--------------------------------------------------------------
void  update_rounds (Character* player_one, Character* player_two, int atributo_usado, char* src_rounds)
{
	/**
	 * @brief Registra uma luta em um arquivo seguindo o padrão
	 * vencedor(inteiro nomeatributo) vs perdedor(inteiro nomeatributo).
	 * @param rounds Nome do arquivo de destino das informações da luta.
	 */

	FILE* rounds;
	rounds = fopen(src_rounds,"a");

	if(rounds == NULL)
	{
		print_error(rounds);
		return;
	}

	char* atributoNome = (char*) malloc((strlen("Intelligence")+1)*sizeof(char));
	int*  player_atribute;

	switch(atributo_usado)
	{
		case 1: strcpy(atributoNome, "Agility");
				break;
		case 2: strcpy(atributoNome, "Strength");
				break;
		case 3: strcpy(atributoNome, "Intelligence");
				break;
		case 4: strcpy(atributoNome, "Health");
				break;
	}

	player_atribute = &player_one->agility;

	fprintf(rounds,"%s (%d %s)", player_one->name, player_atribute[atributo_usado-1], atributoNome);

	fprintf(rounds," X ");

	player_atribute = &player_two->agility;

	fprintf(rounds,"%s (%d %s)\r\n", player_two->name, player_atribute[atributo_usado-1], atributoNome);

	fclose(rounds);

	free(atributoNome);

}//End update_rounds()


//--------------------------------------------------------------
var_lista*  round_anterior (t_node* root)
{
	/**
	 * @brief Percorre a arvore e caso chegue numa folha, ou em
	 * uma "pseudo-folha"(rastros de lutas já ocorridas na árvore),
	 * insere na lista.
	 * @param root Árvore referente ao torneio.
	 * @return var_lista *round_anterior.
	 */

	var_lista* resultado = aloca_lista();

	bool chegou_no_round = false;

	bool excita_no = false;

	int numero_de_folhas = 0;

	insere_lista (FINAL, &root, sizeof(t_node*), resultado, DADO_HEAP);

	while( !lista_vazia(resultado) )
	{
		if(excita_no)
			if(resultado->tamanho == numero_de_folhas/2)
			{
				chegou_no_round = true;
				excita_no = false;
			}
			//Tudo que será enfileirado à partir de agora
			//são as folhas da arvore

		if(chegou_no_round)
			if(resultado->tamanho == numero_de_folhas)
				break;

		t_node** saiu_lista = (t_node**) pop_lista(resultado, 0);

		t_node* no_destacado = *saiu_lista;

		if( !excita_no && no_destacado->character != NULL )
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
				insere_lista(FINAL, &no_destacado->left, sizeof(t_node*), resultado, DADO_HEAP);

			if( no_destacado->right != NULL )
				insere_lista(FINAL, &no_destacado->right, sizeof(t_node*), resultado, DADO_HEAP);
		}

		free(saiu_lista);
	}

	return resultado;
}


//--------------------------------------------------------------
void  print_fight (Character* vencedor, Character* adversario, int atributo)
{
	if(vencedor != NULL && adversario != NULL)
	{
		char* atributoNome = (char*) malloc((strlen("Intelligence")+1)*sizeof(char));
		int*  player_atribute;

		switch(atributo)
		{
			case 1: strcpy(atributoNome, "Agility");
					break;
			case 2: strcpy(atributoNome, "Strength");
					break;
			case 3: strcpy(atributoNome, "Intelligence");
					break;
			case 4: strcpy(atributoNome, "Health");
					break;
		}

		player_atribute = &vencedor->agility;

		printf("%s (%d %s)", vencedor->name, player_atribute[atributo-1], atributoNome);

		printf(" vs ");

		player_atribute = &adversario->agility;

		printf("%s (%d %s)\r\n", adversario->name, player_atribute[atributo-1], atributoNome);

		free(atributoNome);

		printf("%s da casa %s foi vitorioso", vencedor->name, vencedor->house);

	}//end if(vencedor != NULL && adversario != NULL)

}//End print_fight()


//--------------------------------------------------------------
void  update_nerfs (int codigo_da_acao, Character* character,
int atributo_usado, var_lista* steroids)
{
	Steroids* setup = ((Steroids*)busca_lista(steroids, character, INFORMACAO_MODS));

	if(codigo_da_acao == TIRED)
		setup->nerf = atributo_usado;
	if(codigo_da_acao == DEAD)
		esvazia_lista(steroids,true);

}//End update_nerfs()


//--------------------------------------------------------------
void  user_fight (Character* users_choice, var_lista* steroids, t_node* torneio, int roundNumero, char* rounds)
{
	t_node* node_pai = busca_pai(torneio, busca_no(torneio, users_choice));
	if( node_pai != NULL )
	{
		printf("Seu personagem: ");print_character(users_choice, NERFED, steroids);

		Character* adversario;
		if(node_pai->left->character == users_choice)
			adversario = node_pai->right->character;
		else
			adversario = node_pai->left->character;

		printf("\nO adversário: ");print_character(adversario, NAME_ONLY, NULL);

		printf("\nSelecione um atributo: ");

		int atributo, nerf = 0;
		bool valid = false;

		if(!lista_vazia(steroids))
			nerf = ((Steroids*)busca_lista(steroids, users_choice, INFORMACAO_MODS))->nerf;

		do{
			if(scanf("%d", &atributo) < 1)
			{
				printf("ERROR INVALID USER INPUT ERROR\n");
				limpa_buffer();
			}
			else
			{
				if(atributo != nerf && atributo > 0 && atributo < 5)
					valid = true;
				else
					printf("ERROR USER INPUT OUT OF RANGE ERROR\n");
			}
		}while(!valid);

		Character* vencedor = fight(users_choice,adversario,atributo);

		if(vencedor == users_choice)
		{
			system("reset");
			update_rounds(vencedor,adversario,atributo,rounds);
			update_nerfs(TIRED,users_choice,atributo,steroids);
			printf("Round %d: Resultado\n\n", roundNumero);
			print_file("src_files/you_win.txt");
			print_fight(vencedor,adversario,atributo);
		}
		else
		{
			system("reset");
			update_rounds(vencedor,users_choice,atributo,rounds);
			update_nerfs(DEAD,users_choice,atributo,steroids);
			printf("Round %d: Resultado\n\n", roundNumero);
			print_file("src_files/you_lose.txt");
			print_fight(vencedor,users_choice,atributo);
		}

		node_pai->character = vencedor;
		printf("\n\nPressione 'Enter' para prosseguir ");
		limpa_buffer();getchar();

	}//end if( node_pai != NULL )

}//End user_fight()


//--------------------------------------------------------------
void  fight_judge (Character* fighter_one, Character* fighter_two, t_node* torneio, char* rounds)
{
	t_node* node_pai = busca_pai(torneio, busca_no(torneio, fighter_one));
	if( node_pai != NULL )
	{
		if(fighter_one != NULL && fighter_two != NULL)
		{
			struct timespec seed;
			clock_gettime(CLOCK_REALTIME, &seed);
			srand(seed.tv_nsec);
			int atributo = rand() % 4 + 1;

			Character* vencedor = fight(fighter_one,fighter_two,atributo);

			if(vencedor == fighter_one)
				update_rounds(vencedor, fighter_two, atributo, rounds);
			else
				update_rounds(vencedor, fighter_one, atributo, rounds);

			node_pai->character = vencedor;
		}
	}
}//End fight_judge()


//--------------------------------------------------------------
void  battle_round (Character* users_choice, var_lista* steroids,
t_node* torneio, int roundNumero, char* rounds)
{
	///SELO GAMBIARRA
	//metodo perfeito
	//remover o usuário e seu adversário da lista non_playable_characters
	var_lista* non_playable_characters = round_anterior(torneio);

	user_fight(users_choice, steroids, torneio, roundNumero, rounds);
	//elemento::dados são t_node**

	t_node* node_pai = busca_pai(torneio, busca_no(torneio, users_choice));

	t_node** source_one, **source_two;

	Character* player_one, *player_two;

	if(torneio->character == NULL)
	{

		while(!lista_vazia(non_playable_characters))
		{
			source_one = (t_node**) pop_lista(non_playable_characters,0);
			source_two = (t_node**) pop_lista(non_playable_characters,0);

			if( source_one != NULL && source_two != NULL )
			{
				player_one = (*source_one)->character;
				player_two = (*source_two)->character;
				//gambiarra
				if(! ( player_one == node_pai->left->character
					|| player_one == node_pai->right->character
					|| player_two == node_pai->left->character
					|| player_two == node_pai->right->character ) )
				{
					fight_judge(player_one, player_two, torneio, rounds);
				}

				free(source_one);
				free(source_two);
			}
		}
	}

	free_lista(non_playable_characters);

}//End battle_rounds()
