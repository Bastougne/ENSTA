#include <stdio.h>
#include <stdlib.h>

/* Factorise pour éviter de calculer les même puissances -> 7 opérations. */
float poly (float x) {
  return x * (x * (x * (-3 * x + 5)) + 2) + 5 ;
}

int main () {
  float x ;
  printf ("Point d'évaluation ? : ") ;
  scanf ("%f", &x) ;
  printf ("poly (%f) = %f\n", x, poly (x)) ;
  return 0 ;
}
