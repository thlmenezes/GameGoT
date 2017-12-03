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
#include "../headers/fila.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>



//TOD:
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
void  tree_free (t_node* tree)
{

	/**
	 * @brief Libera uma árvore binária que outrora fora aloca dinamicamente
	 * de acordo com os padrões definidos por aloca_arvore().
	 * @param tree Endereço para a raiz da árvore binária.
	 */

	var_fila* folhas = enfileira_folhas(tree);

	t_node** pop_fila = (t_node**) sair_fila(folhas);

	Character* character;

	while(pop_fila != NULL)
	{
		character = (*pop_fila)->character;
		character_free(character);
		free(pop_fila);
		pop_fila = (t_node**) sair_fila(folhas);
	}

	free_fila(folhas);

	freeTreeAutumn(tree);

}//End tree_free()


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
		print_error(personagens);
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
void  print_character (Character* character, int print_code, var_lista* steroids)
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
				if(steroids == NULL)
					return;

				int nerf = ((Steroids*)busca_lista(steroids, character, INFORMACAO_MODS))->nerf;
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
