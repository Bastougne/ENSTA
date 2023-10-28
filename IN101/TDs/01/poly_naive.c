#include <stdio.h>
#include <stdlib.h>

/* 5x^3 + 2x - 3x^4 + 5 -> 11 opérations. */
float poly (float x) {
  return 5 * x * x * x + 2 * x - 3 * x * x * x * x + 5 ;
}

int main () {
  float x ;
  printf ("Point d'évaluation ? : ") ;
  scanf ("%f", &x) ;
  printf ("poly (%f) = %f\n", x, poly (x)) ;
  return 0 ;
}
