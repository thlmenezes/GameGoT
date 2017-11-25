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
//https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
//http://www.theasciicode.com.ar/extended-ascii-code/box-drawings-single-horizontal-line-character-ascii-code-196.html
#include "../headers/character.h"
#include <stdlib.h>
#include <stdio.h>


//TODO: atualizar funções de liberação para retornar ponteiro NULL
int main (void)
{
	char string[] = "personagens.txt";
	var_lista* personagens_jogaveis = LoadFromFile(string);

	printf("\n");
	var_elemento* cursor = personagens_jogaveis->primeiro;

	while(cursor != NULL)
	{
		print_character(cursor->dados,NULL);
		printf("\n");
		character_free(cursor->dados);
		cursor->dados = NULL;
		cursor = cursor->proximo;
	}

	//esvazia_listaChar(personagens_jogaveis);

	free_lista(personagens_jogaveis);

	return 0;
}
