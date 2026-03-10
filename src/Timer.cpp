#include "Timer.h"

Timer::Timer()
{
	mTimeElapsed = 0;
	mStartTime = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
}

void Timer::start()
{
	//Reset variables
	mTimeElapsed = 0;
	mStartTime = std::chrono::steady_clock::now(); // Get current time
}
void Timer::sleepUnitlElapsed(double ms)
{
	//Get milliseconds as a duration 
	std::chrono::duration<double, std::milli> msAsDuration = (std::chrono::duration<double, std::milli>)ms;
	
	//Get the endtime 
	auto endTime = mStartTime + msAsDuration;

	//Sleep until the endtime
	std::this_thread::sleep_until(endTime);

	//Get the time elapsed
	mTimeElapsed = std::chrono::duration<double, std::milli>(endTime - mStartTime).count();
}
double Timer::getElapsedTime()
{
	//Get the time elapsed
	auto currentTime = std::chrono::steady_clock::now();
	mTimeElapsed = std::chrono::duration<double, std::milli>(currentTime - mStartTime).count();

	return mTimeElapsed;
}