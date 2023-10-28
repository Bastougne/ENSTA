#ifndef CHRONO_H
#define CHRONO_H

#include "../TP1/timespec.h"

class Chrono
{
  private:
	timespec startTime_, stopTime_;

  public:
	Chrono();

	void stop();

	void restart();

	bool isActive();

	double startTime();

	double stopTime();

	double lap();
};

#endif
