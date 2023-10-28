#ifndef PERIODCTIMER_H
#define PERIODCTIMER_H

#include "timer.h"

class PeriodicTimer : public Timer
{
  public:
	void start( double duration_ms );
};

#endif
