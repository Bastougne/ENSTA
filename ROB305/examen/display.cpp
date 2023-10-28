#include "display.h"

#include <iostream>

Display::Display( int init_count ) { count = init_count; }

Display::~Display() {}

void Display::callback()
{
	std::cout << --count << std::endl;

	if ( count <= 0 )
		stop();
}

int Display::get_counter() { return count; }
