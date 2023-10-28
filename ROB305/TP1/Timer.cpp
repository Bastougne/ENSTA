/* -------------------------------------------------------------------------------------------------------------------
 * Timer.cpp
 * Author: Shebli ANVAR
 * ---------------------------------------------------------------------------------------------------------------- */

#include "Timer.h"

Timer::Timer()
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = call_callback;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGRTMIN, &sa, nullptr);

    struct sigevent sev;
    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = (void*) this;

    timer_create(CLOCK_REALTIME, &sev, &tid);
}

Timer::~Timer()
{
    timer_delete(tid);
}

void Timer::start(int period_ms)
{
    itimerspec its;
    its.it_value.tv_sec = period_ms / 1000;
    its.it_value.tv_nsec = (period_ms % 1000) * 1000000;
    its.it_interval = its.it_value;
}

void Timer::stop()
{
    itimerspec its;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = 0;
    its.it_interval = its.it_value;
}

void Timer::call_callback(int, siginfo_t* si, void*)
{
    Timer* timer = (Timer*) si->si_value.sival_ptr;
    timer->callback();
}
