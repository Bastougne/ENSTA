#include <stdio.h>
#include <stdlib.h>

struct intervalle {
    double binf;
    double bsup;
};

void affichage( struct intervalle i ) {
    printf( "[%f,%f]\n", i.binf, i.bsup );
}

struct intervalle saisie_intervalle() {
    float a, b;
    scanf( "%f,%f", &a, &b );
    struct intervalle i = { a, b };
    return ( i );
}

struct intervalle intersection( struct intervalle i1, struct intervalle i2 ) {
    float a, b;
    if ( i1.binf > i2.binf ) {
        a = i1.binf;
    } else {
        a = i2.binf;
    }
    if ( i1.bsup > i2.bsup ) {
        b = i2.bsup;
    } else {
        b = i1.bsup;
    }
    struct intervalle i = { a, b };
    return ( i );
}

struct intervalle *saisie_tableau( int N ) {
    struct intervalle *T = malloc( N * sizeof( struct intervalle ) );
    for ( int k = 0; k < N; k++ ) {
        T[k] = saisie_intervalle();
    }
    return ( T );
}

struct intervalle intersection_tableau( struct intervalle *T, int N ) {
    struct intervalle i = T[0];
    for ( int k = 1; k < N; k++ ) {
        i = intersection( i, T[k] );
    }
    return ( i );
}

void affichage_tableau_inverse( struct intervalle *T, int N ) {
    for ( int k = N - 1; k >= 0; k-- ) {
        affichage( T[k] );
    }
}

void main() {
    int N = 3;
    struct intervalle *T = saisie_tableau( N );
    affichage( intersection_tableau( T, N ) );
    printf( "\n" );
    affichage_tableau_inverse( T, N );
    free( T );
}