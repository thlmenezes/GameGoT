#include "../headers/fila.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	var_fila* fila = aloca_fila();

	int numero = 4;

	print_fila(fila, INT);

	entrar_fila(&numero, sizeof(int), fila);

	numero = 7;

	entrar_fila(&numero, sizeof(int), fila);

	print_fila(fila, INT);

	int* ponteiro_numero = (int*) sair_fila(fila);

	printf("%d\n", *ponteiro_numero);

	free_fila(fila);

	free(ponteiro_numero);

	return 0;
}
