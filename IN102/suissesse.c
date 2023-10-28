#include <stdio.h>

void afficher( char *ch ) {
    int i = 0;
    while ( ch[i] != '\0' ) {
        printf( "%c", ch[i] );
        i++;
    }
    printf( "\n" );
}

int compter_lettre( char *ch, char x ) {
    int i = 0;
    int compteur = 0;
    while ( ch[i] != '\0' ) {
        if ( ch[i] == x ) {
            compteur++;
        }
        i++;
    }
    return ( compteur );
}

int position( char *ch, char x ) {
    int i = 0;
    while ( ch[i] != '\0' && ch[i] != x ) {
        i++;
    }
    if ( ch[i] == '\0' ) {
        i = -1;
    }
    return ( i );
}

int position_chaine( char *ch, char *x ) {
    int i = 0;
    while ( ch[i] != '\0' ) {
        // on recommence à partir de i
        int k = 0;
        while ( ch[i + k] != '\0' && x[k] != '\0' && ch[i + k] == x[k] ) {
            k++;
        }
        if ( x[k] == '\0' ) {
            break;
        }
        i++;
    }

    if ( ch[i] == '\0' ) {
        i = -1;
    }
    return ( i );
}

void main() {
    char *M = "suissesse";
    // printf( "%s\n", M );
    // afficher( M );
    // printf( "%d\n", compter_lettre( M, 's' ) );
    // printf( "%d\n", position( M, 'x' ) );
    // printf( "%d\n", position_chaine( M,"ee" ) );
}