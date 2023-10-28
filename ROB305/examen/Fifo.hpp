/*
 * Fifo.hpp
 *
 *  Created on: Nov 17, 2015
 *      Author: anvar
 */

#ifndef Fifo_hpp_INCLUDED
#define Fifo_hpp_INCLUDED

#include <queue>
#include <exception>

template <typename T>
class Fifo
{
public:
	void push(const T& element);
	T pop();

private:
	Mutex notEmpty;
	std::queue<T> elements;
};

template <typename T>
void Fifo<T>::push(const T& element)
{
	Mutex::Lock l(notEmpty);
	elements.push(element);
	l.notify();
}

template <typename T>
T Fifo<T>::pop()
{
	Mutex::Lock l(notEmpty);
	while (elements.empty())
	{
		l.wait();
	}
	T returnValue = elements.front();
	elements.pop();
	return returnValue;
}

#endif /* Fifo_hpp_INCLUDED */
