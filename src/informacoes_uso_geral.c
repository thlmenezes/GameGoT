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

	char caractere;
	while((caractere = getchar()) != '\n');

}//End limpa_buffer()
