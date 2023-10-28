#ifndef TIMER_H
#define TIMER_H

#include "../TP1/timespec.h"

class Timer
{
  protected:
	timer_t tid;

  public:
	Timer();

	virtual ~Timer();

	void start( double duration_ms );

	void stop();

  protected:
	virtual void callback() = 0;

  private:
	static void call_callback( int sig, siginfo_t *si, void * );
};

#endif
