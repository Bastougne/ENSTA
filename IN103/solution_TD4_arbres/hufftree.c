#include <stdio.h>
#include <stdlib.h>
#include "freq.h"
#include "hufftree.h"


/** \brief Lib�ration de la m�moire utiliser par un arbre. La fonction proc�de
    en lib�rant r�cursivement les fils gauche et droite avant de lib�rer le
    noeud courant.
    \param tree : Pointeur sur l'arbre � lib�rer. */
void free_tree (struct huff_node_t *tree)
{
  if (tree != NULL) {
    free_tree (tree->left) ;
    free_tree (tree->right) ;
    free (tree) ;
  }
}



/** \brief Construction de l'arbre de Huffman associ� au fichier dont le nom
    est pass� en argument.
    \param fname : Nom du fichier � analyser et pour lequel cr�er l'arbre.
    \return Le pointeur sur l'arbre cr�� ou NULL si une erreur s'est produite
    durant le traitement. L'arbre obtenu devra �tre lib�r� ult�rieurement en
    fin d'utilit�. */
struct huff_node_t* build_tree (char *fname)
{
  struct huff_node_t *trees[256] ;
  struct huff_node_t *min_tree1, *min_tree2 ;
  int i, n_trees ;
  unsigned int min ;

  /* On commence par r�cup�rer la table des occurrences pour ce fichier. */
  unsigned int *occs_tbl = get_occs_table (fname) ;
  if (occs_tbl == NULL) return (NULL) ;

  /* Cr�ation de toutes les feuilles. On les stocke dans un tableau. */
  for (i = 0; i < 256; i++) {
    trees[i] = malloc (sizeof (struct huff_node_t)) ;
    if (trees[i] == NULL) {
      /* Si plus de m�moire pour les feuilles, on lib�re celles d�j� allou�es
         et on lib�re la table d'occurrences. */
      for (i--;i >= 0; i--) free (trees[i]) ;
      free (occs_tbl) ;
      return (NULL) ;
    }   /* Fin de if (trees[i] == NULL). */
    trees[i]->letter = (char) i ;
    trees[i]->left = NULL ;
    trees[i]->right = NULL ;
    trees[i]->nb_occs = occs_tbl[i] ;
  }     /* Fin de for (i = 0; i < 256; i++). */

  /* Maintenant d�but le processus it�ratif d'aggr�gation des 2 sous arbres
     d'occurrences minimales. */
  n_trees = 256 ;
  /* On s'arr�tera lorsqu'il ne restera plus qu'un seul sous-arbre. */
  while (n_trees > 1) {
    /* On extrait un premier "min". */
    min = 0 ;
    for (i = 1; i < n_trees; i++) {
      if (trees[i]->nb_occs < trees[min]->nb_occs) min = i ;
    }
    min_tree1 = trees[min] ;
    /* On bouche le trou que va laisser l'aggr�gation de ce "min" avec le
       prochain. En effet, on prend 2 arbres pour n'en faire qu'un seul. Il va
       donc en disara�tre un. */
    trees[min] = trees[n_trees - 1] ;
    /* On a (enfin, va bient�t effectivement avoir) un arbre de moins. */
    n_trees-- ;

    /* On extrait un second "min". */
    min = 0 ;
    for (i = 1; i < n_trees; i++) {
      if (trees[i]->nb_occs < trees[min]->nb_occs) min = i ;
    }
    min_tree2 = trees[min] ;

    /* On fusionne les 2 "mins" et on replace l'arbre r�sultat dans le
       tableau. On replace le nouveau sous-arbre directement � la place de
       min. */
    trees[min] = malloc (sizeof (struct huff_node_t)) ;
    if (trees[min] == NULL) {
      /* Plus de m�moire: il faudrait lib�re ce qu'il reste d'arbres. Pour
         ne pas complexifier l'exercice, on fait l'impasse :$ */
      return (NULL) ;
    }
    /* Le champ lettre n'a pas de signification: on l'ignore. */
    trees[min]->left = min_tree1 ;
    trees[min]->right = min_tree2 ;
    trees[min]->nb_occs = min_tree1->nb_occs + min_tree2->nb_occs ;
  }   /* Fin de while (n_trees > 1). */

  /* Il ne nous reste plus qu'un noeud, c'est la racine de l'arbre. */
  return (trees[0]) ;
}
