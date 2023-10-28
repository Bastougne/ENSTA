#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <iostream>

#include "periodictimer.h"

class CountDown : public PeriodicTimer
{
  private:
	int n;

  public:
	CountDown( unsigned int init_val );

	void start();

	void callback();
};

#endif
