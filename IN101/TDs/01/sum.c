#include <stdio.h>
#include <stdlib.h>

int sum (int x, int y) {
  int accu = 0 ;
  int start = x ;
  int stop = y ;
  int i ;

  /* Vérification de quel argument est le plus petit et on commence à partir
     de lui. */
  if (y < x) {
    start = y ;
    stop = x ;
  }

  for (i = start; i <= stop; i++) {
    if ((i % 5 == 0) && (i % 2 != 0)) accu = accu + i ;
  }
  return accu ;
}

int main () {
  int x, y ;

  printf ("x y ? : ") ;
  scanf ("%d %d", &x, &y) ;
  printf ("%d\n", sum (x, y)) ;
  return 0 ;
}
