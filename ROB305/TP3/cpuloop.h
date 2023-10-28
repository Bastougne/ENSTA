#ifndef CPULOOP_H
#define CPULOOP_H

#include "calibrator.h"

class CpuLoop 
  : public Looper
{
private:
	Calibrator calibrator;

public:
	CpuLoop(Calibrator& calibrator);
	void runTime(double duration_ms);
  
};

#endif
