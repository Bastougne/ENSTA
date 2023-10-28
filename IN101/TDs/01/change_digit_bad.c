#include <stdbool.h>
#include <stdio.h>

bool change( char *str ) {
	if ( str[1] == '\0' )
		return true;
	for ( int i = 1; str[i] != '\0'; i++ ) {
		if ( str[i] != '9' )
			return false;
	}
	return true;
}

int main() {
	char str[64];

	printf( "Chaîne ? : " );
	scanf( "%s", str );
	printf( "%d\n", change( str ) );
	return 0;
}
