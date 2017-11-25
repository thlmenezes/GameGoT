//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   character.h
 * @author Thales Lima Menezes
 * @date   08/11/2017
 * @brief  Contém todas as definições, informações e funções
 * relacionadas com os personagens e suas interações.
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "lista_dupla.h"


typedef struct {
	char* name;
	char* house;
	int agility;
	int strength;
	int intelligence;
	int health;
} Character;


Character* character_create(char* _name, char* _house, int _agility,
int _strength, int _intelligence, int _health);

void       character_free(Character* character);

Character* fight(Character* fighter_one, Character* fighter_two,
int atribute);

void       print_character(Character* character, void* nerfs_n_buffs);

var_lista* LoadFromFile(char* src_personagens);

void       esvazia_listaChar(var_lista* lista);

#endif
