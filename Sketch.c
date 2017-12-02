#include <stdlib.h>

int main (void)
{

	var_lista* data = loadFromFile("personagens.txt");

	t_node* torneio = tree_create();

	var_fila* vagas = enfileira_folhas(torneio);

	var_lista* personagensJogaveis = random_roullete(vagas->tamanho, sizeof(Character), data);

	free_listaCharacter(data);

	free_fila(vagas);

	LoadFighters(torneio, personagensJogaveis);

	Character* users_choice = character_selection(personagensJogaveis);

	var_lista* torneio_status = round_anterior(torneio);
	// lembre-se cada elemento::dados é um t_node**

	var_lista* nerfs_n_buffs = aloca_lista();

	char nomeArquivoRounds[] = "rounds.txt";
	remove(nomeArquivoRounds);
	//Recebe nome do arquivo e retorna 0 em caso de sucesso

	FILE* rounds;
	int roundNumero = 1;

	while(esta_vivo(users_choice,torneio_status))
	{
		system("reset");

		rounds = fopen(nomeArquivoRounds,"a");
		fprintf(rounds,"\r\nRound %d\r\n", roundNumero++);
		fclose(rounds);

			battle_round(users_choice, esteroids, nomeArquivoRounds, torneio);
		/*Função: battle_round
		  Brief: Busca o personagem do usuário, faz a sua luta; e
		  Gerencia as lutas dos NonPlayableCharacter's(NPC's).
		  Parâmetros:   Character* users_choice,
						var_lista* esteroids,
						char* nomeArquivoRounds,
						t_node* torneio.
		  Return: void*/
			fight_judge(fighter_one, fighter_two, nomeArquivoRounds, nerfs_n_buffs);
			/*Função: fight_judge
			  Brief: Gerencia as lutas dos NonPlayableCharacter's(NPC's);
			  selecionando quem irá selecionar o atributo, busca seu nome
			  na lista para saber suas limitações e realiza a escolha do
			  atributo. Atualiza nerfs_n_buffs e rounds.
			  Parâmetros:	Character* fighter_one,fighter_two
			  				char* rounds
			  				t_node* torneio
			  Return: void*/
				update_nerfs(TIRED, player_one, atributo, nerfs_n_buffs);
				/*Função: update_nerfs
				  Brief: Atualiza as limitações para a próxima batalha.
				  Parâmetros:   int codigo_da_acao,
				  				Character* winner_fighter,
								int atributo_usado,
								var_lista* nerfs_n_buffs.
				  Return: void*/
				update_nerfs(DEAD, player_two, atributo, nerfs_n_buffs);
				/*Função: update_nerfs
				  Brief: Exclui o lutador que morreu da lista.
				  Parâmetros:   int codigo_da_acao,
				  				Character* winner_fighter,
								int atributo_usado,
								var_lista* nerfs_n_buffs.
				  Return: void*/
				update_rounds(player_one, player_two, atributo, nomeArquivoRounds);

		torneio_status = round_anterior(torneio);
	}
	print_file(rounds);

	tree_free(torneio);

	free_lista(torneio_status);

	esvazia_lista(personagensJogaveis, false);

	free_lista(personagensJogaveis);

	free_nerfs(nerfs_n_buffs);

	return 0;
}
