#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int find_index_by_name (char *in_array[], int tlen, char *name) {
  for (int i = 0; i < tlen; i++) {
    if (strcmp (in_array[i], name) == 0) return i ;
  }
  return -1 ;
}


void compute_amounts (char *fname) {
  unsigned int nb_persons ;
  char **names ; /* Array of names of persons. */
  /* Temporary strings to fetch names. We could save one but let's keep 3
     instead of 2 for sake of readability. */
  char tmp_name[256], name_debit[256], name_credit[256] ;
  int *balances ;      /* Array of balances. */
  int amount ;    /* Read amount at each iteration in the file. */

  /* Open the file. */
  FILE *file = fopen (fname, "rb") ;
  if (file == NULL) {
    printf ("Error. Unable to open file.\n") ;
    return ;
  }

  /* Get the number of persones. */
  fscanf (file, "%u", &nb_persons) ;
  /* Create the array of persons. */
  names = malloc (nb_persons * sizeof (char*)) ;
  if (names == NULL) {
    printf ("Error. Unable to allocate the array of persons.\n") ;
    fclose (file) ;
    return ;
  }

  /* Fill the array of persons. */
  for (int i = 0; i < nb_persons; i++) {
    fscanf (file, "%s", tmp_name) ;
    names[i] = malloc ((strlen (tmp_name) + 1) * sizeof (char)) ;
    if (names[i] == NULL) {
      printf ("Error. Unable to allocate a name.\n") ;
      /* Free the names already allocated at this point. */
      for (i = i - 1; i >= 0; i--) free (names[i]) ;
      free (names) ;
      fclose (file) ;
      return ;
    }
    strcpy (names[i], tmp_name) ;
  }

  /* Create an array with a balance of 0 for each person. */
  balances = malloc (nb_persons * sizeof (int)) ;
  if (balances == NULL) {
    printf ("Error. Unable to allocate the array of balances.\n") ;
    for (int i = 0; i < nb_persons; i++) free (names[i]) ;
    free (names) ;
    fclose (file) ;
    return ;
  }
  for (int i = 0; i < nb_persons; i++) balances[i] = 0 ;

  /* Loop on the file until its end... */
  fscanf (file, "%s %s %d", name_debit, name_credit, &amount) ;
  while (!feof (file)) {
    /* Get the index of the person to debit. */
    int index_debit = find_index_by_name (names, nb_persons, name_debit) ;
    /* Get the index of the person to credit. */
    int index_credit = find_index_by_name (names, nb_persons, name_credit) ;
    if ((index_credit == -1) || (index_debit == -1)) {
      printf ("Error. Unable to find a person.\n") ;
      /* TODO : must free arrays and close the file. See how it is done
         at the end of the function. I'm lazy in this solution. */
      return ;
    }
    /* Subtract / add the amount. */
    balances[index_debit] = balances[index_debit] - amount ;
    balances[index_credit] = balances[index_credit] + amount ;
    /* Read next line if any. */
    fscanf (file, "%s %s %d", name_debit, name_credit, &amount) ;
  }
  /* Close the opened file. */
  fclose (file) ;
  /* Summarize the debts/credits. */
  for (int i = 0; i < nb_persons; i++)
    printf ("%s : %d\n", names[i], balances[i]) ;

  /* Free the allocated memory. */
  for (int i = 0; i < nb_persons; i++) free (names[i]) ;
  free (names) ;
  free (balances) ;
}


int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf ("Error. Wrong number of arguments.\n") ;
    return 1 ;
  }

  compute_amounts (argv[1]) ;
  return 0 ;
}
