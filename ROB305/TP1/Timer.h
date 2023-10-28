/* -------------------------------------------------------------------------------------------------------------------
 * Timer.h
 * Author: Shebli ANVAR
 * ---------------------------------------------------------------------------------------------------------------- */

#ifndef Timer_h_INCLUDED
#define Timer_h_INCLUDED

#include <time.h>
#include <signal.h>

class Timer
{
public:
    Timer();
    virtual ~Timer();
    void start(int period_ms);
    void stop();

protected:
    virtual void callback() = 0;

private:
    static void call_callback(int sig, siginfo_t* si, void*);

private:
    timer_t tid;
};

#endif
