
#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include "../headers/character.h"
#include "../headers/arvore.h"
#include "../headers/battle.h"
#include "../headers/fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



//TOD:
int main (void)
{
	var_lista* data = loadFromFile("personagens.txt");

	t_node* torneio = tree_create();

	var_fila* vagas = enfileira_folhas(torneio);

	var_lista* personagensJogaveis = random_roullete(vagas->tamanho, sizeof(Character), data);

	free_listaCharacter(data);

	free_fila(vagas);

	char nomeArquivoRounds[] = "rounds.txt";
	remove(nomeArquivoRounds);

	FILE* rounds;
	int roundNumero = 1;
	rounds = fopen(nomeArquivoRounds,"a");

	fprintf(rounds,"\r\nRound %d:\r\n", roundNumero++);

	fclose(rounds);

	time_t t;
	srand((unsigned) time(&t));

	var_elemento *cursor = personagensJogaveis->primeiro;
	Character *personagem_hum;
	Character *personagem_dois;

	while( cursor != NULL )
	{
		personagem_hum = (Character*) cursor->dados;
		personagem_dois = (Character*) cursor->proximo->dados;
		update_rounds(  personagem_hum, personagem_dois, rand() % 4 + 1 , nomeArquivoRounds);
		cursor = cursor->proximo->proximo;
	}

	print_file(nomeArquivoRounds);

	free_listaCharacter(personagensJogaveis);

	tree_free(torneio);

	return 0;
}
