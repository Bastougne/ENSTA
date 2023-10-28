#include <stdio.h>
#include <stdlib.h>


/* Compute and print the unit fractions representing the Egyptian fraction. */
void work (long int num, long int denom) {
  if (denom % num == 0) {
    printf ("1 / %ld\n", (denom / num)) ;
    return ;
  }
  long int n = (denom / num) + 1 ;
  printf ("1 / %ld\n", n) ;
  long int new_num = num * n - denom ;
  long int new_denom = denom * n ;
  work (new_num, new_denom) ;
}


int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf ("Error. Wrong number of arguments.\n") ;
    return 1 ;
  }
  long int num = atol (argv[1]) ;
  long int denom = atol (argv[2]) ;
  if (num > denom) printf ("Error : input fraction > 1.\n") ;
  else work (num, denom) ;
  return 0 ;
}
