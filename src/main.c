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
#include "../headers/fila.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	var_fila* fila = aloca_fila();

	int numero = 4;

	print_fila(fila, INT);

	entrar_fila(&numero, sizeof(int), fila);

	numero = 7;

	entrar_fila(&numero, sizeof(int), fila);

	print_fila(fila, INT);

	int* ponteiro_numero = (int*) sair_fila(fila);

	printf("%d\n", *ponteiro_numero);

	free_fila(fila);

	free(ponteiro_numero);

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
