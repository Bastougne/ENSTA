#include "posixthread.h"
#include "../TP1/timespec.h"

PosixThread::PosixThread()
{
	pthread_attr_init( &posixAttr );
	pthread_attr_setinheritsched( &posixAttr, PTHREAD_EXPLICIT_SCHED );
	pthread_attr_setschedpolicy( &posixAttr, SCHED_OTHER );
}

PosixThread::PosixThread( pthread_t posixId )
{
	this->posixId = posixId;
	PosixThread();
}

PosixThread::~PosixThread() { pthread_attr_destroy( &posixAttr ); }

void PosixThread::start( Callback threadFunc, void *threadArg )
{
	pthread_create( &posixId, &posixAttr, threadFunc, (void *)&threadArg );
}

bool PosixThread::join() { return pthread_join( posixId, nullptr ); }

bool PosixThread::join( double timeout_ms )
{
	timespec timeout_ts = timespec_from_ms( timeout_ms );
	return pthread_timedjoin_np( posixId, nullptr, &timeout_ts );
}

bool PosixThread::setScheduling( int p_schedPolicy, int priority )
{
	struct sched_param p_schedParam {
		priority
	};
	pthread_setschedparam( posixId, p_schedPolicy, &p_schedParam );
	return true;
}

bool PosixThread::getScheduling( int *p_schedPolicy = nullptr,
								 int *priority = nullptr )
{
	struct sched_param p_schedParam;
	pthread_getschedparam( posixId, p_schedPolicy, &p_schedParam );
	*priority = p_schedParam.sched_priority;
	return true;
}
