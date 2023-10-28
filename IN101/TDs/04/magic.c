#include <stdio.h>
#include <stdlib.h>

/* Cut the deck. Put everything above 'at' below the deck. In a deck, the upper
   card is at index 0, deeper cards are a increasing indices.
   [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
          ^
   Cut a index 2 take everything before the cell of index 2 end put it at the
   end of the deck (array).
   [3, 4, 5, 1, 2, 3, 4, 5, 1, 2] */
int* cut (int *deck, int at, unsigned int nb_cards) {
  if ((at >= 0) && (at < nb_cards)) {
    int *new_deck = malloc (nb_cards * sizeof (int)) ;
    if (new_deck == NULL) {
      printf ("Error. cut. No memory.\n") ;
      exit (1) ;
    }

    int dest = 0 ;
    for (; dest < nb_cards - at; dest++) new_deck[dest] = deck[at + dest] ;
    for (int src = 0; src < at; src++) {
      new_deck[dest] = deck[src] ;
      dest++ ;
    }
    return new_deck ;
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
      right deck = [1, 2, 3, 4, 5] */
struct deck_pair_t* split_deck_in_2 (int *deck, unsigned int nb_cards) {
  if (nb_cards % 2 != 0) return NULL ;
  int sub_deck_len = nb_cards / 2 ;
  struct deck_pair_t *decks = malloc (sizeof (struct deck_pair_t)) ;
  if (decks == NULL) {
    printf ("Error. split_deck_in_2. No memory.\n") ;
    exit (1) ;
  }
  decks->left_deck = malloc (sub_deck_len * sizeof (int)) ;
  if (decks->left_deck == NULL) {
    printf ("Error. split_deck_in_2. No memory.\n") ;
    free (decks) ;
    exit (1) ;
  }
  decks->right_deck = malloc (sub_deck_len * sizeof (int)) ;
  if (decks->right_deck == NULL) {
    printf ("Error. split_deck_in_2. No memory.\n") ;
    free (decks->left_deck) ;
    free (decks) ;
    exit (1) ;
  }
  /* Left deck contains the first half of cards in reverse order ! */
  /* Right deck contains the last half of cards without changing their order. */
  for (int i = 0; i < sub_deck_len; i++) {
    decks->left_deck[i] = deck[sub_deck_len - 1 - i] ;
    decks->right_deck[i] = deck[sub_deck_len + i] ;
  }
  return (decks) ;
}


/* Remove the first card of a deck assumed to contain at least 2 cards. Return
   the new deck whose size is initial deck's size - 1. */
int* remove_first (int *deck, unsigned int nb_cards) {
  int new_size = nb_cards - 1 ;
  if (new_size == 0) {
    printf ("Error. remove_first. Null new array size.\n") ;
    exit (1) ;
  }
  int *new_deck = malloc (new_size * sizeof (int)) ;
  if (new_deck == NULL) {
    printf ("Error. remove_first. No memory.\n") ;
    exit (1) ;
  }
  for (int i = 0; i < new_size; i++) new_deck[i] = deck[i + 1] ;
  return new_deck ;
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
    /* Make the moves. */
    int *deck_left2 = cut (deck_left, nb_moves_left, decks_size) ;
    int *deck_right2 = cut (deck_right, nb_moves_right, decks_size) ;
    /* Suppress the top card. */
    int *deck_left3 = remove_first (deck_left2, decks_size) ;
    int *deck_right3 = remove_first (deck_right2, decks_size) ;
    /* Free no more used decks. */
    free (deck_left2) ;
    free (deck_right2) ;
    play (deck_left3, deck_right3, decks_size - 1, nb_moves - 1) ;
  }
}


/* Size = 10 --> deck = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 }. */
#define DECK_SIZE (10)


/* Finally create the initial deck, ask the user to cut where he wants, how
   long he wants, then ask and execute the moves and check that the 2 ending
   cards are the same. */
int main () {
  int cut_at ;
  int *full_deck = malloc (DECK_SIZE * sizeof (int)) ;
  if (full_deck == NULL) {
    printf ("Error. main. No memory.\n") ;
    return 1 ;
  }
  for (unsigned int i = 0; i < (DECK_SIZE / 2); i++) {
    full_deck[i] = i + 1 ;
    full_deck[i + (DECK_SIZE / 2)] = i + 1 ;
  }

  printf ("Where to cut? ") ;
  scanf ("%d", &cut_at) ;
  while ((cut_at >= 0) && (cut_at < DECK_SIZE)) {
    int *new_deck = cut (full_deck, cut_at, DECK_SIZE) ;
    /* TODO: check success of the allocation. */
    free (full_deck) ;
    full_deck = new_deck ;
    printf ("Where to cut? ") ;
    scanf ("%d", &cut_at) ;
  }
  /* Some debug the spectator should never see ^^ */
  printf ("Deck is now:") ;
  for (unsigned int i = 0; i < DECK_SIZE; i++) printf (" %d", full_deck[i]) ;
  printf ("\n") ;

  struct deck_pair_t *decks = split_deck_in_2 (full_deck, DECK_SIZE) ;
  free (full_deck) ;
  play (decks->left_deck, decks->right_deck,
        (DECK_SIZE / 2), (DECK_SIZE / 2) - 1) ;
  free (decks->left_deck) ;
  free (decks->right_deck) ;
  free (decks) ;

  return 0 ;
}
