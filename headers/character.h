/**
 * @file   character.h
 * @author Thales Lima Menezes
 * @date   08/11/2017
 * @brief  Contém todas as definições, informações e funções
 * relacionadas com os personagens e suas interações.
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__


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

#endif
