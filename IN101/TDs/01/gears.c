#include <stdio.h>

float turns (float *gears, unsigned int nb_gears, float nb_turns) {
  if (nb_gears == 0) return 0 ;
  if (nb_gears == 1) return nb_turns ;
  return ((nb_turns * gears[0]) / gears[nb_gears - 1]) ;
}

int main () {
#define TLEN (4)
  float t[TLEN] = { 1, 4, 6, 2 } ; /* 1 tour à gauche -> 1/2 tour à droite. */
  printf ("%f\n", turns (t, TLEN, 1.0)) ;
  return 0 ;
}
