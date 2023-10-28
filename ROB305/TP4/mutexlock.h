#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "mutexmonitor.h"

class Mutex::Lock : public Monitor
{
  public:
	Lock( Mutex &m );

	Lock( Mutex &m, double timeout_ms );

	~Lock();
};

#endif
