//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   battle.h
 * @author Thales Lima Menezes
 * @date   03/12/2017
 * @brief  Contém todas as definições, informações e funções
 * referentes as lutas e seus gerenciamento.
 */

#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "character.h"

void       update_rounds      (Character* player_one, Character* player_two,
int atributo_usado, char* src_rounds);

var_lista* round_anterior     (t_node* root);

void       print_fight        (Character* vencedor, Character* adversario,
int atributo);

void       update_nerfs       (int codigo_da_acao, Character* character,
int atributo_usado, var_lista* steroids);

void       user_fight         (Character* users_choice, var_lista* steroids,
t_node* torneio, int roundNumero, char* rounds);

void       fight_judge        (Character* fighter_one, Character* fighter_two,
t_node* torneio, char* rounds);

void       battle_round       (Character* users_choice, var_lista* steroids,
t_node* torneio, int roundNumero, char* rounds);

#endif
