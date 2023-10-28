#include <stdio.h>

int main (int argc, char *argv[]) {
  if (argc == 1) return 0 ;
  else {
    int r = main (argc - 1, argv) ;
    printf ("%s\n", argv[argc - 1]) ;
    return r ;
  }
}
