#include <stdio.h>
#include <stdlib.h>


/* Convert the graph representing debts between persons into a net amount
   per person. */
int* compute_amounts (int **graph, int nb_persons) {
  int *amounts = malloc (nb_persons * sizeof (int)) ;
  if (amounts == NULL) {
    printf ("Error. compute_amounts. No memory.\n") ;
    exit (1) ;
  }
  /* Clear the array. */
  for (int i = 0; i < nb_persons; i++) amounts[i] = 0 ;
  for (int i = 0; i < nb_persons; i++) {
    for (int j = 0; j < nb_persons; j++) {
      amounts[j] = amounts[j] + graph[i][j] ;
      amounts[i] = amounts[i] - graph[i][j] ;
    }
  }
  return amounts ;
}


/* Find the 2 indices of the minimal and maximal values inside an array. */
void find_min_max_indices (int *amounts, int nb_persons,
                           int *min_index, int *max_index) {
  int min_i = 0 ;
  int max_i = 0 ;
  for (int i = 0; i < nb_persons; i++) {
    if (amounts[i] < amounts[min_i]) min_i = i ;
    if (amounts[i] > amounts[max_i]) max_i = i ;
  }
  *min_index = min_i ;
  *max_index = max_i ;
}


#define min(x,y) ((x) < (y) ? (x) : (y))

void compute_flow (int *amounts, int nb_persons) {
  /* Find at once the 2 persons with min and max amount, i.e. the most
     debtor and the most creditor. */
  int min_i, max_i ;

  find_min_max_indices (amounts, nb_persons, &min_i, &max_i) ;
  /* If nobody has to pay and nobody expects money, we are done. */
  if ((amounts[min_i] == 0) && (amounts[max_i] == 0)) return ;
  /* Find the smallest absolute value of amount. */
  int to_pay = min (- amounts[min_i], amounts[max_i]) ;
  /* Reduce the pending debt of the debtor. */
  amounts[min_i] = amounts[min_i] + to_pay ;
  /* Reduce the pending credit of the creditor. */
  amounts[max_i] = amounts[max_i] - to_pay ;
  printf ("%d pays %d to %d.\n", min_i, to_pay, max_i) ;
  compute_flow  (amounts, nb_persons) ;
}


#define NB_PERSONS (4)

int main () {
  /* Allocate the graph.
     TODO: check success of allocations. I'm lazy today ^^ */
  int **debts = malloc (NB_PERSONS * sizeof (int*)) ;
  for (int i = 0; i < NB_PERSONS; i++)
    debts[i] = malloc (NB_PERSONS * sizeof (int)) ;
  /* Fill it. Manually it's boring!
    [ [ 0, 100, 50, 0 ],
      [ 0, 0, 0, 0 ],
      [ 75, 0, 0, 0 ],
      [ 0, 40, 20, 0 ] ] */
  debts[0][0] = 0 ; debts[0][1] = 100 ; debts[0][2] = 50 ; debts[0][3] = 0 ;
  debts[1][0] = 0 ; debts[1][1] = 0 ; debts[1][2] = 0 ; debts[1][3] = 0 ;
  debts[2][0] = 75 ; debts[2][1] = 0 ; debts[2][2] = 0 ; debts[2][3] = 0 ;
  debts[3][0] = 0 ; debts[3][1] = 40 ; debts[3][2] = 20 ; debts[3][3] = 0 ;

  /* Compute for each person what he must pay or receive. A positive value
     means that the person is creditor. A negative value means thar the
     person is debtor. */
  int *amounts = compute_amounts (debts, NB_PERSONS) ;
  printf ("Amounts:") ;
  for (int i = 0; i < NB_PERSONS; i++) printf (" %d", amounts[i]) ;
  printf ("\n") ;
  compute_flow (amounts, NB_PERSONS) ;
  free (amounts) ;
  return 0 ;
}

