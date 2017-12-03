#include "../headers/character.h"
#include "../headers/arvore.h"

int main(void)
{
	t_node* node = node_create();
	tree_free(node);
	tree_free(tree_create());
	return 0;
}
