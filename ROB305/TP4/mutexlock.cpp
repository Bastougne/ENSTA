#include "mutexlock.h"


Mutex::Lock::Lock( Mutex &m ) : Mutex::Monitor::Monitor( m ) { m.lock(); }

Mutex::Lock::~Lock() {}

Mutex::Lock::Lock( Mutex &m, double timeout_ms ) : Mutex::Monitor::Monitor( m )
{
	int ret = m.lock( timeout_ms );

	if ( ret != 0 ) {
		throw Mutex::Monitor::TimeoutException();
	}
}
