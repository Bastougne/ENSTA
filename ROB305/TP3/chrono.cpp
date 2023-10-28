#include "chrono.h"

Chrono::Chrono()
{
	clock_gettime( CLOCK_REALTIME, &startTime_ );
	stopTime_ = startTime_;
}

void Chrono::stop() { clock_gettime( CLOCK_REALTIME, &stopTime_ ); }

void Chrono::restart()
{
	clock_gettime( CLOCK_REALTIME, &startTime_ );
	stopTime_ = startTime_;
}

// Ce n'est que lorsqu'on arrête le chrono qu'on a stopTime_ != startTime_
bool Chrono::isActive() { return stopTime_ == startTime_; }

double Chrono::startTime() { return timespec_to_ms( startTime_ ); }

double Chrono::stopTime() { return timespec_to_ms( stopTime_ ); }

double Chrono::lap() { return timespec_to_ms( stopTime_ - startTime_ ); }
