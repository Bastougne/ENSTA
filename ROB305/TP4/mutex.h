#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>

class Mutex
{
  public:
	class Lock;
	class TryLock;
	class Monitor;

  private:
	pthread_mutex_t posixId;
	pthread_cond_t posixCondId;

  public:
	Mutex();

	~Mutex();

  private:
	void lock();

	bool lock( double timeout_ms );

	bool trylock();

	void unlock();
};

#endif
