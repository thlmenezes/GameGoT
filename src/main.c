/**
 * @file   main.c
 * @author Thales Lima Menezes
 * @date   01/11/2017
 * @brief  executa funções das bibliotecas criadas
 *
 * @mainpage Segundo Trabalho da Disciplina Estrutura de Dados
 * @section intro_sec Introdução
 * Disciplina CIC 116319 - Estruturas de Dados - Turma A do Professor Marcos F. Caetano.
 * @section dev_team_sec Desenvolvedores
 * Projeto desenvolvido em conjunto pelos alunos:\n
	• Fernanda Macedo de Sousa - 17/0010058\n
	• Thales Lima Menezes - 17/0045919
 */
//https://stackoverflow.com/questions/8013471/how-to-use-rand-to-generate-numbers-in-a-range
//http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
//http://www.gnu.org/software/make/manual/make.html
//https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
//https://stackoverflow.com/questions/1139271/makefiles-with-source-files-in-different-directories
#include "../headers/character.h"
#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	char _name[20], _house[20];
	int _agility, _strength, _intelligence, _health;

	scanf("%s %s %d %d %d %d", _name, _house, &_agility, &_strength, &_intelligence, &_health);

	Character* kungLao = character_create(_name, _house, _agility, _strength, _intelligence, _health);

	scanf("%s %s %d %d %d %d", _name, _house, &_agility, &_strength, &_intelligence, &_health);

	Character* chunLee = character_create(_name, _house, _agility, _strength, _intelligence, _health);

	print_character(fight(kungLao,chunLee,2), NULL);

	character_free(kungLao);
	character_free(chunLee);

	return 0;
}
