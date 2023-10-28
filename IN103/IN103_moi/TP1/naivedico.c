#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct word_list_t {
    char* word;
    struct word_list_t* next;
};

char** load_file(char* fname, unsigned int* size)
{
    char** words_array;
    unsigned int count_words = 0;
    struct word_list_t* wl = NULL;
    char buffer[256];
    FILE* in_hd;

    /* First open the file and check success. */
    in_hd = fopen(fname, "rb");
    if (in_hd == NULL) return (NULL);

    /* Read the first word. */
    fscanf(in_hd, "%s", buffer);
    while (!feof(in_hd)) {
        char* word_cpy;
        struct word_list_t* new_cell = malloc(sizeof(struct word_list_t*));
        if (new_cell == NULL) {
            /* Close the opened file. */
            fclose(in_hd);
            /* BAD: We should also free the already allocated string list cells, but
               I'm too lazzy ^^ Don't do this at home... */
            return (NULL);
        }
        /* Allocate memory to store the word. */
        word_cpy = malloc((1 + strlen(buffer)) * sizeof(char));
        if (word_cpy == NULL) {
            /* BAD: Same comment than above. */
            fclose(in_hd);
            return (NULL);
        }
        /* Copy the buffer into the fresh string. */
        strcpy(word_cpy, buffer);
        new_cell->word = word_cpy;
        /* Now, link the cell. */
        new_cell->next = wl;
        wl = new_cell;
        count_words++;

        /* Read the next word. */
        fscanf(in_hd, "%s", buffer);
    }

    /* Now, close the file since we do not need it anymore. */
    fclose(in_hd);

    /* It's now time to transfer the string into an array. Attention, the list
       construction has reversed the order of the words. */
    words_array = malloc(count_words * sizeof(char**));
    if (words_array == NULL) {
        /* BAD: We should free the already allocated memory. */
        return (NULL);
    }

    /* Store the size now since we will use 'count_words' to fill the array. */
    *size = count_words;

    while (count_words != 0) {
        /* Attention: by invariant, wl->next is never NULL while in the loop. This
           is due to the fact that the length of the list is exactly
           'count_words'. */
        struct word_list_t* tmp = wl->next;
        count_words--;
        /* Copy the pointer hence share the string. So, do not free it now ! */
        words_array[count_words] = wl->word;
        /* Go to the next cell of the list. */
        wl = tmp;
    }

    return (words_array);
}

bool find_word_naive (char** words, char* word, unsigned int num_words) {
  int i = 0 ;
  bool trouve = false ;
  while ( trouve == 0 && i < num_words ) {
      if ( strcmp( word, words[i] ) == 0 ) {
          trouve = true;
      } else {
          i++;
      }
  }
  return ( trouve ) ;
}

int main ( int argc, char *argv[] ) {
  char **words ;
  unsigned int num_words = 0 ;
  char buffer[30];
  if ( argc != 2 ) { // On v�rifie que les entr�es sont bien valides
    printf( "Entr�es invalides\n" ) ;
    return( 1 );
  }
  words = load_file( argv[1], &num_words ) ;
  if ( words == NULL ) {
    printf( "Fichier illisible\n" ) ;
    return( 1 );
  }
  while ( gets( buffer ) ) {
      if ( find_word_naive( words, buffer, num_words ) ) {
          printf( "Trouv�\n" );
      } else {
          printf( "Non trouv�\n" );
      }
  }
  return( 0 );
}
