#include "mutexmonitor.h"
#include "../TP1/timespec.h"

Mutex::Monitor::Monitor( Mutex &m ) : Monitor( m ) {}

void Mutex::Monitor::notify() { pthread_cond_signal( &m.posixCondId ); }

void Mutex::Monitor::notifyAll() { pthread_cond_broadcast( &m.posixCondId ); }

bool Mutex::Monitor::wait( double timeout_ms )
{
	timespec timeout_tspec =
		( timespec_now() ) + timespec_from_ms( timeout_ms );

	bool ret =
		pthread_cond_timedwait( &m.posixCondId, &m.posixId, &timeout_tspec );

	return (bool)ret;
}

void Mutex::Monitor::wait() { pthread_cond_wait( &m.posixCondId, &m.posixId ); }
