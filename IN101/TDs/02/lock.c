#include <stdio.h>
#include <stdlib.h>

int min (int a, int b) { return a < b ? a : b ; }


int unlock (int current, int code) {
  int nb_turns = 0 ;

  while (current != 0 || code != 0) {
    int curr_d = current % 10 ;
    int code_d = code % 10 ;
    int diff = abs (curr_d - code_d) ;
    nb_turns += min (diff, 10 - diff) ;
    current /= 10 ;
    code /= 10 ;
  }

  return nb_turns ;
}


int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf ("Error. Usage: <unlock code> <current state>.\n") ;
    return 1 ;
  }

  int current = atoi (argv[2]) ;
  int code = atoi (argv[1]) ;
  printf ("Nb turns: %d\n", unlock (current, code)) ;
  return 0 ;
}
