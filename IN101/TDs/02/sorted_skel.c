#include <stdbool.h>
#include <stdio.h>

bool sorted (int *t, unsigned int l) {
  /* *********************************** */
  /* ************ Fill here ************ */
  /* *********************************** */
}


int main () {
  printf ("%d\n", sorted (NULL, 0)) ;  // true
  int t1[1] = { 42 } ;
  printf ("%d\n", sorted (t1, 1)) ;   // true
  int t2[4] = { 1, 1, 1, 1 } ;
  printf ("%d\n", sorted (t2, 4)) ;   // true
  int t3[6] = { 1, 1, 1, 1, 2, 3 } ;
  printf ("%d\n", sorted (t3, 6)) ;   // true
  int t4[7] = { 1, 1, 1, 1, 2, 3, 2 } ;
  printf ("%d\n", sorted (t4, 7)) ;   // false
  int t5[3] = { 4, 2, 1 } ;
  printf ("%d\n", sorted (t5, 3)) ;   // true
  int t6[4] = { 4, 2, 2, 1 } ;
  printf ("%d\n", sorted (t6, 4)) ;   // true
  int t7[4] = { 4, 0, 2, 1 } ;
  printf ("%d\n", sorted (t7, 4)) ;   // false
  int t8[4] = { 0, 4, 2, 1 } ;
  printf ("%d\n", sorted (t8, 4)) ;   // false
  int t9[5] = { 0, 1, 4, 2, 1 } ;
  printf ("%d\n", sorted (t9, 5)) ;   // false
  int t10[5] = { 4, 4, 3, 2, 1 } ;
  printf ("%d\n", sorted (t10, 5)) ;   // true
  int t11[6] = { 4, 4, 3, 2, 1, 4 } ;
  printf ("%d\n", sorted (t11, 6)) ;   // false
  return 0 ;
}
