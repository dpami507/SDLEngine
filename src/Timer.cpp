#include "Timer.h"

Timer::Timer()
{
	start();
}

Timer::~Timer()
{
}

void Timer::start()
{
	mStartTime = SDL_GetPerformanceCounter();
}

void Timer::sleepUnitlElapsed(double ms)
{	
	//Get time to sleep
	double timeToSleep = (ms - getElapsedTime());

	//Sleep until the endtime
	if (timeToSleep > 0)
		SDL_Delay(timeToSleep);
}
double Timer::getElapsedTime()
{
	//Get the current time
	double now = SDL_GetPerformanceCounter();
	//Get the time elapsed in ms
	return (now - mStartTime) / PERFORMANCE_FREQ * 1000.0f;
}