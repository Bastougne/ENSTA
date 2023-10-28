#include <stdio.h>
#include <stdlib.h>

void nth( char *str, int index ) { printf( "%c\n", str[index] ); }

int main() {
	char str[64];
	int pos;

	printf( "Chaîne et position ? : " );
	scanf( "%s %d", str, &pos );
	nth( str, pos );
	return 0;
}
