/**
 * @file   character.c
 * @author Thales Lima Menezes
 * @date   08/11/2017
 * @brief  Contém a implementação de todas as funções
 * referentes aos personagens e suas informações.
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include "../headers/arvore.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>



//TODO: expandir função print_character() para usar nerfs_n_buffs
//--------------------------------------------------------------
Character*  character_create (char* _name, char* _house, int _agility,
int _strength, int _intelligence, int _health)
{
	/**
	 * @brief Aloca dinamicamente memória para estrutura do tipo
	 * Character, e inicializa por cópia todos os atributos.
	 * @param ALL Informações para preencher os atributos da
	 * estrutura Character alocada.
	 * @return Endereço para estrutura Character alocada.
	 */

	Character* personagem    = (Character*) malloc(sizeof(Character));

	personagem->name         = (char*) malloc((strlen(_name)+1) *sizeof(char));
	/*strlen() retorna o índice da posição do char '\0' logo não considera a si
	no cálculo por isso +1*/
	personagem->house        = (char*) malloc((strlen(_house)+1)*sizeof(char));

	strcpy(personagem->name, _name);

	strcpy(personagem->house, _house);

	personagem->agility      = _agility;

	personagem->strength     = _strength;

	personagem->intelligence = _intelligence;

	personagem->health       = _health;

	return personagem;

}//End character_create()


//--------------------------------------------------------------
Steroids*  aloca_steroids (void)
{
	Steroids* steroids = (Steroids*) malloc(sizeof(Steroids));

	steroids->character = NULL;
	steroids->nerf = steroids->buff = 0;

	return steroids;

}//End aloca_steroids()


//--------------------------------------------------------------
void  insere_steroids (var_lista* lista, Character* character, int nerf, int buff)
{
	var_elemento* elemento = aloca_elemento();

	Steroids* esteroide = aloca_steroids();

	esteroide->character = character;
	esteroide->nerf = nerf;
	esteroide->buff = buff;

	elemento->dados = esteroide;

	insere_lista (FINAL, elemento, sizeof(var_elemento), lista, VAR_ELEMENTO);

	free(elemento);
}//End insere_steroids()


//--------------------------------------------------------------
void  character_free (Character* character)
{
	/**
	 * @brief Libera a memória alocada segundo character_create().
	 * @param character Ponteiro para estrutura Character.
	 */

	if(character != NULL)
	{
		if(character->name  != NULL)
			free(character->name);
		if(character->house != NULL)
			free(character->house);
		free(character);
	}

}//End character_free()


//--------------------------------------------------------------
Character* fight (Character* fighter_one, Character* fighter_two,
int atribute)
{
	/**
	 * @brief Compara o valor do atributo definido para a luta do
	 * fighter_one e do fighter_two, retornando o ponteiro para
	 * o personagem vencedor. Em caso de empate, o ponteiro para
	 * fighter_one deverá ser retornado;
	 * @param atribute Atributo escolhido para a luta.
	 * @return Ponteiro para estrutura Character do vencedor da
	 * disputa.
	 */

	Character* vencedor = fighter_one;

	switch(atribute)
	{
		case 1: if(fighter_two->agility > fighter_one->agility)
					vencedor = fighter_two;
				break;
		case 2: if(fighter_two->strength > fighter_one->strength)
					vencedor = fighter_two;
				break;
		case 3: if(fighter_two->intelligence > fighter_one->intelligence)
					vencedor = fighter_two;
				break;
		case 4: if(fighter_two->health > fighter_one->health)
					vencedor = fighter_two;
				break;
	}

	return vencedor;

}//End fight()


//--------------------------------------------------------------
bool  esta_vivo (Character* users_choice, var_lista* torneio_status)
{
	/**
	 * @brief Busca o personagem na lista do
	 * status atual do torneio, caso morto é enviado o
	 * sinal false.
	 * @return bool O personagem esta vivo?
	 */

	if(users_choice != NULL && torneio_status != NULL)
		return (busca_lista(torneio_status, users_choice, INFORMACAO_ROUND) == users_choice);
	return false;

}//End esta_vivo()


//--------------------------------------------------------------
var_lista*  loadFromFile (char* src_personagens)
{
	/**
	 * @brief Retorna uma lista com todas as estruturas Character
	 * presentes no arquivo segundo o formato correto (name, house,
	 * agility, strenght, intelligence, health) montadas e prontas
	 * para acesso.
	 * @param personagens Nome do arquivo fonte.
	 * @return var_lista* personagens_jogaveis.
	 */

	FILE *personagens;
	personagens = fopen(src_personagens,"r");
	//fopen() retorna NULL em caso de falha
	if(personagens == NULL)
	{
		printf("    ┌─────────────────────────────────────────────────────┐\n");
		printf("    ├──ERROR×──»    ¤    File not found   ¤    «──×ERROR──┤\n");
		printf("    └─────────────────────────────────────────────────────┘\n");
		getchar();
		return NULL;
	}

	char encontrei_char;

	var_lista* personagens_jogaveis = aloca_lista();

	while(fscanf(personagens, "%c", &encontrei_char) > 0)
	{
		/* Sabendo que a função fscanf() "This function
		returns the number of input items successfully
		matched and assigned, which can be fewer than
		provided for, or even zero in the event of an
		early matching failure."*/
		if (encontrei_char != '\n' && encontrei_char != '\r')
		{
			int comprimento = 1;
			while(fscanf(personagens,"%c", &encontrei_char))
			{
				if (encontrei_char == ',')
					break;
				else
					comprimento++;
			}

			int comprimento_strNome = ++comprimento;
			comprimento = -1;
			/* Iniciamos a contagem com -1 devido a presença de um " "
			depois da vírgula*/

			while(fscanf(personagens,"%c", &encontrei_char))
			{
				if (encontrei_char == ',')
					break;
				else
					comprimento++;
			}

			int comprimento_strCasa = ++comprimento;

			Character* personagem_status = (Character*) malloc(sizeof(Character));

			personagem_status->name      = (char*) malloc(comprimento_strNome*sizeof(char));

			personagem_status->house     = (char*) malloc(comprimento_strCasa*sizeof(char));
			// Variáveis comprimento_str já consideram o espaço para o '\0'

			int espacamento = 2;
			// +2 pela string ", " que separa os elementos

			int backwards = comprimento_strCasa + comprimento_strNome + 1;
			/* +1 pela primeira vírgula; e como as variáveis comprimentos
			já incrementam considerando +1 do '\0' não é necessário
			adicionar espacamento*/

			fseek(personagens, -backwards, SEEK_CUR);
			/* Depois de saber todos os comprimentos necessários
			e alocar a memória retornamos o cursor para o
			ínicio da linha*/
			fgets(personagem_status->name, comprimento_strNome, personagens);

			fseek(personagens, espacamento, SEEK_CUR);
			// Avança o cursor para o próximo elemento a ser lido

			fgets(personagem_status->house, comprimento_strCasa, personagens);

			fseek(personagens, espacamento, SEEK_CUR);
			// Avança o cursor para o próximo elemento a ser lido

			fscanf(personagens, "%d", &personagem_status->agility);

			fseek(personagens, espacamento, SEEK_CUR);
			// Avança o cursor para o próximo elemento a ser lido
			fscanf(personagens, "%d", &personagem_status->strength);

			fseek(personagens, espacamento, SEEK_CUR);
			// Avança o cursor para o próximo elemento a ser lido
			fscanf(personagens, "%d", &personagem_status->intelligence);

			fseek(personagens, espacamento, SEEK_CUR);
			// Avança o cursor para o próximo elemento a ser lido
			fscanf(personagens, "%d", &personagem_status->health);

			insere_lista(FINAL, personagem_status, sizeof(Character), personagens_jogaveis, DADO_HEAP);
			// Deixo as areas de memórias ligadas a personagem_status no controle da lista
			personagem_status->name = personagem_status->house = NULL;

			character_free(personagem_status);

		}//end if(encontrei_char != '\n')

	}//end while()

	fclose(personagens);

	return personagens_jogaveis;

}//End loadFromFile()


//--------------------------------------------------------------
void  free_listaCharacter (var_lista* lista)
{
	/**
	 * @brief Libera uma var_lista em que cada elemento::dados
	 * aponta para um Character.
	 */

	var_elemento* cursor = lista->primeiro;
	/*Primeiro liberamos todas as áreas de memória vinculadas à
	Character e atualizamos os ponteiros das áreas liberadas*/

	Character* personagemDestaque;

	while(cursor != NULL)
	{
		personagemDestaque = (Character*) cursor->dados;

		if( personagemDestaque->name  != NULL)
		{
			free( personagemDestaque->name );
			personagemDestaque->name = NULL;
		}

		if( personagemDestaque->house != NULL)
		{
			free( personagemDestaque->house );
			personagemDestaque->house = NULL;
		}

		cursor = cursor->proximo;
	}

	esvazia_lista( lista, true );
	/*Liberamos a memória todos os var_elementos presentes
	na lista, inclusive a area de memória elemento::dados*/

	/**
	 * Observação: Estou ciente que poderia ter usado a função
	 * free_lista() diretamente sem antes esvaziar a lista.
	 */

	free_lista(lista);

}


//--------------------------------------------------------------
void  loadFighters (t_node* torneio, var_lista* personagens_jogaveis)
{
	/**
	 * Carrega todos os personagens que irão participar do torneio nas
	 * folhas da arvore binária.
	 * @param torneio Árvore a ser modificada.
	 * @param personagens_jogaveis Lista contendo os personagens
	 * inscritos no torneio.
	 */

	var_fila* folhas = enfileira_folhas(torneio);

	var_elemento* cursor_lista = personagens_jogaveis->primeiro;

	t_node** cursor_fila = (t_node**) sair_fila(folhas);

	while(cursor_fila != NULL)
	{
		(*cursor_fila)->character = (Character*) cursor_lista->dados;

		free(cursor_fila);

		cursor_fila = (t_node**) sair_fila(folhas);

		cursor_lista = cursor_lista->proximo;

	}

	free_fila(folhas);

}//End LoadFighters()


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
		printf("    ┌─────────────────────────────────────────────────────┐\n");
		printf("    ├──ERROR×──»    ¤    File not found   ¤    «──×ERROR──┤\n");
		printf("    └─────────────────────────────────────────────────────┘\n");
		getchar();
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
Character* character_selection(var_lista* personagensJogaveis)
{
	/**
	 * @brief Imprime na tela todos os personagensJogaveis(PC's)
	 * ocultando seus nomes e suas casas, mostrando ao
	 * usuário somente 1 de seus 4 atributos, escolhido
	 * aleatoriamente. e permite que o usuário selecione o seu
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

	bool valido = false;
	printf("Escolha um personagem dentre os listados acima: ");
	int escolha;
	do {
		scanf("%d", &escolha);
		if(escolha <= personagensJogaveis->tamanho && escolha > 0)
			valido = true;
	} while(!valido);

	return (Character*) busca_lista(personagensJogaveis, &escolha, POSICAO);

}//End character_selection()


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
int atributo_usado, var_lista* esteroids)
{
	Steroids* setup = ((Steroids*)busca_lista(esteroids, character, INFORMACAO_MODS));

	if(codigo_da_acao == TIRED)
		setup->nerf = atributo_usado;
	if(codigo_da_acao == DEAD)
		esvazia_lista(esteroids,true);

}//End update_nerfs()


//--------------------------------------------------------------
void  user_fight (Character* users_choice, var_lista* esteroids, t_node* torneio, int roundNumero, char* rounds)
{
	t_node* node_pai = busca_pai(torneio, busca_no(torneio, users_choice));
	if( node_pai != NULL )
	{
		printf("Seu personagem: ");print_character(users_choice, NERFED, esteroids);

		Character* adversario;
		if(node_pai->left->character == users_choice)
			adversario = node_pai->right->character;
		else
			adversario = node_pai->left->character;

		printf("\nO adversário: ");print_character(adversario, NAME_ONLY, NULL);

		printf("\nSelecione um atributo: ");

		bool valid = false;
		int atributo;
		int nerf = 0;

		if(!lista_vazia(esteroids))
			nerf = ((Steroids*)busca_lista(esteroids, users_choice, INFORMACAO_MODS))->nerf;

		do{
			scanf("%d", &atributo);
			if(atributo != nerf && atributo > 0 && atributo < 5)
				valid = true;
			else
				printf("Escolha inválida");
		}while(!valid);

		Character* vencedor = fight(users_choice,adversario,atributo);

		if(vencedor == users_choice)
		{
			system("reset");
			update_rounds(vencedor,adversario,atributo,rounds);
			update_nerfs(TIRED,users_choice,atributo,esteroids);
			printf("Round %d: Resultado\n\n", roundNumero);
			printf("You Win\n\n");
			print_fight(vencedor,adversario,atributo);
		}
		else
		{
			system("reset");
			update_rounds(vencedor,users_choice,atributo,rounds);
			update_nerfs(DEAD,users_choice,atributo,esteroids);
			printf("Round %d: Resultado\n\n", roundNumero);
			printf("You Lose\n\n");
			print_fight(vencedor,users_choice,atributo);
		}

		node_pai->character = vencedor;
		printf("\n\nPressione qualquer tecla para prosseguir ");
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
void  battle_round (Character* users_choice, var_lista* esteroids,
t_node* torneio, int roundNumero, char* rounds)
{
	///SELO GAMBIARRA
	//metodo perfeito
	//remover o usuário e seu adversário da lista non_playable_characters
	var_lista* non_playable_characters = round_anterior(torneio);

	user_fight(users_choice, esteroids, torneio, roundNumero, rounds);
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

//--------------------------------------------------------------
void  print_character (Character* character, int print_code, var_lista* esteroids)
{
	/**
	 * @brief Imprime estruturas Character alocadas segundo
	 * character_create() e de acordo com as restrições de
	 * escolha de atributo, regra imposta a jogabilidade.
	 */

	if(character != NULL)
 	{
		if(print_code == FULL || print_code == NAME_ONLY || print_code == NERFED)
		{
			printf("%s da Casa %s\n", character->name, character->house);

			if(print_code == NAME_ONLY)
				return;

			int* status = &character->agility;

			if(print_code == NERFED)
			{
				if(esteroids == NULL)
					return;

				int nerf = ((Steroids*)busca_lista(esteroids, character, INFORMACAO_MODS))->nerf;
				int indice = 0;
				char string_exaurido[] = "X) X            : XX";

				if( --nerf != indice)
					printf("1) Agility      : %d\n", status[indice++]);
				else
				{
					indice++;
					printf("%s\n", string_exaurido);
				}

				if( nerf != indice)
					printf("2) Strength     : %d\n", status[indice++]);
				else
				{
					indice++;
					printf("%s\n", string_exaurido);
				}

				if( nerf != indice)
					printf("3) Intelligence : %d\n", status[indice++]);
				else
				{
					indice++;
					printf("%s\n", string_exaurido);
				}

				if( nerf != indice)
					printf("4) Health       : %d\n", status[indice++]);
				else
				{
					indice++;
					printf("%s\n", string_exaurido);
				}
			}
			else
			{
				printf("1) Agility      : %d\n", status[0]);
				printf("2) Strength     : %d\n", status[1]);
				printf("3) Intelligence : %d\n", status[2]);
				printf("4) Health       : %d\n", status[3]);
			}
		}

		if (print_code == ONE_LINE)
		{
			struct timespec seed;
			clock_gettime(CLOCK_REALTIME, &seed);
			srand(seed.tv_nsec);

			int show = rand() % 4 + 1;
			int* status = &character->agility;

			printf("Agility:");
			if(show == 1)
				printf(" %d  ", status[show-1]);
			else
				printf(" ??  ");

			printf("Strength:");

			if(show == 2)
				printf(" %d  ", status[show-1]);
			else
				printf(" ??  ");

			printf("Intelligence:");
			if(show == 3)
				printf(" %d  ", status[show-1]);
			else
				printf(" ??  ");

			printf("Health:");
			if(show == 4)
				printf(" %d  \n", status[show-1]);
			else
				printf(" ??  \n");

		}//end if (print_code == PRINT_LINE)

	}//end if (character != NULL)

}//End print_character()
