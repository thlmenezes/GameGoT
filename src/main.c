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
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include "../headers/arvore.h"
#include "../headers/battle.h"
#include "../headers/fila.h"
#include "../headers/menu.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//TODO: atualizar funções de liberação para retornar ponteiro NULL
int main (void)
{
	main_menu("src_files/main_menu.txt");
	
	return 0;
}
