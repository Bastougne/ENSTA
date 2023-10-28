#include <stdio.h>

void count (int *t, unsigned int tlen, int n) {

}


int main () {
#define TLEN (4)
  int t1[TLEN] = { 1, 2, 3, 4 } ;
  int t2[TLEN] = { 0, 0, 0, 0 } ;
  int t3[TLEN] = { -1, -1, -1, -1 } ;

  count (t1, TLEN, 1) ;
  count (t1, TLEN, 0) ;
  count (t1, TLEN, -1) ;
  count (t2, TLEN, 0) ;
  count (t3, TLEN, -1) ;

  return 0 ;
}
