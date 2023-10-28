#include <stdio.h>
#include <stdlib.h>


char *data_0_23_strings[] = {
  "", "une", "deux", "trois", "quatre", "cinq", "six", "sept", "huit",
  "neuf", "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
  "dix sept", "dix huit", "dix neuf", "vingt", "vingt et une", "vingt deux",
  "vingt trois"
};


/* Convert a number in [0; 21] into a french string. */
void string_of_0_23 (unsigned int n) {
  if (n > 23) {
    printf ("Error. Wrong number > 23.\n") ;
    exit (1) ;
  }
  printf ("%s", data_0_23_strings[n]) ;
}


/* Convert a number of minutes in [0; 30] into a french string. */
void string_of_minutes_0_30 (unsigned int n) {
  if (n == 15) printf ("et quart") ;
  else if (n == 30) printf ("et demi") ;
  else if (n <= 21) string_of_0_23 (n) ;
  else if (n < 30) {
    printf ("vingt") ;
    if (n != 20) printf (" ") ; /* Space if "vingt" followed by something. */
    string_of_0_23 (n - 20) ;
  }
  else {
    printf ("Error. Wrong number of minutes.\n") ;
    exit (1) ;
  }
}


/* Convert a number of hours in [0; 23] into a french string. */
void string_of_hours (unsigned int hours) {
  /* Handle the two particular cases of "midi" and "minuit". */
  if (hours == 0) printf ("minuit") ;
  else if (hours == 12) printf ("midi") ;
  else if (hours == 1) {
    /* No 's' at "heure" since only one hour. */
    string_of_0_23 (hours) ;
    printf (" heure") ;
  }
  else if ((hours >= 2) && (hours <= 23)) {
    string_of_0_23 (hours) ;
    printf (" heures") ;
  }
  else {
    printf ("Error. Wrong number of hours.\n") ;
    exit (1) ;
  }
}


void string_of_time (unsigned int hours, unsigned int minutes) {
  /* For minutes > 30, we print "moins" and process 60 minus the number
     of minutes. Hence our function for minutes does not have to handle
     manually all the 59 minutes.
     If minutes are > 30, the hour said is the next one. Be careful for
     23 oclock : it must wrap to 0, not 24. */
  if (minutes > 30) {
    /* Check the special case of 45 minutes since there is a "le" after
       "moins". For other minutes > 30, there is only "moins". */
    if (minutes == 45) {
      string_of_hours ((hours + 1) % 24) ;
      printf (" moins le quart") ;
    }
    else {
      string_of_hours ((hours + 1) % 24) ;
      printf (" moins ") ;
      string_of_minutes_0_30 (60 - minutes) ;
    }
  }
  else {
    /* Minutes < 30. */
    string_of_hours (hours) ;
    if (minutes != 0) printf (" ") ;
    string_of_minutes_0_30 (minutes) ;
  }
}


int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf ("Error. Wrong number of arguments.\n") ;
    return 1 ;
  }

  string_of_time (atoi (argv[1]), atoi (argv[2])) ;
  printf ("\n") ;
  return 0 ;
}
