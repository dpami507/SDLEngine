#pragma once
#include <SDL3/SDL_timer.h>

#include "Tracked.h"
#include "Debug.h"

class Timer : public Tracked
{
public:
	Timer();
	~Timer();

	void start();
	void sleepUnitlElapsed(double ms);
	double getElapsedTime();

private:
	UINT64 mStartTime; //Start time
	const float PERFORMANCE_FREQ = SDL_GetPerformanceFrequency();
};