#include "timespec.h"

#define SEC2MS 1000
#define MS2NS 1000000
#define SEC2NS SEC2MS *MS2NS

#include <iostream>

using namespace std;

// a) Gestion simplifiée du temps Posix

// Converts timespec to ms duration
double timespec_to_ms( const timespec &time_ts )
{
	return SEC2MS * time_ts.tv_sec + time_ts.tv_nsec / (double)MS2NS;
}

// Converts ms duration to normalised timespec
timespec timespec_from_ms( double time_ms )
{
	time_t sec = time_ms / SEC2MS;
	long nsec = MS2NS * ( time_ms - SEC2MS * sec );

	sec = ( nsec > 0 ) ? sec : sec - 1;
	nsec = ( nsec > 0 ) ? nsec : nsec + SEC2NS;

	sec = ( nsec < SEC2NS ) ? sec : sec + 1;
	nsec = ( nsec < SEC2NS ) ? nsec : nsec - SEC2NS;

	return { .tv_sec = sec, .tv_nsec = nsec };
}

// Gets timespec corresponding to current time
timespec timespec_now()
{
	double time_ms = time( 0 );

	return timespec_from_ms( time_ms );
}

// Returns the opposite of a timespec
timespec timespec_negate( const timespec &time_ts )
{
	double time_ms = timespec_to_ms( time_ts );

	return timespec_from_ms( -time_ms );
}

// Adds two timespecs
timespec timespec_add( const timespec &time1_ts, const timespec &time2_ts )
{
	double time1_ms = timespec_to_ms( time1_ts );
	double time2_ms = timespec_to_ms( time2_ts );

	return timespec_from_ms( time1_ms + time2_ms );
}

// Subtracts two timespecs
timespec timespec_sub( const timespec &time1_ts, const timespec &time2_ts )
{
	double time1_ms = timespec_to_ms( time1_ts );
	double time2_ms = timespec_to_ms( time2_ts );

	return timespec_from_ms( time1_ms - time2_ms );
}

// Waits for delay and returns remaining duration as a timespec
timespec timespec_wait( const timespec &delay_ts )
{
	timespec rem_ts;
	timespec zero{ .tv_sec = 0, .tv_nsec = 0 };

	int interrupt = nanosleep( &delay_ts, &rem_ts );
	return interrupt ? rem_ts : zero;
}

// Unary operator -
timespec operator-( const timespec &time_ts )
{
	return timespec_negate( time_ts );
}

// Operator +
timespec operator+( const timespec &time1_ts, const timespec &time2_ts )
{
	return timespec_add( time1_ts, time2_ts );
}

// Binary operator -
timespec operator-( const timespec &time1_ts, const timespec &time2_ts )
{
	return timespec_sub( time1_ts, time2_ts );
}

// Operator +=
timespec &operator+=( timespec &time_ts, const timespec &delay_ts )
{
	time_ts = timespec_add( time_ts, delay_ts );
	return time_ts;
}

// Operator -=
timespec &operator-=( timespec &time_ts, const timespec &delay_ts )
{
	time_ts = timespec_sub( time_ts, delay_ts );
	return time_ts;
}

// Operator ==
bool operator==( const timespec &time1_ts, const timespec &time2_ts )
{
	double time1_ms = timespec_to_ms( time1_ts );
	double time2_ms = timespec_to_ms( time2_ts );

	return time1_ms == time2_ms;
}

// Operator !=
bool operator!=( const timespec &time1_ts, const timespec &time2_ts )
{
	return !( time1_ts == time2_ts );
}

// Operator <
bool operator<( const timespec &time1_ts, const timespec &time2_ts )
{
	double time1_ms = timespec_to_ms( time1_ts );
	double time2_ms = timespec_to_ms( time2_ts );

	return time1_ms < time2_ms;
}

// Operator >
bool operator>( const timespec &time1_ts, const timespec &time2_ts )
{
	double time1_ms = timespec_to_ms( time1_ts );
	double time2_ms = timespec_to_ms( time2_ts );

	return time1_ms > time2_ms;
}

// Timespec tests
void timespec_tests()
{
	cout << "2300.3" << endl;
	timespec ts = timespec_from_ms( 2300.3 );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	double time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "wait" << endl;
	ts = timespec_wait( ts );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "-2300.3" << endl;
	ts = timespec_from_ms( -2300.3 );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "-2000.0" << endl;
	ts = timespec_from_ms( -2000.0 );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "now" << endl;
	timespec ts1 = timespec_now();
	cout << "tv_sec = " << ts1.tv_sec << ", tv_nsec = " << ts1.tv_nsec << endl;
	time_ms = timespec_to_ms( ts1 );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "negate now" << endl;
	timespec ts2 = timespec_negate( ts1 );
	cout << "tv_sec = " << ts2.tv_sec << ", tv_nsec = " << ts2.tv_nsec << endl;
	time_ms = timespec_to_ms( ts2 );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "now + negate now" << endl;
	ts = timespec_add( ts1, ts2 );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "now - now" << endl;
	ts = timespec_sub( ts1, ts1 );
	cout << "tv_sec = " << ts.tv_sec << ", tv_nsec = " << ts.tv_nsec << endl;
	time_ms = timespec_to_ms( ts );
	cout << "time_ms = " << time_ms << endl << endl;

	cout << "now == negate now" << endl;
	cout << ( ( ts1 == ts2 ) ? "True" : "False" ) << endl << endl;

	cout << "now != negate now" << endl;
	cout << ( ( ts1 != ts2 ) ? "True" : "False" ) << endl << endl;

	cout << "now > negate now" << endl;
	cout << ( ( ts1 > ts2 ) ? "True" : "False" ) << endl << endl;
}

// b) Timers avec callback

// Posix handler example
void handler( int sig, siginfo_t *si, void * )
{
	int *p_counter = (int *)( si->si_value.sival_ptr );
	( *p_counter )++;
	cout << "counter = " << *p_counter << endl << endl;
}

// Posix timer example
void posix_timer_example()
{
	volatile int counter = 0;

	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset( &sa.sa_mask );
	sigaction( SIGRTMIN, &sa, nullptr );

	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_value.sival_ptr = (void *)&counter;

	timer_t tid;
	timer_create( CLOCK_REALTIME, &sev, &tid );

	itimerspec its;
	its.it_value.tv_sec = 0;
	its.it_value.tv_nsec = SEC2NS / 2;
	its.it_interval = its.it_value;
	timer_settime( tid, 0, &its, nullptr );

	while ( counter < 15 ) {
	}

	timer_delete( tid );
}

// c) Fonction simple consommant du CPU

// dummy function
void incr( unsigned int nLoops, double *pCounter )
{
	for ( unsigned int i = 0; i < nLoops; ++i ) {
		*pCounter += 1.0;
	}
}

// dummy function test
void incr_test( int argc, char **argv )
{
	int nLoops = atoi( argv[1] );
	double counter = 0.0;
	timespec begin, end;

	clock_gettime( CLOCK_REALTIME, &begin );
	incr( nLoops, &counter );
	clock_gettime( CLOCK_REALTIME, &end );

	cout << "counter = " << counter << endl;
	cout << "ellapsed time = " << timespec_to_ms( end - begin ) << " ms\n\n";
}

// d) Mesure du temps d’exécution d’une fonction

// dummy function v2
unsigned incr_v2( unsigned int nLoops, double *pCounter, bool *pStop )
{
	unsigned int i;
	for ( i = 0; i < nLoops and not *pStop; ++i ) {
		*pCounter += 1.0;
	}
	return i;
}
