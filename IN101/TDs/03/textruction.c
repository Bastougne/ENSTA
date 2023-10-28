#include <stdio.h>     /* For file operations. */
#include <stdbool.h>   /* For booleans. */
#include <ctype.h>     /* For isalpha. */
#include <stdlib.h>    /* For srand. */
#include <unistd.h>    /* For getpid. */
#include <string.h>



void shuffle (char *buffer) {
  int len = strlen (buffer) ;
  /* Only need to work of the word has more than 3 letters since first and
     last must not move. */
  if (len > 3) {
    int i ;
    int len_minus_two = len - 2 ;
    /* Iterate on all the letters between the first and the last ones, bounds
       excluded. */
    for (i = 1; i <= len_minus_two; i++) {
      /* Randomly chose 1 character index in the string between first and last
         letters excluded . */
      int j = 1 + (rand () % len_minus_two) ;
      /* Exchange it with the current character. */
      char tmp = buffer[i] ;
      buffer[i] = buffer[j] ;
      buffer[j] = tmp ;
    }
  }
}


/* If different from the null character ('\0'), this represent an already
   read character that is not alphabetic, hence that stopped the input
   of a string. Since this character was not put in the ended string but was
   really read, we must remind it to return it next time the lexer will be
   called. Otherwise, we would loose it.
   We don't export this variable in the .h since it is purely "local" to the
   next_word function. */
char pending_char = '\0' ;


bool next_word (FILE *in, char *buffer) {
  int i = 0 ;  /* Where to add in the string under construction the current
                  read character. */
  int found_char ;  /* Character currently read from the file. */

  /* If the previous time we already read a character that stopped the
     previous string construction, then we must use it to build the current
     string. */
  if (pending_char != '\0') {
    /* Make a string with this only character. */
    buffer[0] = pending_char ;
    buffer[1] = '\0' ;     /* Close the string. */
    /* Character is not anymore to process. Clear it. */
    pending_char = '\0' ;
    return (true) ;   /* End. */
  }

  /* "Else" ... no pending character, hence really read in the file. */
  found_char = fgetc (in) ;
  while (!feof (in) && isalpha (found_char)) {
    /* While the end of file is not reached and the read character is
       alphabetic, store it in the string under construction. */
    buffer[i] = found_char ;
    i++ ;
    /* Read next character. */
    found_char = fgetc (in) ;
  }

  /* Always close the current string. Even if we didn't read anymore
     characters. */
  buffer[i] = '\0' ;
  /* If we stopped because end of file we must ensure that we do not still
     have already read a word. If so, return true. */
  if (feof (in)) {
    if (i != 0) return (true) ;
    else return (false) ;/* Otherwise really nothing remaining, return false. */
  }
  else {
    /* Stopped *not* because end of file. Hence inevitably because a non
       alphabetic character was read. Hence, remind it for next turn and
       return telling that there is possibly something that remains to be
       read. String under construction was closed just above, hence is
       complete for this turn. */
    pending_char = found_char ;
    return (true) ;
  }
}


int main (int argc, char *argv[]) {
  FILE *in ;
  char buffer[256] ;

  /* Ensure there is only one argument on the command line. */
  if (argc != 2) {
    printf ("Error: wrong number of arguments. Expected <file name>.\n") ;
    return (1) ;
  }

  /* Attempt to open the file whose name was given on the command line. Open
     it in "read" mode. */
  in = fopen (argv[1], "rb") ;
  if (in == NULL) {
    /* Unable to open the file. */
    printf ("Error: unable to open file '%s'.\n", argv[1]) ;
    return (1) ;
  }

  /* Initialize random generator. */
  srand (getpid ()) ;
  /* While the lexing function doesn't tell we reached the end of the file... */
  while (next_word (in, buffer)) {
    /* Hack the letters of the read word. */
    shuffle (buffer) ;
    /* Print the hacked word. */
    printf ("%s", buffer) ;
  }

  /* Close the input file before exiting. */
  fclose (in) ;
  return (0) ;
}
