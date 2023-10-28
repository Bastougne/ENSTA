#include "countdown.h"

CountDown::CountDown( unsigned int init_val ) { n = init_val; }

void CountDown::start()
{
	PeriodicTimer::start( 1000 / 2 );
	while ( n > 0 ) {
	}
}

void CountDown::callback()
{
	std::cout << "counter = " << --n << std::endl << std::endl;

	if ( n <= 0 ) {
		stop();
	}
}
