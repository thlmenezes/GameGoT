//http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsection
/**
 * @file   menu.h
 * @author Thales Lima Menezes
 * @date   03/12/2017
 * @brief  Contém todas as definições, informações e funções
 * referentes a menus e seu gerenciamento.
 */

#ifndef __MENU_H__
#define __MENU_H__

#include "character.h"
#include "lista_dupla.h"

void       main_menu           (char* background);

Character* character_selection (var_lista* personagensJogaveis);

int        gameloop            (void);

void       exit_game           (t_node* arvore, var_lista* participantes,
var_lista* modificadores, var_lista* torneio_status);

#endif
