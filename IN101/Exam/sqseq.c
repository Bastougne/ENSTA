#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fonction recursive

int prochain_carre( char *val, char *chaine ) {
    int puissance = 0;
    int tempo = atoi( chaine );
    while ( tempo != 0 ) {
        tempo = tempo / 10;
        puissance++;
    }
    tempo = atoi( val ) * atoi( val );
    while ( tempo != 0 ) {
        tempo = tempo / 10;
        puissance--;
    }
    int comparer = atoi( chaine );
    for ( int i = 0; i < puissance; i++ ) {
        comparer = comparer / 10;
    }
    printf( "%d   %d\n", comparer, atoi( val ) * atoi( val ) );
    if ( comparer = atoi( val ) * atoi( val ) ) {
                return( prochain_carre( comparer,
    } else {
        return ( 0 );
    }
}

void main( int argc, char *argv[] ) {
    if ( prochain_carre( "2", "123" ) == 1 ) {
        printf( "Ok" );
    } else {
        printf( "Ko" );
    }
}
