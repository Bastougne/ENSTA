#include <stdio.h>
#include <stdlib.h>

void main( int argc, char *argv[] ) {
    double x = atof( argv[1] );
    double y = atof( argv[2] );
    double z = atof( argv[3] );
    double max = x;
    if ( y > max ) {
        max = y;
    }
    if ( z > max ) {
        max = z;
    }
    printf( "%lf\n", max );
}