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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



//TODO: expandir função print_character() para usar nerfs_n_buffs
//--------------------------------------------------------------
Character*  character_create(char* _name, char* _house, int _agility,
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
void  character_free(Character* character)
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
Character* fight(Character* fighter_one, Character* fighter_two,
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
void  print_character(Character* character, void* nerfs_n_buffs)
{
	/**
	 * @brief Imprime estruturas Character alocadas segundo
	 * character_create() e de acordo com as restrições de
	 * escolha de atributo, regra imposta a jogabilidade.
	 */

	printf("%s da Casa %s\n", character->name, character->house);

	if(nerfs_n_buffs != NULL)
		return;

	printf("1) Agility      : %d\n", character->agility);
	printf("2) Strength     : %d\n", character->strength);
	printf("3) Intelligence : %d\n", character->intelligence);
	printf("4) Health       : %d\n", character->health);

}//End print_character()



//--------------------------------------------------------------
var_lista* LoadFromFile(char* src_personagens)
{
	/**
	 * @brief Retorna uma lista com todas
	 * as estruturas Character presentes no
	 * arquivo segundo o formato correto
	 * (name, house, agility, strenght,
	 * intelligence, health) montadas e
	 * prontas para acesso.
	 * @param personagens Nome do arquivo fonte.
	 * @return var_lista* personagens_jogaveis
	 */

	FILE *personagens;
	personagens = fopen(src_personagens,"r");

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

			insere_lista(INSERE_FINAL,personagem_status,sizeof(Character),personagens_jogaveis,INSERE_DADO_HEAP);
			// Deixo as areas de memórias ligadas a personagem_status no controle da lista
			personagem_status->name = personagem_status->house = NULL;

			character_free(personagem_status);

		}//end if(encontrei_char != '\n')

	}//end while()

	fclose(personagens);

	return personagens_jogaveis;

}//End LoadFromFile()


//--------------------------------------------------------------
void free_ListaCharacter(var_lista* lista)
{
	/**
	 * @brief ñ sei dizer ainda.
	 */

	var_elemento* cursor = lista->primeiro;
	//Primeiro libera todas as áreas de memória vinculadas à Character
	while(cursor != NULL)
	{
		if( ((Character*) cursor->dados)->name  != NULL)
		{
			free( ((Character*) cursor->dados)->name );
			((Character*) cursor->dados)->name = NULL;
		}

		if( ((Character*) cursor->dados)->house != NULL)
		{
			free( ((Character*) cursor->dados)->house );
			((Character*) cursor->dados)->house = NULL;
		}

		cursor = cursor->proximo;
	}

	//esvazia_lista(lista,true);
	/*excluir todos os var_elementos presentes na lista,
	com sinal positivo(true) para exclusão das áreas
	de memória*/

	free_lista(lista);

}
