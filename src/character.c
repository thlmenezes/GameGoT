/**
 * @file   character.c
 * @author Thales Lima Menezes
 * @date   08/11/2017
 * @brief  Contém a implementação de todas as funções
 * referentes aos personagens e suas informações.
 */

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

	if(character->name  != NULL)
		free(character->name);
	if(character->house != NULL)
		free(character->house);

	free(character);

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
	if(nerfs_n_buffs != NULL)
		return;

	printf("%s da Casa %s\n", character->name, character->house);
	printf("1) Agility      : %d\n", character->agility);
	printf("2) Strength     : %d\n", character->strength);
	printf("3) Intelligence : %d\n", character->intelligence);
	printf("4) Health       : %d\n", character->health);

}//End print_character()
