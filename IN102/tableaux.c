#include <stdio.h>

void affichage( int *X, int n ) {
    for ( int i = 0; i < n - 1; i++ ) {
        printf( "%d,", X[i] );
    }
    printf( "%d\n", X[n - 1] );
}

int compter_nombre( int *X, int n, int y ) {
    int compteur = 0;
    for ( int i = 0; i < n; i++ ) {
        if ( X[i] == y ) {
            compteur++;
        }
    }
    return ( compteur );
}

int trouver_max( int *X, int m ) {
    int max = X[0];
    for ( int i = 1; i < m; i++ ) {
        if ( max < X[i] ) {
            max = X[i];
        }
    }
    return ( max );
}

int max_idx( int *X, int m, int *imax ) {
    int max = X[0];
    *imax = 0;
    for ( int i = 1; i < m; i++ ) {
        if ( max < X[i] ) {
            max = X[i];
            *imax = i;
        }
    }
    return ( max );
}

void main() {
    int n = 20;
    int T[n];
    T[0] = 3;
    for ( int i = 1; i < n; i++ ) {
        if ( T[i - 1] % 2 == 0 ) {
            T[i] = T[i - 1] / 2;
        } else {
            T[i] = 3 * T[i - 1] + 1;
        }
    }
    // affichage( T, n );
    // printf("%d\n", compter_nombre( T, n, 1 ) );
    // printf("%d\n", trouver_max( T, n ) );
    int imax = 0;
    int max = max_idx( T, n, &imax );
    printf( "%d, %d\n", max, imax );
}