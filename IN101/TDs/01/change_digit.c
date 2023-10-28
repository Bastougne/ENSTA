#include <stdbool.h>
#include <stdio.h>

bool change( char *str ) {
	char must_be;
	int start_at = 1;

	if ( str[0] == '-' ) {
		must_be = '0';
		start_at = 2;
	} else if ( str[0] == '+' ) {
		must_be = '9';
		start_at = 2;
	} else if ( str[1] == '\0' )
		return true;
	else
		must_be = '9'; /* start_at est déjà à 1 par initialisation. */

	while ( str[start_at] != '\0' ) {
		if ( str[start_at] != must_be )
			return false;
		start_at++;
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
