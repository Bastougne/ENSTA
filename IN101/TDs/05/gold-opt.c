#include <stdio.h>
#include <stdlib.h>

int max (int x, int y) { return x > y ? x : y ; }
int min (int x, int y) { return x < y ? x : y ; }


#ifdef COUNTREC
/* Si on compile avec l'option -DCOUNTREC, le programme compte et affiche
   le nombre d'appels récursifs faits à la fonction max_loot. */
int nb_rec_calls = 0 ;
#endif


/* Calcul du nombre maximal de pièces que le joueur 1 doit récupérer en
   partant du principe que le joueur 2 jour de manière optimale. */
int max_loot (int *pots, int l, int r, int **memo) {
#ifdef COUNTREC
  nb_rec_calls++ ;
#endif

  if (memo[l][r] != -1) return memo[l][r] ;

  /* Cas de base: seulement un pot restant, on n'a pas le choix, on le prend. */
  if (l == r) {
    memo[l][r] = pots[l] ;
    return pots[l] ;
  }

  /* Il ne reste que 2 pots, donc l'adversaire va avoir encore un tour après
     nous. On maximise notre gain pour notre dernier tour. */
  if (l + 1 == r) {
    int best = max (pots[l], pots[r]) ;
    memo[l][r] = best ;
    return best ;
  }

  /* Si le joueur 1 prend le pot de gauche (l), le joueur 2 a deux choix
     parmi les pots restants dans [l + 1, r] :
     - s'il prend à gauche (l + 1), on récurse sur [l + 2, r]
     - s'il prend à droite (r), on récurse sur [l + 1, r - 1] */
  int from_left =
    pots[l] + min (max_loot (pots, l + 2, r, memo),
                   max_loot (pots, l + 1, r - 1, memo)) ;
  /*  Si le joueur 1 prend le pot de droite (j), le joueur 2 a deux choix
      parmi les pots restants dans [l, r - 1] :
      - s'il prend à gauche (l), on récurse sur [l + 1, r - 1]
      - s'il prend à droite (r - 1), on récurse sur [l, r - 2] */
  int from_right =
    pots[r] + min (max_loot (pots, l + 1, r - 1, memo),
                   max_loot (pots, l, r - 2, memo)) ;
   int best = max (from_left, from_right) ;
   memo[l][r] = best ;
  /* On retourne le max des deux possibilités pour le joueur 1. */
   return best ;
}


int main (int argc, char *argv[]) {
  if (argc < 2) {
    printf ("No pots. Cowardly giving up.\n") ;
    return 0 ;
  }

  int nb_pots = argc - 1 ;
  /* On construit le tableau de pots. */
  int *pots = malloc (nb_pots * sizeof (int)) ;
  if (pots == NULL) {
    printf ("Error: no memory for gold.\n") ;
    return 1 ;
  }
  /* On construit le tableau de mémoïsation et on le remplit de -1 dans
     la foulée. */
  /* [TODO] On n'a pas vérifié le succès des allocations, c'est TRÈS mal.
     Considérons que c'est pour ne pas rallonger le code de la solution,
     certainement pas par fénéantise... Hum... */
  int **memo = malloc (nb_pots * sizeof (int*)) ;
  for (int i = 0; i < nb_pots; i++) {
    memo[i] = malloc (nb_pots * sizeof (int)) ;
    for (int j = 0; j < nb_pots; j++) memo[i][j] = -1 ;
  }

  /* On remplit le tableau de pots. */
  for (int i = 0; i < nb_pots; i++) pots[i] = atoi (argv[i + 1]) ;

  printf ("Max loot for player 1: %d\n",
          max_loot (pots, 0, nb_pots - 1, memo)) ;

#ifdef COUNTREC
  printf ("Recursive calls ount: %d\n", nb_rec_calls) ;
#endif

  free (pots) ;
  for (int i = 0; i < nb_pots; i++) free (memo[i]) ;
  free (memo) ;
  return 0 ;
}
