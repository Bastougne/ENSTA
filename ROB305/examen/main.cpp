#include "display.h"
#include <iostream>

int main()
{

	Display d( 5 );
	d.start( 500 );
	while ( d.count > 0 ) {
		continue;
	}

	return 0;
}
