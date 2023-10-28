#include "semaphore.h"
#include "mutexlock.h"

Semaphore::Semaphore( unsigned int initCount, unsigned maxCount )
{
	counter = initCount <= maxCount ? initCount : maxCount;
	maxCounter = maxCount;
}

void Semaphore::give()
{
	Mutex::Lock Lock( m );

	if ( counter < maxCounter ) {
		++counter;
	}
}

void Semaphore::take()
{
	Mutex::Lock Lock( m );

	while ( counter == 0 ) {
		Lock.wait();
	}
	--counter;
}

unsigned int Semaphore::getCounter() { return counter; }

bool Semaphore::take( double timeout_ms )
{
	Mutex::Lock Lock( m );

	if ( counter == 0 )
		if ( !Lock.wait( timeout_ms ) )
			return false;

	--counter;
	return true;
}

Semaphore::~Semaphore() {}
