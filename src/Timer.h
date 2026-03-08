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
	void sleepUnitlElapsed(double ms);

	double getElapsedTime() { return mTimeElapsed; }

private:
	double mTimeElapsed;
	std::chrono::steady_clock::time_point mStartTime;
};