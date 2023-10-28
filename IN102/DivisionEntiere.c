#include <stdio.h>
int main() {
    int x = 7;
    int y = 22;
    int n = 5;
    int d = x % y;
    printf( "%d,\n", x / y );
    for ( int i = 1; i <= n; ++i ) {
        d = ( 10 * d ) / y;
        printf( "%d\n", d );
    }
}