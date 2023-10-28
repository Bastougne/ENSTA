#include <stdio.h>
#include <stdlib.h>

/* Cut the deck. Put everything above 'at' below the deck. In a deck, the upper
   card is at index 0, deeper cards are a increasing indices.
   [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
          ^
   Cut a index 2 take everything before the cell of index 2 end put it at the
   end of the deck (array).
   [3, 4, 5, 1, 2, 3, 4, 5, 1, 2]
   Modification performed in place, hence the function returns nothing.
   We need a temporary array since read and writes are overlaping in the
   initial deck. */
void cut (int *deck, int at, unsigned int nb_cards) {
  if ((at >= 0) && (at < nb_cards)) {
    int *tmp_deck = malloc (nb_cards * sizeof (int)) ;
    if (tmp_deck == NULL) {
      printf ("Error. cut. No memory.\n") ;
      exit (1) ;
    }

    int dest = 0 ;
    for (; dest < nb_cards - at; dest++) tmp_deck[dest] = deck[at + dest] ;
    for (int src = 0; src < at; src++) {
      tmp_deck[dest] = deck[src] ;
      dest++ ;
    }

    /* Copy back into the initial array. */
    for (int i = 0; i < nb_cards; i++) deck[i] = tmp_deck[i] ;
    free (tmp_deck) ;
    return ;
  }
  printf ("Error. cut. Invalid position.\n") ;
  exit (1) ;
}


/* Pair of sub-decks obtained after splitting the initial deck in two parts. */
struct deck_pair_t {
  int *left_deck ;
  int *right_deck ;
};


/* Split a deck (assumed to contain an even number of cards) into 2 subdecks.
   The left deck contains the the first half of cards in reverse order.
   The right deck contains the last half of cards without changing their order.
   Deck [1, 2, 3, 4, 5, 1, 2, 3, 4, 5] =>
      left deck = [5, 4, 2, 2, 1]
      right deck = [1, 2, 3, 4, 5]

   Both sub-decks share the same memory area as the initial one.
   Indeed, the right deck points inside the initial one. */
struct deck_pair_t* split_deck_in_2 (int *deck, unsigned int nb_cards) {
  if (nb_cards % 2 != 0) return NULL ;
  int sub_deck_len = nb_cards / 2 ;
  struct deck_pair_t *decks = malloc (sizeof (struct deck_pair_t)) ;
  if (decks == NULL) {
    printf ("Error. split_deck_in_2. No memory.\n") ;
    exit (1) ;
  }

  /* Left deck contains the first half of cards in reverse order ! So we
     must swap the elemnts of the first half of the deck. */
  for (int i = 0; i < sub_deck_len / 2; i++) {
    int tmp = deck[i] ;
    deck[i] = deck[sub_deck_len - 1 - i] ;
    deck[sub_deck_len - 1 - i] = tmp ;
  }

  /* Right deck contains the last half of cards without changing their order.
     So, nothing to do. */

  /* Left deck starts at the beginning of the initial stack. */
  decks->left_deck = deck ;
  /* Right deck start at the mid point of the initial stack. */
  decks->right_deck = &deck[sub_deck_len] ;
  return decks ;
}


/* Remove the first card of a deck assumed to contain at least 2 cards. Return
   the new deck whose size is initial deck's size - 1.
   Indeed do not remove anything physically, simply return the address of the
   next cell of the array. */
int* remove_first (int *deck, unsigned int nb_cards) {
  int new_size = nb_cards - 1 ;
  if (new_size == 0) {
    printf ("Error. remove_first. Null new array size.\n") ;
    exit (1) ;
  }
  /* Just return a pointer to the next element (pointer arithmetic). */
  return deck + 1 ;
}


/* Play the scenario of asking how many moves on each deck.
   One remarks that the "move" operation on each deck is exactly the same
   than the "shuffle" of the beginning.
   Indeed, the argument [decks_size] is useless since it is always equal to
   [nb_moves]. */
void play (int *deck_left, int *deck_right, unsigned int decks_size,
           unsigned int nb_moves) {
  if (nb_moves == 0) {
    printf ("%d -- %d\n", deck_left[0], deck_right[0]) ;
    if (deck_left[0] == deck_right[0]) printf ("Correct\n") ;
    else printf ("Lost\n") ;
   }
  else {
    int nb_moves_left ;
    printf ("%d moves allowed.\n#moves ont left deck? ", nb_moves) ;
    scanf ("%d", &nb_moves_left) ;
    while ((nb_moves_left < 0) || (nb_moves_left > nb_moves)) {
      printf ("Bad number of moves.\n#moves on left deck? ") ;
      scanf ("%d", &nb_moves_left) ;
    }

    unsigned int nb_moves_right = nb_moves - nb_moves_left ;
    /* Make the moves. Cuts are performed in place. */
    cut (deck_left, nb_moves_left, decks_size) ;
    cut (deck_right, nb_moves_right, decks_size) ;
    /* Suppress the top card. */
    int *deck_left2 = remove_first (deck_left, decks_size) ;
    int *deck_right2 = remove_first (deck_right, decks_size) ;
    play (deck_left2, deck_right2, decks_size - 1, nb_moves - 1) ;
  }
}


/* Size = 10 --> deck = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 }. */
#define DECK_SIZE (10)


/* Finally create the initial deck, ask the user to cut where he wants, how
   long he wants, then ask and execute the moves and check that the 2 ending
   cards are the same. */
int main () {
  int cut_at ;
  int full_deck[DECK_SIZE] ;

  for (unsigned int i = 0; i < (DECK_SIZE / 2); i++) {
    full_deck[i] = i + 1 ;
    full_deck[i + (DECK_SIZE / 2)] = i + 1 ;
  }

  printf ("Where to cut? ") ;
  scanf ("%d", &cut_at) ;
  while ((cut_at >= 0) && (cut_at < DECK_SIZE)) {
    cut (full_deck, cut_at, DECK_SIZE) ;
    printf ("Where to cut? ") ;
    scanf ("%d", &cut_at) ;
  }
  /* Some debug the spectator should never see ^^ */
  printf ("Deck is now:") ;
  for (unsigned int i = 0; i < DECK_SIZE; i++) printf (" %d", full_deck[i]) ;
  printf ("\n") ;

  struct deck_pair_t *decks = split_deck_in_2 (full_deck, DECK_SIZE) ;
  play (decks->left_deck, decks->right_deck,
        (DECK_SIZE / 2), (DECK_SIZE / 2) - 1) ;

  free (decks) ;
  return 0 ;
}
