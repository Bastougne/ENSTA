#include "calibrator.h"
#include <iostream>
#include <vector>

Calibrator::Calibrator( double samplingPeriod_ms, unsigned int nSamples )
	: pCounter( nSamples )
{
	std::cout << "Beginning of Calibrator" << std::endl;
	PeriodicTimer::start( samplingPeriod_ms );
	looper->runLoop();

	std::vector<double> times;
	for ( int i = 1; i <= nSamples; i++ ) {
		times.push_back( samplingPeriod_ms * i );
	}

	double ySum = 0;
	double xxSum = 0;
	double xSum = 0;
	double xySum = 0;

	for ( int i = 0; i < nSamples; i++ ) {
		ySum += samples[i];
		xSum += times[i];
		xxSum += times[i] * times[i];
		xySum += times[i] * samples[i];
	}
	a = ( nSamples * xySum - xSum * ySum ) / ( nSamples * xxSum - xSum * xSum );
	b = ( xxSum * ySum - xSum * xySum ) / ( nSamples * xxSum - xSum * xSum );
}

void Calibrator::callback()
{
	--pCounter;

	if ( pCounter == 0 ) {
		samples.push_back( looper->stopLoop() );
		stop();
	} else {
		samples.push_back( looper->getSample() );
	}
}

double Calibrator::nLoops( double duration_ms )
{
	return ( a * duration_ms + b );
}
