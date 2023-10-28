#include <stdio.h>
#include <stdlib.h>

void print_spaces (unsigned int number) {
  for (int i = 0; i < number; i++) printf (" ") ;
}


void print_tree (unsigned int height) {
  for (int line = 0; line < height; line++) {
    /* Left shift computes a power of 2. Saves a power function. */
    int spacing = (1 << (height - line)) - 1 ;
    int indent = spacing / 2 ;
    int nb_nodes = 1 << line ;
    /* Print spaces starting the line. */
    print_spaces (indent) ;
    /* Print the first star apart to avoid trailing white spaces. */
    printf ("*") ;
    for (int i = 1; i < nb_nodes; i++) {
      print_spaces (spacing) ;
      printf ("*") ;
    }
    /* 2 ends of line. */
    printf ("\n\n") ;
  }
}


int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf ("Error. Wrong number of arguments.\n") ;
    return 1 ;
  }

  print_tree (atoi (argv[1])) ;
  return 0 ;
}
