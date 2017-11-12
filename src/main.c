/**
 * @file   main.c
 * @author Thales Lima Menezes
 * @date   01/11/2017
 * @brief  Arquivo para execução das funções das bibliotecas criadas
 *
 * @mainpage Segundo Trabalho de Estrutura de Dados
 * @section intro_sec Introdução
 * Disciplina CIC 116319 - Estruturas de Dados - Turma A do Professor Marcos F. Caetano.
 */
//https://stackoverflow.com/questions/8013471/how-to-use-rand-to-generate-numbers-in-a-range
//http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
//http://www.gnu.org/software/make/manual/make.html
//https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
//https://stackoverflow.com/questions/1139271/makefiles-with-source-files-in-different-directories
#include "../headers/lista_dupla.h"
//#include "../headers/character.h"
#include "../headers/arvore.h"
//#include <stdlib.h>
//#include <stdio.h>

int main(void)
{
	t_node* node = node_create();
	tree_free(node);
	tree_free(tree_create());
	return 0;
}
/*
int main (void)
{
	char _name[9] = malloc, _house[6];
	int _agility, _strenght, _intelligence, _health;
	scanf("%s %s %d %d %d %d", &_name, &_house, &_agility, &_strenght, &_intelligence, &_health);
	Character* chara = character_create(_name, _house, _agility, _strenght, _intelligence, _health);
	return 0;
}
*/
