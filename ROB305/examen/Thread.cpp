/* -------------------------------------------------------------------------------------------------------------------
 * Thread.cpp
 * Author: Shebli ANVAR
 * ---------------------------------------------------------------------------------------------------------------- */


#include "Thread.h"

Thread::Thread() : posixThread(INVALID_ID)
{
	pthread_attr_init(&posixThreadAttribute);
}

Thread::~Thread()
{
	pthread_attr_destroy(&posixThreadAttribute);
	join();
}

void Thread::resetSelfScheduligPolicy(SchedulingPolicy schedPolicy, int priority)
{
	auto posixSchedParam = normalizeSchedParam(priority, schedPolicy);
	pthread_setschedparam(pthread_self(), schedPolicy, &posixSchedParam);
}

struct sched_param Thread::normalizeSchedParam(int priority, SchedulingPolicy schedPolicy)
{
	auto minPrio = sched_get_priority_min(schedPolicy);
	auto maxPrio = sched_get_priority_max(schedPolicy);
	if (priority < minPrio) priority = minPrio;
	if (priority > maxPrio) priority = maxPrio;

	struct sched_param posixSchedParam;
	posixSchedParam.sched_priority = priority;

	return posixSchedParam;
}

struct sched_param Thread::normalizeSchedParam(int priority)
{
	struct sched_param posixSchedParam;
	SchedulingPolicy policy;

	pthread_getschedparam(pthread_self(), &policy, &posixSchedParam);

	return normalizeSchedParam(posixSchedParam.sched_priority, policy);
}

bool Thread::start(int priority)
{
	Mutex::Lock l(startMutex);

	if (posixThread != INVALID_ID)
		return false;

	auto schedParam = normalizeSchedParam(priority);
	pthread_attr_setschedparam(&posixThreadAttribute, &schedParam);
	pthread_create(&posixThread, &posixThreadAttribute, call_run, this);
	return true;
}

void Thread::join()
{
	pthread_join(posixThread, nullptr);
}

void* Thread::call_run(void* v_thr)
{
	Thread* thr = (Thread*) v_thr;
	thr->run();
	thr->posixThread = INVALID_ID; // end of thread is imminent
	return v_thr;
}
