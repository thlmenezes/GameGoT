/**
 * @file   informacoes_uso_geral.c
 * @author Thales Lima Menezes
 * @date   16/10/2017
 * @brief  Arquivo que contém a implementação de funções de uso geral.
 */
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include <stdio.h>
#include <stdlib.h>



//TOD
//--------------------------------------------------------------
void  limpa_buffer (void)
{

	/**
	 * Responsável pela limpeza do buffer.
	 */

	char caractere;
	while((caractere = getchar()) != '\n');

}//End limpa_buffer()


//--------------------------------------------------------------
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
		print_error(arquivo);
		return;
	}

	char encontrei_char;

	while(fscanf(arquivo, "%c", &encontrei_char) > 0)
		printf("%c", encontrei_char);

	fclose(arquivo);

}//End print_file()


//--------------------------------------------------------------
void  print_error (FILE* screen)
{

	/**
	 * @brief Gerencia a impressão dos erros relacionados a
	 * arquivos.
	 */

	if(screen == NULL)
	{
		printf("    ┌─────────────────────────────────────────────────────┐\n");
		printf("    ├──ERROR×──»    ¤    File not found   ¤    «──×ERROR──┤\n");
		printf("    └─────────────────────────────────────────────────────┘\n");
		getchar();
		return;
	}

}//End print_error()


//--------------------------------------------------------------
void  system_comands(int command)
{

	/**
	 * @brief Função visando viabilizar portabilidade com outras
	 * plataformas, além do Linux.
	 */

	switch(command)
	{
		case RESET:
			#ifdef WIN32
				system("cls");
			#else
				system("reset");
			#endif
				break;
		default:
				break;
	}

}//End system_commands()
