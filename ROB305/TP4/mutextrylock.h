#ifndef MUTEXTRYLOCK_H
#define MUTEXTRYLOCK_H

#include "mutexmonitor.h"

class Mutex::TryLock : public Monitor
{
  public:
	TryLock( Mutex &m ) throw( TimeoutException );

	~TryLock();
};

#endif
