/**
 * @file   informacoes_uso_geral.c
 * @author Thales Lima Menezes
 * @date   16/10/2017
 * @brief  Arquivo que só existe para que as regras do makefile sejam cumpridas.
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include <stdio.h>
#include <stdlib.h>



//TOD
//--------------------------------------------------------------
void  limpa_buffer(void)
{
	/**
	 * Responsável pela limpeza do buffer.
	 */
	char caractere;
	while((caractere = getchar()) != '\n');

}//End limpa_buffer()


//
void  print_file (char* srcFile)
{
	/**
	 * @brief Imprime todos os caracteres presentes
	 * dentro de um arquivo.
	 * @param srcFile Nome do arquivo de onde serão
	 * extraídos os caracteres.
	 */

	FILE* arquivo;
	arquivo = fopen(srcFile,"r");

	if(arquivo == NULL)
	{
		printf("    ┌─────────────────────────────────────────────────────┐\n");
		printf("    ├──ERROR×──»    ¤    File not found   ¤    «──×ERROR──┤\n");
		printf("    └─────────────────────────────────────────────────────┘\n");
		getchar();
		return;
	}

	char encontrei_char;

	while(fscanf(arquivo, "%c", &encontrei_char) > 0)
		printf("%c", encontrei_char);

	fclose(arquivo);

}//end print_file()
