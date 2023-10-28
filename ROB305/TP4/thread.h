#ifndef THREAD_H
#define THREAD_H

#include "posixthread.h"

class Thread : public PosixThread
{
  private:
	timespec startTime;
	timespec stopTime;

	bool started = false;

  public:
	Thread();

	~Thread();

	bool start();

  protected:
	virtual void run() = 0;

  private:
	static void *call_run( void *v_thread );

  public:
	static double sleep_ms( double delay_ms );

	double startTime_ms();

	double stopTime_ms();

	double execTime_ms();
};

#endif
