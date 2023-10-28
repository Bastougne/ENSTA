#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "load_dic.h"


bool find_word_dicho (char **words, char *word, int left, int right)
{
  int mid ;
  int cmp ;

#ifdef DEBUG
  printf ("Search between %d %d\n", left, right) ;
#endif
  if (left > right) return (false) ;
  mid = (left + right) / 2 ;

  /* Is word > words[mid] ? */
  cmp = strcmp (word, words[mid]) ;
#ifdef DEBUG
  printf ("Index: %d %s ? %s Cmp: %d\n", mid, word, words[mid], cmp) ;
#endif
  if (cmp == 0) return (true) ;     /* word == words[mid] */

  /* word < words[mid] ? */
  if (cmp < 0) return (find_word_dicho (words, word, left, mid - 1)) ;

  /* Obviously word > words[mid]. */
  return (find_word_dicho (words, word, mid + 1, right)) ;
}



int main (int argc, char *argv[])
{
  char buffer[256] ;
  char **words ;
  unsigned int num_words = 0 ;

  if (argc != 2) {
    printf ("Error: wrong number of arguments. Expected <filename>.\n") ;
    return (1) ;
  }

  words = load_file (argv[1], &num_words) ;
  if (words == NULL) {
    printf ("Error: unable to open dico file '%s'.\n", argv[1]) ;
    return (1) ;
  }

  printf ("Number of words: %d.\n", num_words) ;

  while (gets (buffer)) {
    if (find_word_dicho (words, buffer, 0, num_words)) printf ("Found :)\n") ;
    else printf ("Not found :(\n") ;
  }

  return (0) ;
}
