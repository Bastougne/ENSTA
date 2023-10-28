#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool col (float xa, float ya, float xb, float yb, float xc, float yc) {
  return ((xb - xa) / (xc - xb) == (yb - ya) / (yc - yb)) ;
}

int main () {
  float xa, ya, xb, yb, xc, yc ;

  printf ("Coordonnées x y de A B C ? : ") ;
  scanf ("%f %f %f %f %f %f", &xa, &ya, &xb, &yb, &xc, &yc) ;
  if (col (xa, ya, xb, yb, xc, yc)) printf ("Vrai\n") ;
  else printf ("Faux\n") ;
  return 0 ;
}
