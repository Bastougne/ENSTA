#include <stdio.h>
#include <stdlib.h>

#include "hufftree.h"

void free_tree(struct huff_node_t* feuille)
{
	 if (feuille != NULL) {
	 	free_tree(feuille->left);
	 	free_tree(feuille->right);
	 	free(feuille);
	 }
}

