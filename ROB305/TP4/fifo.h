#ifndef FIFO_H
#define FIFO_H

#include "mutex.h"
#include <queue>

template <class T> class Fifo
{
  private:
	std::queue<T> elements;
	Mutex m;

  protected:
	class EmptyException : std::exception
	{
	  public:
		const char *msg() const noexcept;
	};

  public:
	Fifo();

	~Fifo();

	void push( T element );

	T pop();

	T pop( double timeout_ms );
};

#endif
