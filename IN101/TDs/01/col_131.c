#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool col (float xa, float ya, float xb, float yb, float xc, float yc) {
  float left = (xb - xa) * (yc - yb) ;
  float right = (xc - xb) * (yb - ya) ;
  float delta = left - right ;
  return (delta == 0) ;
}

int main () {
  float x = 13.1 ;
  float y = sqrt (x) ;
  printf ("%d\n", col (1, 1, y * y, x, 5, 5)) ;
  return 0 ;
}
