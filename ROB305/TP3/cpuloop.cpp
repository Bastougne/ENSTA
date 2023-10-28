#include "cpuloop.h"
#include <iostream>

CpuLoop::CpuLoop( Calibrator &calibrator_ ) : calibrator( calibrator_ ) {}

void CpuLoop::runTime( double duration_ms )
{
	double nLoops = calibrator.nLoops( duration_ms );
	runLoop( nLoops );
}
