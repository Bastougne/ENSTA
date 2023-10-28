#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool same_sum (int n, int c) {
  /* Impossible d'avoir une somme négative de chiffres positifs. */
  if (n < 0) return (false) ;
  /* Ne pas diviser par 0. La somme est correcte seulement si elle vaut 0. */
  if (c == 0) return (n == 0) ;
  return (n % c == 0) ;  /* Implicitly "else". */
}

int main () {
  int n, c ;

  printf ("Nombre et chiffre ? : ") ;
  scanf ("%d %d", &n, &c) ;
  printf ("%d\n", same_sum (n, c)) ;
  return 0 ;
}
