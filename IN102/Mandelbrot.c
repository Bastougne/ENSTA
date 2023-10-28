#include <stdio.h>

int compter_iteration( double x, double y, int max_iter ) {
    double a = 0;
    double b = 0;
    double c = 0;
    int n = 0;
    while ( a * a + b * b <= 2 && n < max_iter ) {
        c = a * b;
        a = a * a - b * b + x;
        b = 2 * c + y;
        n = n + 1;
    }
    return ( n );
}

int main() {
    double x = 0;
    double y = 0.75;
    int max_iter = 100;
    int n = compter_iteration( x, y, max_iter );
    printf( "%d", n );
    return ( 0 );
}