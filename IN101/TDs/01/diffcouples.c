#include <stdio.h>

void count (int *t, unsigned int tlen, int n) {
  int i, j ;
  int cpt = 0 ;

  for (i = 0; i < tlen; i++) {
    /* Le même élément peut être pris 2 fois. */
    if (t[i] - t[i] == n) cpt++ ;
    /* On doit commencer à j égal à la prochaine case. Comme on ne veut
       pas compter 2 fois (à cause de la symétrie testée ci-dessous) le
       cas où on prend la même valeur, on est bien obligé de faire le
       cas particulier ci-dessus. */
    for (j = i + 1; j < tlen; j++) {
      /* Attention, un "couple" est ordonné. Donc (a, b) <> (b, a). */
      if (t[i] - t[j] == n) cpt++ ;
      if (t[j] - t[i] == n) cpt++ ;
    }
  }
  printf ("%d\n", cpt) ;
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
