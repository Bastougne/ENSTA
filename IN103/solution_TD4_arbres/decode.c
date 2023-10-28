#include <stdio.h>
#include <stdbool.h>
#include "hufftree.h"



/** \brief Décodage du fichier compressé \a in_fname selon l'arbre de Huffman
    \a tree et écriture du résultat dans le fichier \a out_fname.
    \param in_fname : Fichier source à lire et décoder.
    \param out_fname : Fichier destination dans lequel écrire le résultat du
    décodage.
    \param tree : Arbre de Huffman ayant servi à compresser le fichier initial
    et dont le résultat de compression (à décompresser) se trouve dans
    \a in_fname.
    \return Booléen disant si la décompression s'est passée sans erreur. */
bool decode (char *in_fname, char *out_fname, struct huff_node_t *tree)
{
  FILE *in, *out ;
  int c ;
  struct huff_node_t *current_node ;
  bool error = false ;

  in = fopen (in_fname, "rb") ;
  if (in == NULL) {
    printf ("Error. Unable to open input file '%s'.\n", in_fname) ;
    return (false) ;
  }

  out = fopen (out_fname, "wb") ;
  if (out == NULL) {
    printf ("Error. Unable to open output file '%s'.\n", out_fname) ;
    fclose (in) ;
    return (false) ;
  }

  /* Lecture "bit par bit", donc dans notre cas simplifié, caractère par
     caractère du fichier d'entrée et descente dans l'arbre de Huffman de
     la racine jusqu'à trouver une feuille. */
  c = fgetc (in) ;
  current_node = tree ;
  while ((! error) && (c != EOF)) {
    switch (c) {
    case '0':
      /* Descente à gauche. */
      current_node = current_node->left ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL left child.\n") ;
        error = true ;
      }
      /* Si le noeud est une feuille, il faut écrire le caractère correspondant
         et repartir du haut de l'arbre. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '0'. */

    case '1':
      /* Descente à droite. */
      current_node = current_node->right ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL right child.\n") ;
        error = true ;
      }
      /* Même chose que pour la descente à gauche. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '1'. */

    default:
      /* Ne devrait jamais se produire puisque l'on n'a écrit que des
         caractères '0' et '1'. */
      printf ("Error. Unexpected bit-like character in input stream.\n") ;
      error = true ;
      break ;
    }

    /* Lecture du prochain "bit" (caractère). */
    c = fgetc (in) ;
  }   /* Fin de while (c != EOF). */

  /* Normalement, il ne devrait pas rester de "bits" en suspend, donc à la
     fin de la lecture du flot de biti on devrait se trouver de nouveau à la
     racine de l'arbre. Ca sentirait le bug ou le fichier corrompu. */
  if (current_node != tree) printf ("Warning. Spurious bit(s) remaining.\n") ;
  if (error) printf ("Error encountered.\n") ;

  fclose (in) ;
  fclose (out) ;
  return (true) ;
}
