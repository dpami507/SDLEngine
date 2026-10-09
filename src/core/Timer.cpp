#include "Timer.h"
#include <thread>

using namespace engine::time;

Timer::Timer() :mElapsedTime(0.0), mPaused(true), mFactor(1.0), mLastFactor(1.0)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    mStartTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    //reset end time as well
    mEndTime = 0;

    mElapsedTime = 0.0;

    pause(false);//unpause
}

void Timer::stop()
{
    mEndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    mElapsedTime = calcDifferenceInMS(mStartTime, mEndTime);
}

void Timer::pause(bool shouldPause)
{
    if (shouldPause && !mPaused)//want to pause and we are not currently paused
    {
        mPaused = true;
        mEndTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        mElapsedTime += calcDifferenceInMS(mStartTime, mEndTime);
    }
    else if (!shouldPause && mPaused)//want to unpause and we are paused
    {
        mPaused = false;
        mStartTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}

double Timer::getElapsedTime() const
{
    //if we have an end time then the timer isn't running and we can just return the elapsed time
    if (mEndTime != 0)
    {
        return mElapsedTime;
    }
    else //otherwise we need to get the current time, do the math and return that
    {
        long long currentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        
        return calcDifferenceInMS(mStartTime, currentTime);
    }
}

void Timer::sleepUntilElapsed(double ms)
{
    long long currentTime, lastTime;
    currentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    double timeToSleep = ms - calcDifferenceInMS(mStartTime, currentTime);

    while (timeToSleep > 0.0)
    {
        lastTime = currentTime;
        currentTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        double timeElapsed = calcDifferenceInMS(lastTime, currentTime);
        timeToSleep -= timeElapsed;
        if (timeToSleep > 2.0)//if we are going to be in this loop for a long time - 
        {                                               //Sleep to relinquish back to the operating system
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
}

void Timer::sleep(double ms)
{
    auto savedTime = mStartTime;

    mStartTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


    sleepUntilElapsed(ms);

    mStartTime = savedTime;
}

double Timer::calcDifferenceInMS(long long from, long long to) const
{
    double difference = (double)(to - from);
    difference *= mFactor;
    return difference / 1e6;
}