#include "fifo.h"

template <class T> Fifo<T>::Fifo() { mutex = Mutex(); }

template <class T> Fifo<T>::~Fifo() {}

template <class T> void Fifo<T>::push( T element )
{
	Mutex::Lock lock( mutex );
	elements.push( element );
	lock.notify();
}

template <class T> T Fifo<T>::pop()
{
	T element;
	Mutex::Lock lock( mutex );

	while ( elements.empty() )
		lock.wait();

	element = elements.front();
	elements.pop();

	return element;
}

template <class T> T Fifo<T>::pop( double timeout_ms )
{
	T element;
	Mutex::Lock lock( mutex );

	while ( elements.empty() )
		if ( lock.wait( timeout_ms ) )
			throw Fifo<T>::EmptyException();

	element = elements.front();
	elements.pop();

	return element;
}
