#ifndef display_h_INCLUDED
#define display_h_INCLUDED

#include "Timer.h"

class Display : public Timer
{
  public:
	volatile int count;

  public:
	Display( int init_count );

	~Display();

	void callback() override;

	int get_counter();
};

#endif
