#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nth (char *str, unsigned int index) {
  if (index >= strlen (str))
    printf ("Erreur. Indice hors limites.\n") ;
  else printf ("%c\n", str[index]) ;
}

int main () {
  char str[64] ;
  int pos ;

  printf ("Chaîne et position ? : ") ;
  scanf ("%s %d", str, &pos) ;
  nth (str, pos) ;
  return 0 ;
}
