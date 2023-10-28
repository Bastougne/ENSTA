#ifndef MUTEXMONITOR_H
#define MUTEXMONITOR_H

#include "mutex.h"
#include <exception>

class Mutex::Monitor
{
  protected:
	class TimeoutException : std::exception
	{
	  public:
		const char *error();
	};

  private:
	Mutex &m;

  protected:
	Monitor( Mutex &m );

  public:
	void wait();

	bool wait( double timeout_ms );

	void notify();

	void notifyAll();
};

#endif
