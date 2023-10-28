#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { INCONNU_SANS,
       INCONNU_AVEC,
       DEMINE,
       MINE };

int *creer_grille( int N, int M ) {
    int *grille = malloc( N * M * sizeof( int ) );
    for ( int i = 0; i < N * M; i++ ) {
        grille[i] = INCONNU_SANS;
    }
    return ( grille );
}

int afficher_grille( int *grille, int N, int M ) {
    char *val_case[4] = { "?", "!", ".", "*" };
    int X = 0;
    int Y = 0;
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            printf( "%s", val_case[grille[M * i + j]] );
            if ( grille[M * i + j] == MINE ) {
                X++;
            }
            if ( grille[M * i + j] == INCONNU_AVEC ) {
                Y++;
            }
        }
        printf( "\n" );
    }
    printf( "%d trouvées, %d restantes\n", X, Y );
    return ( Y );
}

void test_affichage() {
    int N = 3;
    int M = 4;
    int *grille = creer_grille( 4, M );
    grille[4] = DEMINE;
    grille[2] = INCONNU_AVEC;
    grille[6] = INCONNU_AVEC;
    grille[8] = MINE;
    afficher_grille( grille, N, M );
}

int miner( int c, int *grille, int N, int M ) {
    int avec = 0;
    if ( grille[c] == MINE || grille[c] == INCONNU_AVEC ) {
        avec = 1;
    }
    grille[c] = INCONNU_AVEC;
    return ( avec );
}

int *test_miner() {
    int N = 3;
    int M = 4;
    int *grille = creer_grille( N, M );
    printf( "%d\n", miner( 1, grille, N, M ) );
    printf( "%d\n", miner( 1, grille, N, M ) );
    printf( "%d\n", miner( 5, grille, N, M ) );
    afficher_grille( grille, N, M );
    return ( grille );
}

void mine_alea( int *grille, int N, int M ) {
    int c = 0;
    do {
        c = rand() % ( N * M );
    } while ( miner( c, grille, N, M ) == 1 );
}

void mine_alea_k( int *grille, int N, int M, int K ) {
    for ( int i = 0; i < K; i++ ) {
        mine_alea( grille, N, M );
    }
}

void transformer( int c, int *grille, int N, int M ) {
    if ( grille[c] == INCONNU_AVEC ) {
        grille[c] = MINE;
    }
    if ( grille[c] == INCONNU_SANS ) {
        grille[c] = DEMINE;
    }
}

int jouer( int c, int *grille, int N, int M ) {
    if ( grille[c] == INCONNU_AVEC || grille[c] == MINE ) {
        return ( 0 );
    }
    int j = c % M;
    int i = ( c - j ) / M;
    transformer( M * i + j, grille, N, M );
    if ( j != 0 ) {
        transformer( M * i + ( j - 1 ), grille, N, M );
    }
    if ( j != M - 1 ) {
        transformer( M * i + ( j + 1 ), grille, N, M );
    }
    if ( i != 0 ) {
        transformer( M * ( i - 1 ) + j, grille, N, M );
    }
    if ( i != N - 1 ) {
        transformer( M * ( i + 1 ) + j, grille, N, M );
    }
    return ( 1 );
}

void test_jouer() {
    int N = 3;
    int M = 4;
    int K = 3;
    srand( time( 0 ) );
    int *grille = test_miner();
    jouer( 7, grille, N, M );
    afficher_grille( grille, N, M );
    jouer( 9, grille, N, M );
    afficher_grille( grille, N, M );
}

int afficher_grille_v2( int *grille, int N, int M ) {
    char *val_case[9] = { "?", "!", ".", "*", "0", "1", "2", "3", "4" };
    int X = 0;
    int Y = 0;
    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < M; j++ ) {
            printf( "%s", val_case[grille[M * i + j]] );
            if ( grille[M * i + j] == MINE ) {
                X++;
            }
            if ( grille[M * i + j] == INCONNU_AVEC ) {
                Y++;
            }
        }
        printf( "\n" );
    }
    printf( "%d trouvées, %d restantes\n", X, Y );
    return ( Y );
}

int nb_mines( int c, int *grille, int N, int M ) {
    int j = c % M;
    int i = ( c - j ) / M;
    int nb = 0;
    if ( j != 0 ) {
        if ( grille[M * i + ( j - 1 )] == INCONNU_AVEC ) {
            nb++;
        }
    }
    if ( j != M - 1 ) {
        transformer( M * i + ( j + 1 ), grille, N, M );
    }
    if ( i != 0 ) {
        transformer( M * ( i - 1 ) + j, grille, N, M );
    }
    if ( i != N - 1 ) {
        transformer( M * ( i + 1 ) + j, grille, N, M );
    }
}

int jouer_v2( int c, int *grille, int N, int M ) {
    if ( grille[c] == INCONNU_AVEC || grille[c] == MINE ) {
        return ( 0 );
    }
    int j = c % M;
    int i = ( c - j ) / M;
    transformer( M * i + j, grille, N, M );
    if ( j != 0 ) {
        transformer( M * i + ( j - 1 ), grille, N, M );
    }
    if ( j != M - 1 ) {
        transformer( M * i + ( j + 1 ), grille, N, M );
    }
    if ( i != 0 ) {
        transformer( M * ( i - 1 ) + j, grille, N, M );
    }
    if ( i != N - 1 ) {
        transformer( M * ( i + 1 ) + j, grille, N, M );
    }
    return ( 1 );
}

int main() {
    int N = 3;
    int M = 4;
    int K = 3;
    srand( time( 0 ) );
    int *grille = creer_grille( N, M );
    mine_alea_k( grille, N, M, K );
    afficher_grille( grille, N, M );
    int tours = 0;
    do {
        tours++;
        int c = 0;
        printf( "numéro : " );
        scanf( "%d", &c );
        if ( jouer( c, grille, N, M ) == 0 ) {
            printf( "Perdu en %d tours.\n", tours );
            return ( 0 );
        }
        if ( afficher_grille( grille, N, M ) == 0 ) {
            printf( "Gagné en %d tours.\n", tours );
            return ( 1 );
        }
    } while ( 1 );
}
