#include <stdio.h>
int main() {
    int reponse;
    printf( "Entrez 4 pour quitter: " );
    do {
        scanf( "%d", &reponse );
    } while ( reponse != 4 );
}