#ifndef POSIXTHREAD_H
#define POSIXTHREAD_H

#include "../TP1/timespec.h"

#include <pthread.h>

using Callback = void *(*)( void * );

class PosixThread
{
  public:
	class Exception;

  private:
	pthread_t posixId;
	pthread_attr_t posixAttr;

  protected:
	bool isActive;

  public:
	PosixThread();

	PosixThread( pthread_t posixId );

	~PosixThread();

	void start( Callback threadFunc, void *threadArg );

	bool join();

	bool join( double timeout_ms );

	bool setScheduling( int p_schedPolicy, int priority );

	bool getScheduling( int *p_schedPolicy = nullptr, int *priority = nullptr );
};

#endif
