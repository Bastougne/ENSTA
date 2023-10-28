#include "mutextrylock.h"

Mutex::TryLock::TryLock( Mutex &m ) : Mutex::Monitor( m )
{
	int ret = m.trylock();
	if ( ret != 0 ) {
		throw Mutex::Monitor::TimeoutException();
	}
}

Mutex::TryLock::~TryLock() {}
