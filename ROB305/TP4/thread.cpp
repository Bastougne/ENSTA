#include "thread.h"

Thread::Thread() {}

Thread::~Thread() {}

bool Thread::start()
{
	if ( !started ) {
		startTime = timespec_now();
		PosixThread::start( call_run, (void *)this );
		stopTime = timespec_now();
		started = true;
	}

	return started;
}

void *Thread::call_run( void *v_thread )
{
	Thread *thread = (Thread *)v_thread;
	thread->run();
	return (void *)thread;
}

double Thread::sleep_ms( double delay_ms )
{
	return timespec_to_ms( timespec_wait( timespec_from_ms( delay_ms ) ) );
}

double Thread::startTime_ms() { return timespec_to_ms( startTime ); }

double Thread::stopTime_ms() { return timespec_to_ms( stopTime ); }

double Thread::execTime_ms() { return timespec_to_ms( stopTime - startTime ); }
