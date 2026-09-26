#pragma once
#include "Tracked.h"

#include <chrono>

/* Timer - high accuracy timer - uses Large Integer to prevent rollover

Dean Lawson
Champlain College
2011

Updated to use std::chrono - 2026
*/

class Timer :public Tracked
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    double getElapsedTime() const;//returns how much time has elapsed since start
    void sleepUntilElapsed(double ms);
    void sleep(double ms);
    void pause(bool shouldPause);
    inline double getFactor() const { return mFactor; };
    inline double getStartTime() const { return mStartTime; };
    inline void multFactor(double mult) { mLastFactor = mFactor; mFactor *= mult; };
    inline void setFactor(double theFactor) { mLastFactor = mFactor; mFactor = theFactor; };
    inline void restoreLastFactor() { mFactor = mLastFactor; };

private:
    long long mStartTime = 0;
    long long mEndTime = 0;
    double mElapsedTime;
    double mFactor;
    double mLastFactor;
    bool mPaused;

    //helper function
    double calcDifferenceInMS(long long from, long long to) const;



};