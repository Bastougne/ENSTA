#include <stdio.h>
#include <stdlib.h>



/** \brief Calcul du nombre d'occurrences par caractères dans le contenu d'un
    fichier. La table obtenue est de taille 256, avec une entrée par caractère,
    et indexée sur le code ASCII des caractères.
    \param fname : Nom du fichier à analyser.
    \return Table du nombre d'occurrence ce chaque caractère dans le fichier
    analysé ou NULL si une erreur s'est produite. La libération de cette table
    est à faire par appel à un simple free de la stdlib C. */
unsigned int* get_occs_table (char *fname)
{
  unsigned int *tbl ;
  int c ;

  FILE *in = fopen (fname, "rb") ;
  if (in == NULL) {
    printf ("Error. Unable to open file '%s'.\n", fname) ;
    return (NULL) ;
  }

  /* Allocation avec mise à zéro de chaque octet directement. Ca évite d'écrire
     soit même la boucle qui s'en charge. */
  tbl = calloc (256, sizeof (unsigned int)) ;
  if (tbl == NULL) {
    fclose (in) ;
    return (NULL) ;
  }

  c = fgetc (in) ;
  while (c != EOF) {
    tbl[c]++ ;
    c = fgetc (in) ;
  }

  fclose (in) ;
  return (tbl) ;
}
