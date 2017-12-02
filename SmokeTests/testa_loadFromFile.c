#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include <stdlib.h>
#include <stdio.h>



int main (void)
{
	var_lista* personagens_jogaveis = loadFromFile("personagens.txt");

	var_elemento* cursor = personagens_jogaveis->primeiro;

	while(cursor != NULL)
	{
		print_character(cursor->dados,NULL);
		printf("\n");
		cursor = cursor->proximo;
	}

	free_listaCharacter(personagens_jogaveis);

	return 0;
}
