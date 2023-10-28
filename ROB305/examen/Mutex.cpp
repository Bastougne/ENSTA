/* -------------------------------------------------------------------------------------------------------------------
 * Mutex.cpp
 * Author: Shebli ANVAR
 * ---------------------------------------------------------------------------------------------------------------- */

#include "Mutex.h"

Mutex::Mutex(bool isInversionSafe)
{
	// Initialize Posix mutex attribute
	pthread_mutexattr_t posixMutexAttr;
	pthread_mutexattr_init(&posixMutexAttr);
	pthread_mutexattr_settype(&posixMutexAttr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutexattr_setprotocol(&posixMutexAttr, isInversionSafe ? PTHREAD_PRIO_INHERIT : PTHREAD_PRIO_NONE);

	// Initialize Posix mutex and discard mutex attribute
	pthread_mutex_init(&posixMutex, &posixMutexAttr);
	pthread_mutexattr_destroy(&posixMutexAttr);

	// Initialize Posix condition
	pthread_cond_init(&posixCondition, nullptr);
}

Mutex::~Mutex()
{
	// Destroy Posix mutex and condition
	pthread_mutex_destroy(&posixMutex);
	pthread_cond_destroy(&posixCondition);
}

void Mutex::lock()
{
	auto status = pthread_mutex_lock(&posixMutex);
	std::string errorMessage("Mutex::lock failed: ");
	switch (status)
	{
		case EINVAL:
			errorMessage += "Uninitialized Posix mutex ID";
			break;

		case EAGAIN:
			errorMessage += "Maximum recursive Mutex locks exceeded";
			break;

		default:
			errorMessage += "Unknown error";
			break;
	}
}

void Mutex::unlock()
{
	auto status = pthread_mutex_unlock(&posixMutex);
	std::string errorMessage("Mutex::unlock failed: ");
	switch (status)
	{
		case EINVAL:
			errorMessage += "Uninitialized Posix mutex ID";
			break;

		case EAGAIN:
			errorMessage += "Maximum recursive Mutex locks exceeded";
			break;

		case EPERM:
			errorMessage += "Calling thread does not own the Mutex";
			break;

		default:
			errorMessage += "Unknown error";
			break;
	}
}
