/* -------------------------------------------------------------------------------------------------------------------
 * Thread.h
 * Author: Shebli ANVAR
 * ---------------------------------------------------------------------------------------------------------------- */

#ifndef Thread_h_INCLUDED
#define Thread_h_INCLUDED

#include "Mutex.h"
#include <pthread.h>

class Thread
{
public:
	using SchedulingPolicy = int;
	static const SchedulingPolicy NonRt = SCHED_OTHER;
	static const SchedulingPolicy RtRoundRobin = SCHED_RR;
	static const SchedulingPolicy RtFifo = SCHED_FIFO;
	static const pthread_t INVALID_ID{0};

public:
	Thread();
	virtual ~Thread();

	// Sets global scheduling policy (choose between NonRt, RtRoundRobin and RtFifo), priority set to max valu by default.
	static void resetSelfScheduligPolicy(SchedulingPolicy schedPolicy = NonRt, int priority = 0);

	// Start this Thread with specified priority. If set to 0, priority will be set to maximum value.
	bool start(int priority = 0);

	// Block until Thread execution is over.
	void join();

protected:
	virtual void run() = 0;

private:
	// Normalize priority according to scheduling policy
	static struct sched_param normalizeSchedParam(int priority, SchedulingPolicy schedPolicy);

	// Normalize priority according to calling thread's scheduling policy
	static struct sched_param normalizeSchedParam(int priority);

	// Call thread's main loop implemented in virtuel operation run()
	static void* call_run(void* v_thr);

private:
	Mutex startMutex;
	pthread_t posixThread;
	pthread_attr_t posixThreadAttribute;
};

#endif /* Thread_h_INCLUDED */
