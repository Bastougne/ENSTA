#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "load_dic.h"


bool find_word_naive (char **words, char *word, unsigned int num_words)
{
  unsigned int i = 0 ;
  bool found = false ;

  while ((i < num_words) && (! found)) {
    if (strcmp (word, words[i]) == 0) found = true ;
    else i++ ;
  }

  return (found) ;
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

  words = load_file(argv[1], &num_words) ;
  if (words == NULL) {
    printf ("Error: unable to open dico file '%s'.\n", argv[1]) ;
    return (1) ;
  }

  printf ("Number of words: %d.\n", num_words) ;
  while (gets (buffer)) {
    if (find_word_naive (words, buffer, num_words)) printf ("Found :)\n") ;
    else printf ("Not found :(\n") ;
  }

  return (0) ;
}
