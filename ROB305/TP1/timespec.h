#ifndef TIMESPEC_H
#define TIMESPEC_H

#include <signal.h>
#include <time.h>


// a) Gestion simplifiée du temps Posix
double timespec_to_ms( const timespec &time_ts );
timespec timespec_from_ms( double time_ms );

timespec timespec_now();
timespec timespec_negate( const timespec &time_ts );

timespec timespec_add( const timespec &time1_ts, const timespec &time2_ts );
timespec timespec_sub( const timespec &time1_ts, const timespec &time2_ts );

timespec timespec_wait( const timespec &delay_ts );

timespec operator-( const timespec &time_ts );
timespec operator+( const timespec &time1_ts, const timespec &time2_ts );
timespec operator-( const timespec &time1_ts, const timespec &time2_ts );
timespec &operator+=( timespec &time_ts, const timespec &delay_ts );
timespec &operator-=( timespec &time_ts, const timespec &delay_ts );
bool operator==( const timespec &time1_ts, const timespec &time2_ts );
bool operator!=( const timespec &time1_ts, const timespec &time2_ts );
bool operator<( const timespec &time1_ts, const timespec &time2_ts );
bool operator>( const timespec &time1_ts, const timespec &time2_ts );

void timespec_tests();


// b)Timers avec callback
void handler( int sig, siginfo_t *si, void * );

void posix_timer_example();


// c) Fonction simple consommant du CPU

void incr( unsigned int nLoops, double *pCounter );

void incr_test( int argc, char **argv );


// d) Mesure du temps d’exécution d’une fonction
unsigned incr_v2( unsigned int nLoops, double *pCounter, bool *pStop );

#endif
