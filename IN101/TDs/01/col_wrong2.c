#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool col (float xa, float ya, float xb, float yb, float xc, float yc) {
  float left = (xb - xa) * (yc - yb) ;
  float right = (xc - xb) * (yb - ya) ;
  float delta = left - right ;
  return (delta == 0) ;
}

int main () {
  float xa, ya, xb, yb, xc, yc ;

  printf ("Coordonnées x y de A B C ? : ") ;
  scanf ("%f %f %f %f %f %f", &xa, &ya, &xb, &yb, &xc, &yc) ;

  if (col (xa, ya, xb, yb, xc, yc)) printf ("Vrai\n") ;
  else printf ("Faux\n") ;
  return 0 ;
}
