#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON (0.00001)

bool col (float xa, float ya, float xb, float yb, float xc, float yc) {
  float left = (xb - xa) * (yc - yb) ;
  float right = (xc - xb) * (yb - ya) ;
  float delta = left - right ;
  return (-EPSILON < delta && delta < EPSILON) ;
}

int main () {
  printf ("%d\n", col (1, 1, sqrt (11.5) * sqrt (11.5), 11.5, 5, 5)) ;
  return 0 ;
}
