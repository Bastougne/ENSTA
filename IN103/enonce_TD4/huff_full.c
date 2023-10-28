#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hufftree.h"
#include "code.h"
#include "encode.h"
#include "decode.h"



/** \brief Programme principal qui lit un fichier (\a argv[1]), l'encode et
    stocke le résultat dans un autre fichier (\a argv[2]), puis décode ce
    dernier en stockant le résultat du décodage dans un 3ème fichier
    (\a argv[3]). */
int main (int argc, char *argv[])
{
  int i ;
  struct huff_node_t *tree ;
  char **codes ;

  if (argc != 4) {
    printf
      ("Wrong argument. Expected <input file name> <ouput file name> \
<ouput file name>.\n") ;
    return (-1) ;
  }

  tree = build_tree (argv[1]) ;
  if (tree == NULL) {
    printf ("Error. Could not build tree.\n") ;
    return (-1) ;
  }

  codes = get_codes (tree) ;
  if (codes == NULL) {
    printf ("Error. Codes table not available.\n") ;
    free_tree (tree) ;
    return (-1) ;
  }

  /* Encodage: argv[1] -> argv[2]. */
  if (! encode (argv[1], argv[2], codes)) printf ("Encoding failed.\n") ;


  /* Décodage: argv[2] -> argv[3]. */
  if (! decode (argv[2], argv[3], tree)) printf ("Decoding failed.\n") ;

  /* Libération finale de la mémoire utilisée. */
  for (i = 0; i < 256; i++) {
    if (codes[i] != NULL) free (codes[i]) ;
  }
  free (codes) ;
  free_tree (tree) ;
  return (0) ;
}
