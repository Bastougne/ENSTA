#include "mutex.h"
#include "../TP1/timespec.h"

Mutex::Mutex()
{
	pthread_mutexattr_t mutexAttribute;
	pthread_mutexattr_init( &mutexAttribute );

	pthread_mutexattr_settype( &mutexAttribute, PTHREAD_MUTEX_RECURSIVE );

	pthread_mutex_t posixId;
	pthread_mutex_init( &posixId, &mutexAttribute );
	pthread_cond_init( &posixCondId, nullptr );
	pthread_mutexattr_destroy( &mutexAttribute );
}

Mutex::~Mutex()
{
	pthread_mutex_destroy( &posixId );
	pthread_cond_destroy( &posixCondId );
}

void Mutex::lock() { pthread_mutex_lock( &posixId ); }

void Mutex::unlock() { pthread_mutex_unlock( &posixId ); }

bool Mutex::lock( double timeout_ms )
{
	timespec timeout_ts = timespec_from_ms( timeout_ms ) + timespec_now();
	return pthread_cond_timedwait( &posixCondId, &posixId, &timeout_ts );
}

bool Mutex::trylock() { return pthread_mutex_trylock( &posixId ); }
