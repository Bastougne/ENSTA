#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int* table_occurences( char* fichier ) {
    int* table;
    int val;
    FILE* f = fopen( fichier, "r" );
    if ( f == NULL ) {
        fclose( f );
        return( NULL );
    }
    fscanf( f, "%d", &val );
    while ( val != EOF ) {
        table[val] = table[val] + 1;
        fscanf( f, "%d", &val );
    }
    fclose( f );
    return( table );
}

struct huff_node_t {
  unsigned char letter;
  unsigned int occurences;
  struct huff_node_t* right;
  struct huff_node_t* left;
};

struct huff_node_t* build_tree( char* fichier ) {
  int nb = 0;
  int min1, min2;
  struct huff_node_t* arbres[256];
  struct huff_node_t* arbre_min1;
  struct huff_node_t* arbre_min2;
  int* table = table_occurences( fichier );
  if ( table == NULL ) {
    return( NULL );
  }
  for ( int i = 0; i < 256; i++ ) {
    arbres[i] = malloc( sizeof( struct huff_node_t ) );
    if ( arbres[i] == NULL) {
      for (int i ;i >= 0; i--) free (trees[i]) ;
      free (occs_tbl) ;
      return (NULL) ;
    }
    arbres[i]->letter = ( char ) i;
    arbres[i]->occurences = 0;
    arbres[i]->right = NULL;
    arbres[i]->left = NULL;
  }
  while ( nb < 255 ) {
    min1 = 0;
    min2 = 0;
    for ( int i = 0; i < 256 - nb; i++ ) {
      if ( arbres[i]->occurences < arbres[min1]->occurences ) {
        min2 = min1;
        min1 = i;
      } else if ( arbres[i]->occurences < arbres[min2]->occurences ) {
        min2 = i;
      }
      arbre_min1 = arbres[min1];
      arbre_min2 = arbres[min2];
    }
    arbres[min1] = malloc( sizeof( struct huff_node_t ) );
    arbres[min1]->occurences = arbres[min1]->occurences + arbres[min2]->occurences;
    arbres[min1]->right = arbre_min1;
    arbres[min1]->left = arbre_min2;
    table[min1] = table[min1] + table[min2];
  }
  return( arbres[0] );
}

bool encode (char *in_fname, char *out_fname, char **codes)
{
  FILE *in, *out ;
  int c ;

  in = fopen (in_fname, "rb") ;
  if (in == NULL) {
    printf ("Error. Unable to open input file '%s'.\n", in_fname) ;
    return (false) ;
  }

  out = fopen (out_fname, "wb") ;
  if (out == NULL) {
    printf ("Error. Unable to open output file '%s'.\n", out_fname) ;
    fclose (in) ;
    return (false) ;
  }

  /* Lecture caractère par caractère du fichier d'entrée. */
  c = fgetc (in) ;
  while (c != EOF) {
    fprintf (out, "%s", codes[c]) ;
    c = fgetc (in) ;
  }

  fclose (in) ;
  fclose (out) ;
  return (true) ;
}

void free_tree( struct huff_node_t* arbre ) {
  if ( arbre != NULL ) {
    free_tree( arbre->left );
    free_tree( arbre->right );
    free( arbre );
  }
}
/** \brief Fonction de parcours récursif de l'arbre de Huffman permettant
    de remplir la table des codes. Elle prend en argument un buffer dans
    lequel elle va stocker les différents "bits" de codage rencontrés au cours
    de la descente et recopiera, une fois arrivée à un feuille, la chaîne de
    ces "bits" dans l'entrée de la table correspondant au caractère de la
    feuille.
    \param tree : Noeud courant exploré de l'arbre.
    \param accu : Buffer pour stocker au fur et à mesure de la descente dans
    l'arbre les caractères '0' et '1' des bits rencontrés.
    \param accu_len : Nombre actuel de caractères dans l'accu.
    \param codes : Table des codes à remplir.
    \return Booléen disant si la mémorisation des code s'est passée
    correctement.
    \note Cette fonction est locale au fichier courant et n'est pas exportée.
    Elle sert uniquement de "helper" à la fonction \a get_codes. */
static bool tree_walk (struct huff_node_t *tree, char *accu, int accu_len,
                       char **codes)
{
  if (tree != NULL) {
    if (tree->left == NULL) {
      /* Noeud terminal. Notons que par invariant le fils droit doit être
         également à NULL. */
      codes[tree->letter] = malloc ((accu_len + 1) * sizeof (char)) ;
      if (codes[tree->letter] == NULL) return (false) ;
      strncpy (codes[tree->letter], accu, accu_len) ;
      codes[tree->letter][accu_len] = '\0' ;
      return (true) ;
    }
    else {
      /* Noeud non terminal, on récurse à left et à right en augmentant
         l'accumulateur. */
      accu[accu_len] = '0' ;
      if (! tree_walk (tree->left, accu, accu_len + 1, codes)) return (false) ;
      accu[accu_len] = '1' ;
      return (tree_walk (tree->right, accu, accu_len + 1, codes)) ;
    }
  }
  return (true) ;
}

/** \brief Récupération de la table des codes associés à l'arbre de Huffman
    passé en argument.
    \param tree : Pointeur sur la racine de l'arbre de Huffman.
    \return Tableau de 256 chaînes de caractères représentant le code associé
    à chaque caractère (indexation par le code du caractère). Chaque chaîne
    est composée de caractères '0' et '1' formant une représentation textuelle
    du code binaire associé au caractère encodé. */
char** get_codes (struct huff_node_t *tree)
{
  int i ;
  /* Le cas le plus dégénéré le code le plus long est égal au nombre de
     symboles (ici 256) - 1. Il faut 1 octet de plus pour clore la chaîne
     obtenue. Donc une longueur de chaîne maximale de 256 caractères. */
  char tmp_buffer[256] ;

  char **codes = malloc (257 * sizeof (char*)) ;
  if (codes == NULL) return (NULL) ;

  /* Initialisation des codes à "aucune chaîne". */
  for (i = 0; i < 256; i++) codes[i] = NULL ;

  /* Parcours récursif de l'arbre pour remplir la table. */
  if (! tree_walk (tree, tmp_buffer, 0, codes))
    printf ("Error while building codes table. Table may be incomplete.\n") ;

  return (codes) ;
}


/** \brief Décodage du fichier compressé \a in_fname selon l'arbre de Huffman
    \a tree et écriture du résultat dans le fichier \a out_fname.
    \param in_fname : Fichier source à lire et décoder.
    \param out_fname : Fichier destination dans lequel écrire le résultat du
    décodage.
    \param tree : Arbre de Huffman ayant servi à compresser le fichier initial
    et dont le résultat de compression (à décompresser) se trouve dans
    \a in_fname.
    \return Booléen disant si la décompression s'est passée sans erreur. */

bool decode (char *in_fname, char *out_fname, struct huff_node_t *tree)
{
  FILE *in, *out ;
  int c ;
  struct huff_node_t *current_node ;
  bool error = false ;

  in = fopen (in_fname, "rb") ;
  if (in == NULL) {
    printf ("Error. Unable to open input file '%s'.\n", in_fname) ;
    return (false) ;
  }

  out = fopen (out_fname, "wb") ;
  if (out == NULL) {
    printf ("Error. Unable to open output file '%s'.\n", out_fname) ;
    fclose (in) ;
    return (false) ;
  }
  /* Lecture "bit par bit", donc dans notre cas simplifié, caractère par
     caractère du fichier d'entrée et descente dans l'arbre de Huffman de
     la racine jusqu'à trouver une feuille. */
  c = fgetc (in) ;
  current_node = tree ;
  while ((! error) && (c != EOF)) {
    switch (c) {
    case '0':
      /* Descente à left. */
      current_node = current_node->left ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL left child.\n") ;
        error = true ;
      }
      /* Si le noeud est une feuille, il faut écrire le caractère correspondant
         et repartir du haut de l'arbre. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '0'. */

    case '1':
      /* Descente à right. */
      current_node = current_node->right ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL right child.\n") ;
        error = true ;
      }
      /* Même chose que pour la descente à left. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '1'. */

    default:
      /* Ne devrait jamais se produire puisque l'on n'a écrit que des
         caractères '0' et '1'. */
      printf ("Error. Unexpected bit-like character in input stream.\n") ;
      error = true ;
      break ;
    }

    /* Lecture du prochain "bit" (caractère). */
    c = fgetc (in) ;
  }   /* Fin de while (c != EOF). */

  /* Normalement, il ne devrait pas rester de "bits" en suspend, donc à la
     fin de la lecture du flot de biti on devrait se trouver de nouveau à la
     racine de l'arbre. Ca sentirait le bug ou le fichier corrompu. */
  if (current_node != tree) printf ("Warning. Spurious bit(s) remaining.\n") ;
  if (error) printf ("Error encountered.\n") ;

  fclose (in) ;
  fclose (out) ;
  return (true) ;
}


/** \brief Programme principal qui lit un fichier (\a argv[1]), l'encode et
    stocke le résultat dans un autre fichier (\a argv[2]), puis décode ce
    dernier en stockant le résultat du décodage dans un 3ème fichier
    (\a argv[3]). */
int main (int argc, char *argv[])
{
  int i ;
  struct huff_node_t *tree ;
  char **codes ;

  if (argc != 4) {
    printf
      ("Wrong argument. Expected <input file name> <ouput file name> \
<ouput file name>.\n") ;
    return (-1) ;
  }

  tree = build_tree (argv[1]) ;
  if (tree == NULL) {
    printf ("Error. Could not build tree.\n") ;
    return (-1) ;
  }

  codes = get_codes (tree) ;
  if (codes == NULL) {
    printf ("Error. Codes table not available.\n") ;
    free_tree (tree) ;
    return (-1) ;
  }

  /* Encodage: argv[1] -> argv[2]. */
  if (! encode (argv[1], argv[2], codes)) printf ("Encoding failed.\n") ;


  /* Décodage: argv[2] -> argv[3]. */
  if (! decode (argv[2], argv[3], tree)) printf ("Decoding failed.\n") ;

  /* Libération finale de la mémoire utilisée. */
  for (i = 0; i < 256; i++) {
    if (codes[i] != NULL) free (codes[i]) ;
  }
  free (codes) ;
  free_tree (tree) ;
  return (0) ;
}
