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

typedef struct {
	Character* character;
	int nerf;
	int buff;
} Steroids;

typedef struct node{
	Character* character;
	struct node* left;
	struct node* right;
} t_node;

#include "arvore.h"

Character* character_create   (char* _name, char* _house, int _agility,
int _strength, int _intelligence, int _health);

Steroids*  aloca_steroids     (void);

void       insere_steroids    (var_lista* lista, Character* character,
int nerf, int buff);

void       character_free     (Character* character);

Character* fight              (Character* fighter_one, Character* fighter_two,
int atribute);

bool       esta_vivo          (Character* users_choice, var_lista* torneio_status);

var_lista* loadFromFile       (char* src_personagens);

void       loadFighters       (t_node* torneio, var_lista* personagens_jogaveis);

void       free_listaCharacter(var_lista* lista);

void       update_rounds      (Character* player_one, Character* player_two,
int atributo_usado, char* src_rounds);

var_lista* round_anterior     (t_node* root);

Character* character_selection(var_lista* personagensJogaveis);

void       print_fight        (Character* vencedor, Character* adversario,
int atributo);

void       update_nerfs       (int codigo_da_acao, Character* character,
int atributo_usado, var_lista* esteroids);

void       user_fight         (Character* users_choice, var_lista* esteroids,
t_node* torneio, int roundNumero, char* rounds);

void       fight_judge        (Character* fighter_one, Character* fighter_two,
t_node* torneio, char* rounds);

void       elimina_duplicata  (var_lista* non_playable_characters, t_node* node_pai, t_node* torneio);

void       battle_round       (Character* users_choice, var_lista* esteroids,
t_node* torneio, int roundNumero, char* rounds);

void       print_character    (Character* character, int print_code,
var_lista* esteroids);

#endif
