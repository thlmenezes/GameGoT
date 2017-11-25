#include "../headers/informacoes_uso_geral.h"
#include "../headers/lista_dupla.h"
#include <stdlib.h>
#include <stdio.h>

int main (void){
	var_lista* lista = aloca_lista();

	var_elemento* elemento = aloca_elemento();

	elemento->dados = (void*) malloc(sizeof(int));

	*(int*) elemento->dados = 3;

	insere_lista(INSERE_FINAL, elemento->dados, sizeof(int), lista, INSERE_DADO_HEAP);
	// Insere informações ou elementos na lista por cópia
	*(int*) elemento->dados = 6;

	insere_lista(INSERE_FINAL, elemento, sizeof(var_elemento), lista, INSERE_VAR_ELEMENTO);
	// Insere informações ou elementos na lista por cópia

	free(elemento);
	/*Liberamos o var_elemento alocado nesse escopo,
	NÃO liberar memórias entrelaçadas a ele*/

	deleta_ultimo(lista);
	//Esperado que o 6 seja deletado

	print_lista(lista,INT);

	free_lista(lista);

	return 0;
}
