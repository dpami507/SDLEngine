#include "Timer.h"

Timer::Timer()
{
	mTimeElapsed = 0;
	mStartTime = 0;
}

Timer::~Timer()
{
}

void Timer::start()
{
	//Reset variables
	mTimeElapsed = 0;
	mStartTime = SDL_GetPerformanceCounter();
}
void Timer::sleepUnitl(double ms)
{
	double currentTime, lastTime;

	//Get current time
	currentTime = (double)SDL_GetPerformanceCounter();
	//How many ticks equal one second
	double freq = (double)SDL_GetPerformanceFrequency();
	//SDL_GetPerformanceCounter returns nanoseconds, multiply it by 1000 gets miliseconds
	mTimeElapsed = (currentTime - mStartTime) / freq * 1000;
	//Time to sleep
	double sleepTime = ms - mTimeElapsed;

	while (sleepTime > 0.0)
	{
		//Update last time
		lastTime = currentTime;
		//Get the curent time
		currentTime = (double)SDL_GetPerformanceCounter();
		//Get Time elapsed
		double timeElapsed = (currentTime - lastTime) / freq * 1000;
		//Lower sleep time
		sleepTime -= timeElapsed;
		//Sleep if we are gonna be here a while
		if (sleepTime > 10.0)
		{
			//Sleep
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	//Update Time Elapsed
	currentTime = (double)SDL_GetPerformanceCounter();
	mTimeElapsed = (currentTime - mStartTime) / freq * 1000;
}
