#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Un booléen optionnel. */
enum bool_option {
  BO_False, /* Booléen faux. */
  BO_True,  /* Booléen vrai. */
  BO_Error  /* Pas un booléen, mais une erreur à la place. */
};

enum bool_option same_sum (int n, unsigned int c) {
  if (c > 9) return BO_Error ;
  /* Impossible d'avoir une somme négative de chiffres positifs. */
  if (n < 0) return (BO_False) ;
  /* Ne pas diviser par 0. La somme est correcte seulement si elle vaut 0. */
  if (c == 0) return ((n == 0) ? BO_True : BO_False) ;
  return ((n % c == 0) ? BO_True : BO_False) ;  /* Implicitement "else". */
}

int main () {
  int n, c ;

  printf ("Nombre et chiffre ? : ") ;
  scanf ("%d %d", &n, &c) ;

  switch (same_sum (n, c)) {
  case BO_True : printf ("Vrai\n") ; break ;
  case BO_False : printf ("Faux\n") ; break ;
  case BO_Error : printf ("Erreur. Entrée invalide.\n") ; break ;
  }
  return 0 ;
}
