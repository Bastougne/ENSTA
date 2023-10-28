#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6

enum elt_grille { vide, occupe, rate, detruit };

int c2i( int x, int y ) { return ( ( x - 1 ) + N * ( y - 1 ) ); }

void afficher( int *grille, int cache ) {
    char *val_case[4] = { ".", "*", "X", "O" };
    if ( cache == 1 ) {
        val_case[1] = ".";
    }
    for ( int i = 1; i <= N; i++ ) {
        for ( int j = 1; j <= N; j++ ) {
            printf( "%s", val_case[grille[c2i( i, j )]] );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

int *creer_grille() {
    int *grille = malloc( N * N * sizeof( int ) );
    for ( int i = 0; i < N * N; i++ ) {
        grille[i] = 0;
    }
    return ( grille );
}

void test_affichage() {
    int *grille = creer_grille();
    afficher( grille, 0 );
    grille[c2i( 3, 2 )] = occupe;
    grille[c2i( 1, 5 )] = rate;
    grille[c2i( 4, 4 )] = detruit;
    afficher( grille, 0 );
    afficher( grille, 1 );
}

void placer( int *grille, int i, int j, int lng, int hor_ver ) {
    if ( hor_ver == 0 ) {
        for ( int k = 0; k < lng; k++ ) {
            grille[c2i( i, j + k )] = occupe;
        }
    } else {
        for ( int k = 0; k < lng; k++ ) {
            grille[c2i( i + k, j )] = occupe;
        }
    }
}

void placer_alea( int *grille, int lng ) {
    int i = 1 + rand() % N;
    int j = 1 + rand() % N;
    int hor_ver = 0;
    int possible = 0;
    while ( possible == 0 ) {
        hor_ver = rand() % 2;
        while ( j + lng > N + 1 ) {
            j = 1 + rand() % N;
        }
        possible = 1;
        for ( int k = 0; k < lng; k++ ) {
            if ( hor_ver == 0 ) {
                if ( grille[c2i( i, j + k )] == occupe ) {
                    possible = 0;
                }
            } else {
                if ( grille[c2i( i + k, j )] == occupe ) {
                    possible = 0;
                }
            }
        }
    }
    placer( grille, i, j, lng, hor_ver );
}

void tirer( int *grille, int i, int j ) {
    if ( grille[c2i( i, j )] == occupe ) {
        grille[c2i( i, j )] = detruit;
    } else if ( grille[c2i( i, j )] == vide ) {
        grille[c2i( i, j )] = rate;
    }
}

int tout_detruit( int *grille ) {
    for ( int i = 0; i < N * N; i++ ) {
        if ( grille[i] == occupe ) {
            return ( 0 );
        }
    }
    return ( 1 );
}

void main() {
    srand( time( 0 ) );
    int *grille = creer_grille();
    placer_alea( grille, 3 );
    placer_alea( grille, 2 );
    int tours = 0;
    afficher( grille, 0 );
    while ( tout_detruit( grille ) == 0 ) {
        tours++;
        int x, y;
        printf( "Dans quelles cases jouer ?    -> " );
        scanf( "%d,%d", &x, &y );
        tirer( grille, x, y );
        afficher( grille, 1 );
    }
    printf( "Victoire en %d tours !\n", tours );
}