#include "DeltaTime.h"

void DeltaTime::start()
{
	mLastTime = std::chrono::steady_clock::now();
}
void DeltaTime::update()
{
	auto current = std::chrono::steady_clock::now();
	mDeltaTime = std::chrono::duration<double>(current - mLastTime).count();
	mLastTime = current;
}