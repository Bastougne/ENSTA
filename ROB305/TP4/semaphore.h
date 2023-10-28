#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "mutex.h"
#include<limits>

class Semaphore
{
  private:
	volatile unsigned int counter;
	unsigned int maxCounter;
	Mutex m;

  public:
	Semaphore(
		unsigned int counter = 0,
		unsigned int maxCount = std::numeric_limits<unsigned int>::max() );

	~Semaphore();

	void give();
	void take();
	bool take( double timeout_ms );

	unsigned int getCounter();
};

#endif
