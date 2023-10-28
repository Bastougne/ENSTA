#include <stdio.h>
#include <stdlib.h>

void main( int argc, char *argv[] ) {
    int x = atoi( argv[1] );
    int y = atoi( argv[2] );
    int z = atoi( argv[3] );
    printf( "%d\n", x + y + z );
}