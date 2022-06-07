#include <time.h>


static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() 
{
	return ticks;
}

int seconds_elapsed()
{
	return ticks / 18;
}


int milis_elapsed()
{
	return ticks * 5000 / 91;
}

void wait(uint64_t timeout)
{
    if ( timeout != 0 )
    {
        uint64_t start = milis_elapsed(); 
        while ( (milis_elapsed() - start) < timeout );
    }

}