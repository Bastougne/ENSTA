#include <stdio.h>
#include <stdlib.h>

void nth( char *str, int index ) { printf( "%c\n", str[index] ); }

int main( int argc, char **argv ) {
	char *str = argv[1];
	int pos = atoi( argv[2] );

	nth( str, pos );
	return 0;
}
