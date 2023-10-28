/* -------------------------------------------------------------------------------------------------------------------
 * Mutex.h
 * Author: Shebli ANVAR
 * This class integrates both mutex and condition functionalities
 * ---------------------------------------------------------------------------------------------------------------- */

#ifndef Mutex_h_INCLUDED
#define Mutex_h_INCLUDED

#include <pthread.h>
#include <exception>
#include <string>

class Mutex
{
public:
	struct Exception : public std::exception
	{
		Exception(std::string descript) : descript(descript)
		{
		}

		const char* what() const noexcept override
		{
			return descript.c_str();
		}

	private:
		std::string descript;
	};

	class Lock
	{
	public:
		// Constructor locks the specified Mutex.
		Lock(Mutex& mutex) : mutex(mutex) { mutex.lock(); }

		// Destructor unlocks the associated Mutex.
		~Lock() { mutex.unlock(); }

		// Condition operations
		void wait() { pthread_cond_wait(&mutex.posixCondition, &mutex.posixMutex); }
		void notify() { pthread_cond_signal(&mutex.posixCondition); }
		void notifyAll() { pthread_cond_broadcast(&mutex.posixCondition); }

	private:
		// Forbid dynamic allocation of Lock: the point is to use only automatic stack allocation.
		void* operator new  (size_t) throw() = delete;

	private:
		// Reference to associated resource Mutex.
		Mutex& mutex;

	};

public:
	// Initializes this Mutex; parameter specifies if Mutex must be inversion-safe.
	Mutex(bool isInversionSafe = false);

	// Destroys Mutex.
	virtual ~Mutex();

	// Lock Mutex. Although public, this operation is best used through a Lock object constructor.
	void lock();

	// Unlocks Mutex. Although public, this operation is best used through a Lock object destructor.
	void unlock();

protected:
	// Posix ID of the Mutex.
	pthread_mutex_t posixMutex;
	pthread_cond_t posixCondition;
};

#endif /* Mutex_h_INCLUDED */
