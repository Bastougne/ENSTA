#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hufftree.h"

int* nb_occurence(char *fname)
{
	/* Open the file. */
	FILE *file = fopen (fname, "rb") ;
	if (file == NULL) 
	{
    	printf ("Error. Unable to open file.\n") ;
    	return NULL;
  	}

  	// création d'une table qui contient le nombre d'occurrence des charactères, les char sont aussi des entiers de 0 à 255
  	int* T = calloc(256, sizeof(int)); //pareil que malloc(256*sizeof(int)) mais initialise tout à 0
  	//unsigned char buffer[256];
  	do
  	{
  		//fscanf(file,"%s",buffer);
  		// fgetc renvoie le code du caractère lu donc un entier de 0 à 255
  		T[fgetc(file)]++;

  	} while (!feof(file));

  	fclose(file);
	return T;
}

struct huff_node_t** min (struct huff_node_t** feuille){
	
	int i = 0 ;
	int min = -1;
	struct huff_node_t** p = malloc(sizeof(struct huff_node_t*));
	p = NULL;

	while(i<256)
	{	
		if(feuille[i] != NULL)
		{
			if(feuille[i]->data < min || min == -1)
			{
				min = feuille[i]->data ;
				p = feuille+i;
			} 
		}
		i++;
	}
	return p;
}



struct huff_node_t* build_tree(char* fname) {
	int* T = nb_occurence(fname);

	struct huff_node_t** feuille = malloc(256*sizeof(struct huff_node_t*));
	for (int i = 0; i < 256; ++i)
	{
			feuille[i] = malloc(sizeof(struct huff_node_t));
  			feuille[i]->data  = T[i];
 			feuille[i]->letter = (unsigned char) i;
 			feuille[i]->left = NULL ; 
  			feuille[i]->right = NULL ;
	}
	struct huff_node_t** case_right;
	struct huff_node_t** case_left;


	struct huff_node_t* arbre = malloc(sizeof(struct huff_node_t)); // malloc retourne un pointeur vers la mémoire
	case_right = min(feuille);
	arbre->right = *case_right;
	arbre->data = arbre->right->data;
	*case_right = NULL;
	case_left = min(feuille);

	while(case_left!=NULL){
		//creer le premier arbre
	
	arbre->left =  *case_left;
	arbre->data = arbre->data + arbre->left->data; 
	*case_left = arbre;
	arbre = malloc(sizeof(struct huff_node_t)); // malloc retourne un pointeur vers la mémoire
	case_right = min(feuille);
	arbre->right = *case_right;
	arbre->data = arbre->right->data;
	*case_right = NULL;
	case_left = min(feuille);
	}
	//le sommet c'est arbre->right

	struct huff_node_t* sommet = malloc(sizeof(struct huff_node_t));
	sommet = arbre->right ;
	free(arbre);
	return sommet;

}

bool encode(char* name_src, char* name_dest, char** codes)
{
	/* Open the file. */
	FILE *file = fopen (name_src, "r") ;
	FILE *file1 = fopen (name_dest, "w") ;
	if (file == NULL) 
	{
    	printf ("Error. Unable to open file source.\n") ;
    	return false;
  	}

  	if (file1 == NULL) 
	{
    	printf ("Error. Unable to open file destination.\n") ;
    	return false;
  	}
	int indice = fgetc(file);
  	while (!feof(file))
  	{
  		fprintf(file1, "%s", codes[indice]);
  		indice = fgetc(file);

  	}

  	fclose(file);
  	fclose(file1);
  	return true;
}











