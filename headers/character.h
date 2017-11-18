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


Character* character_create(char* _name, char* _house, int _agility, int _strength, int _intelligence, int _health);
/*
	– aloca dinamicamente memória para estrutura do tipo Character.
Inicializa POR CÓPIA os atributos name, house, agility,
strength, intelligence e health, utilizando, respectivamente,
os parâmetros _name, _house, _agility, _strength, _intelligence
e _health. Ao final, a função retorna o endereço para estrutura
Character alocada;
• void character_free(Character* character);
	– libera a memória alocada e referenciada por character;
• Character* fight(Character* fighter_one, Character* fighter_two,
int atribute);
	– Compara o valor do atributo definido por atribute do fighter_one
e do fighter_two, retornando o ponteiro para o personagem ven-
cedor. Em caso de empate, o ponteiro para fighter_one deverá
ser retornado;
*/

#endif
