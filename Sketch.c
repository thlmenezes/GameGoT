#include <stdlib.h>

int main (void)
{

	var_lista* data = LoadFromFile("personagens.txt");

	var_lista* personagensJogaveis = random_roullete(16, sizeof(Character), data);

	free_listaCharacter(data);

	t_node* torneio = tree_create();

	LoadFighters(torneio, personagensJogaveis);

	Character* users_choice = character_selection(personagensJogaveis);
	/*Função: character_selection
	  Brief: Imprime na tela todos os PlayableCharacter's(PC's)
	  ocultando seus nomes e suas casa, mostrando ao
	  usuário somente 1 de seus 4 status, escolhido
	  aleatoriamente. Retorna um Character* para o
	  personagem escolhido pelo usuário.
	  Parâmetros: var_lista* playableCharacters
	  Return: Character* users_choice*/
	var_lista* torneio_status = round_anterior(torneio);
	/*Função: round_anterior
	  Brief: Percorre a arvore, pós-ordem/largura,ca-
	  so chegue numa folha, ou em uma "pseudo-folha",
	  insere na lista.
	  Parâmetros: t_node* torneio
	  Return: var_lista* round_anterior*/
	var_lista* nerfs_n_buffs = aloca_lista();
	//TODO: Funções para elemento->dados do tipo nerfs_n_buffs

	char nomeArquivoRounds[] = "rounds.txt";
	remove(nomeArquivoRounds);
	//Recebe nome do arquivo e retorna 0 em caso de sucesso

	FILE* rounds;
	int roundNumero = 1;

	while(esta_vivo(users_choice,torneio_status))
	{
	/*Função: esta_vivo
	  Brief: Busca o personagem do usuário na lista do
	  status atual do torneio, caso morto é enviado o
	  sinal false.
	  Parâmetros:   Character* users_choice,
					var_lista* torneio_status,
					t_node* torneio.
	  Return: bool esta_vivo*/
		system("reset");

		rounds = fopen(nomeArquivoRounds,"a");
		fprintf(rounds,"Round %d\r\n", roundNumero++);
		fclose(rounds);

		battle_round(users_choice, rounds, nerfs_n_buffs, torneio);
		/*Função: battle_round
		  Brief: Busca o personagem do usuário, faz a sua luta; e
		  Gerencia as lutas dos NonPlayableCharacter's(NPC's).
		  Parâmetros:   Character* users_choice,
						char* rounds,
						var_lista* nerfs_n_buffs,
						t_node* torneio.
		  Return: void*/
			fight_judge(fighter_one, fighter_two, rounds, nerfs_n_buffs);
			/*Função: fight_judge
			  Brief: Gerencia as lutas dos NonPlayableCharacter's(NPC's);
			  selecionando quem irá selecionar o atributo, busca seu nome
			  na lista para saber suas limitações e realiza a escolha do
			  atributo. Atualiza nerfs_n_buffs e rounds.
			  TODO:Preciso de algum lugar que armazene os nerfs/buffs
			  IDEA:Pode ser criado uma nova estrutura formada de Character* personagem e int nerfs
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
				update_rounds(player_one, player_two, atributo, rounds);

		torneio_status = round_anterior(torneio);
	}
	//TODO: imprimir o status de todo o torneio;
	print_file(rounds);

	tree_free(torneio);

	free_lista(torneio_status);

	esvazia_lista(personagensJogaveis, false);

	free_lista(personagensJogaveis);

	free_nerfs(nerfs_n_buffs);

	return 0;
}
