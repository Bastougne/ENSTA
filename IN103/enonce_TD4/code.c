#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hufftree.h"



/** \brief Fonction de parcours récursif de l'arbre de Huffman permettant
    de remplir la table des codes. Elle prend en argument un buffer dans
    lequel elle va stocker les différents "bits" de codage rencontrés au cours
    de la descente et recopiera, une fois arrivée à un feuille, la chaîne de
    ces "bits" dans l'entrée de la table correspondant au caractère de la
    feuille.
    \param tree : Noeud courant exploré de l'arbre.
    \param accu : Buffer pour stocker au fur et à mesure de la descente dans
    l'arbre les caractères '0' et '1' des bits rencontrés.
    \param accu_len : Nombre actuel de caractères dans l'accu.
    \param codes : Table des codes à remplir.
    \return Booléen disant si la mémorisation des code s'est passée
    correctement.
    \note Cette fonction est locale au fichier courant et n'est pas exportée.
    Elle sert uniquement de "helper" à la fonction \a get_codes. */
static bool tree_walk (struct huff_node_t *tree, char *accu, int accu_len,
                       char **codes)
{
  if (tree != NULL) {
    if (tree->left == NULL) {
      /* Noeud terminal. Notons que par invariant le fils droit doit être
         également à NULL. */
      codes[tree->letter] = malloc ((accu_len + 1) * sizeof (char)) ;
      if (codes[tree->letter] == NULL) return (false) ;
      strncpy (codes[tree->letter], accu, accu_len) ;
      codes[tree->letter][accu_len] = '\0' ;
      return (true) ;
    }
    else {
      /* Noeud non terminal, on récurse à gauche et à droite en augmentant
         l'accumulateur. */
      accu[accu_len] = '0' ;
      if (! tree_walk (tree->left, accu, accu_len + 1, codes)) return (false) ;
      accu[accu_len] = '1' ;
      return (tree_walk (tree->right, accu, accu_len + 1, codes)) ;
    }
  }
  return (true) ;
}



/** \brief Récupération de la table des codes associés à l'arbre de Huffman
    passé en argument.
    \param tree : Pointeur sur la racine de l'arbre de Huffman.
    \return Tableau de 256 chaînes de caractères représentant le code associé
    à chaque caractère (indexation par le code du caractère). Chaque chaîne
    est composée de caractères '0' et '1' formant une représentation textuelle
    du code binaire associé au caractère encodé. */
char** get_codes (struct huff_node_t *tree)
{
  int i ;
  /* Le cas le plus dégénéré le code le plus long est égal au nombre de
     symboles (ici 256) - 1. Il faut 1 octet de plus pour clore la chaîne
     obtenue. Donc une longueur de chaîne maximale de 256 caractères. */
  char tmp_buffer[256] ;

  char **codes = malloc (257 * sizeof (char*)) ;
  if (codes == NULL) return (NULL) ;

  /* Initialisation des codes à "aucune chaîne". */
  for (i = 0; i < 256; i++) codes[i] = NULL ;

  /* Parcours récursif de l'arbre pour remplir la table. */
  if (! tree_walk (tree, tmp_buffer, 0, codes))
    printf ("Error while building codes table. Table may be incomplete.\n") ;

  return (codes) ;
}
