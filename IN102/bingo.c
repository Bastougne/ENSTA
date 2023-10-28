#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bingo( int *grille, int N ) { // on teste les lignes, colonnes et diagonales
    int ok;
    for ( int i = 0; i < N; i++ ) {
        ok = 1;
        for ( int j = 0; j < N; j++ ) {
            if ( grille[N * i + j] != -1 ) {
                ok = 0;
            }
        }
        if ( ok == 1 ) {
            return ( 1 );
        }
    }
    for ( int i = 0; i < N; i++ ) {
        ok = 1;
        for ( int j = 0; j < N; j++ ) {
            if ( grille[N * j + i] != -1 ) {
                ok = 0;
            }
        }
        if ( ok == 1 ) {
            return ( 1 );
        }
    }
    ok = 1;
    for ( int i = 0; i < N; i++ ) {
        if ( grille[( N + 1 ) * i] != -1 ) {
            ok = 0;
        }
    }
    if ( ok == 1 ) {
        return ( 1 );
    }
    ok = 1;
    for ( int i = 0; i < 3; i++ ) {
        if ( grille[( N - 1 ) * ( i + 1 )] != -1 ) {
            ok = 0;
        }
    }
    if ( ok == 1 ) {
        return ( 1 );
    }
    return ( 0 );
}

int main( int argc, char *argv[] ) {
    FILE *file = fopen( argv[1], "r" );
    if ( file == NULL ) {
        printf( "Fichier illisible" );
        fclose( file );
    }
    int N;
    fscanf( file, "%d", &N );

    int *grille = malloc(
        N * N * sizeof( int ) ); // definition de la grille avant remplissage
    int valeur;
    for ( int i = 0; i < N * N; i++ ) {
        fscanf( file, "%d", &valeur );
        grille[i] = valeur;
    }

    int tours = 0; // remplissage des cases
    while ( fscanf( file, "%d", &valeur ) != -1 ) {
        tours++;
        for ( int i = 0; i < N * N; i++ ) {
            if ( grille[i] == valeur ) {
                grille[i] = -1;
            }
        }
        if ( bingo( grille, N ) == 1 ) {
            printf( "Bingo %d\n", tours );
            return ( 0 );
        }
    }
    printf( "Ko\n" );
}
