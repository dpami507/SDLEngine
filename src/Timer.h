#include <SDL3/SDL_timer.h>
#include <thread>
#include <chrono>

#include "Tracked.h"
#include "Debug.h"

class Timer : public Tracked
{
public:
	Timer();
	~Timer();

	void start();
	void sleepUnitl(double ms);

	double getElapsedTime() { return mTimeElapsed; }

private:
	double mTimeElapsed;
	double mStartTime;
};