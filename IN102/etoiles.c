#include <stdio.h>
int main() {
    int n = 20;
    int k = 9;
    int m = 7;
    for ( int j = 1; j <= m; ++j ) {
        for ( int i = 1; i < j + k; ++i ) {
            if ( i < k ) {
                printf( " " );
            } else {
                printf( "*" );
            }
        }
        printf( "\n" );
    }
}