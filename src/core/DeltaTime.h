#pragma once
#include <chrono>

namespace engine::time
{
	class DeltaTime
	{
	public:
		DeltaTime() = default;
		~DeltaTime() = default;

		void start();
		void update();
		inline double get() { return mDeltaTime; }
	private:
		std::chrono::steady_clock::time_point mLastTime;
		double mDeltaTime = 0;
	};
}