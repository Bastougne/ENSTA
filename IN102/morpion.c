#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum joueur { vide, humain, ordi };

int *creer_grille() {
    int *grille = malloc( 9 * sizeof( int ) );
    for ( int i = 0; i < 9; i++ ) {
        grille[i] = 0;
    }
    return ( grille );
}

void afficher_grille( int *grille ) {
    char *val_case[3] = { ".", "X", "O" };
    for ( int i = 0; i < 3; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            printf( "%s", val_case[grille[3 * i + j]] );
        }
        printf( "\n" );
    }
    printf( "\n" );
}

void test_affichage() {
    int *grille = creer_grille();
    afficher_grille( grille );
    grille[4] = humain;
    grille[8] = ordi;
    afficher_grille( grille );
}

void placer( int *grille, int chiffre, int joueur ) {
    grille[chiffre - 1] = joueur;
}

void placer_alea( int *grille, int joueur ) {
    srand( time( 0 ) );
    int chiffre;
    do {
        chiffre = rand() % 9;
    } while ( grille[chiffre] != vide );
    grille[chiffre] = joueur;
}

int a_gagne( int *grille, int joueur ) {
    int ok;
    for ( int i = 0; i < 3; i++ ) {
        ok = 1;
        for ( int j = 0; j < 3; j++ ) {
            if ( grille[3 * i + j] != joueur ) {
                ok = 0;
            }
        }
        if ( ok == 1 ) {
            return ( 1 );
        }
    }
    for ( int i = 0; i < 3; i++ ) {
        ok = 1;
        for ( int j = 0; j < 3; j++ ) {
            if ( grille[3 * j + i] != joueur ) {
                ok = 0;
            }
        }
        if ( ok == 1 ) {
            return ( 1 );
        }
    }
    ok = 1;
    for ( int i = 0; i < 3; i++ ) {
        if ( grille[4 * i] != joueur ) {
            ok = 0;
        }
    }
    if ( ok == 1 ) {
        return ( 1 );
    }
    ok = 1;
    for ( int i = 0; i < 3; i++ ) {
        if ( grille[2 * i + 2] != joueur ) {
            ok = 0;
        }
    }
    if ( ok == 1 ) {
        return ( 1 );
    }
    return ( 0 );
}

void main() {
    int *grille = creer_grille();
    afficher_grille( grille );
    int victoire = 0;
    int tours = 0;
    while ( victoire == 0 ) {
        tours++;
        int c;
        printf( "Dans quelle case jouer ?    -> " );
        scanf( "%d", &c );
        placer( grille, c, humain );
        placer_alea( grille, ordi );
        afficher_grille( grille );
        if ( a_gagne( grille, humain ) == 1 ) {
            printf( "Vous avez gagné !\n" );
            victoire = 1;
        } else if ( a_gagne( grille, ordi ) == 1 ) {
            printf( "Vous avez perdu\n" );
            victoire = 2;
        }
        int plein = 1;
        for ( int j = 0; j < 9; j++ ) {
            if ( grille[j] == 0 ) {
                plein = 0;
            }
        }
        if ( plein == 1 ) {
            printf( "Match nul en %d tour(s)\n", tours );
            victoire = 3;
        }
    }
}