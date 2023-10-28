#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int abs (int i) {
  if (i < 0) return (-i) ;
  return i ;
}


bool move_knight (int x, int y, int x_prim, int y_prim) {
  if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (x_prim < 0) ||
      (y_prim < 0) || (x_prim > 7) || (y_prim > 7) ||
      ((x == x_prim) && (y == y_prim)))
    return false ;
  return (((abs (x - x_prim) == 1) && (abs (y - y_prim) == 2))
          ||
          ((abs (x - x_prim) == 2) && (abs (y - y_prim) == 1))) ;
}


int main (int argc, char *argv[]) {
  if (argc != 5) {
    printf ("Error. Wrong number of arguments.\n") ;
    return 1 ;
  }

  if (move_knight
      (atoi (argv[1]), atoi (argv[2]), atoi (argv[3]), atoi (argv[4])))
    printf ("Legal\n") ;
  else printf ("Illegal\n") ;
  return 1 ;
}
