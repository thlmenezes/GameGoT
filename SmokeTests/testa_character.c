#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include <stdlib.h>
#include <stdio.h>



int main (void)
{
	var_lista* personagens_jogaveis = LoadFromFile("personagens.txt");
	
	var_elemento* cursor = personagens_jogaveis->primeiro;

	while(cursor != NULL)
	{
		print_character(cursor->dados,NULL);
		printf("\n");
		character_free(cursor->dados);
		cursor->dados = NULL;
		cursor = cursor->proximo;
	}

	free_lista(personagens_jogaveis);

	return 0;
}
