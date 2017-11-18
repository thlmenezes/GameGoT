#include <stdlib.h>

int main (void)
{
	FILE *personagens;
	personagens = fopen("personagens.txt","r");
	var_lista* Data = LoadFromFile(personagens);
	/*Função: LoadFromFile
	  Brief: Retorna uma lista com todas
	  as estruturas Character presentes no
	  arquivo segundo o formato correto
	  (name, house, agility, strenght,
	  intelligence, health) montadas e
	  prontas para acesso.
	  Parâmetros FILE *fichas_de_personagens
	  Return var_lista*personagens*/
	fclose(personagens);
	var_lista* playableCharacters = random_roullete(16, Data);
	/*Função: random_roullete
	  Brief: Seleciona um numero X, 1ºparam,
	  de elementos de uma lista Y, 2ºparam,
	  entregando os resultados em uma lista.
	  Seleção é randomica.
	  Parâmetros: int X, var_lista* Y
	  Return: var_lista* results*/
	free_lista(Data);

	t_node* torneio = tree_create();

	LoadFighters(torneio,playableCharacters);
	/*Função: LoadFighters
	  Brief: Carrega nas folhas da árvore, 1ºparam
	  os participantes do torneio, 2ºparam.
	  Parâmetros: t_node* arvore, var_lista* fighters
	  Return: void*/
	Character* users_choice = character_selection(playableCharacters);
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
	var_lista* rounds = aloca_lista();
	//TODO: Funções para elemento->dados do tipo rounds
	//IDEA: cada elemento->dados de rounds armazena
	//IDEA: informações sobre todas as lutas do round anterior
	/*
	rounds->round->string luta
	*/
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
		battle_round(users_choice, rounds, nerfs_n_buffs, torneio);
		/*Função: battle_round
		  Brief: Busca o personagem do usuário, faz a sua luta; e
		  Gerencia as lutas dos NonPlayableCharacter's(NPC's).
		  Parâmetros:   Character* users_choice,
						var_lista* rounds,
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
			  Parâmetros: Character* users_choice,t_node* torneio
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
				/*Função: update_rounds
				  Brief: Registra a luta numa string do padrão
				  vencedor(inteiro nomeatributo) vs perdedor(inteiro nomeatributo).
				  Parâmetros:   Character* fighter1,
								Character* fighter2,
								int atributo_usado,
								var_lista* rounds.
				  Return: void*/
		torneio_status = round_anterior(torneio);
	}
	//TODO: imprimir o status de todo o torneio;
	print_rounds(rounds);

	tree_free(torneio);

	free_lista(torneio_status);

	deletar todos os elementos e liberar playableCharacters

	free_nerfs(nerfs_n_buffs);

	free_rounds(rounds);

	return 0;
}
