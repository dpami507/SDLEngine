#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#undef ERROR
#include "Tracked.h"

enum DebugColor
{
	WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	MAGENTA = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};
const DebugColor DEFAULT_COLOR = WHITE;

class DebugStream
{
public:
	DebugStream(std::string prefix, DebugColor color)
		: mPrefix(prefix), mColor(color), mMoved(false) {
	}
	DebugStream(DebugStream&& other) noexcept
		: mBuffer(std::move(other.mBuffer)),
		mColor(other.mColor),
		mPrefix(std::move(other.mPrefix)),
		mMoved(false) {
		other.mMoved = true;
	}

	DebugStream(const DebugStream&) = delete;
	DebugStream& operator=(const DebugStream&) = delete;

	//Add things to the buffer
	template<typename T>
	DebugStream& operator<<(const T& val)
	{
		mBuffer << val;
		return *this;
	}

	~DebugStream();

private:
	std::ostringstream mBuffer;
	DebugColor mColor;
	std::string mPrefix;
	bool mMoved;
};

class Debug : public Tracked
{
public:

	static Debug* createInstance();
	static Debug* instnace();
	static void removeInstance();

	static DebugStream log(DebugColor color = WHITE, std::string prefix = "[LOG]");
	static DebugStream warning();
	static DebugStream error();

private:
	Debug();
	~Debug();

	static Debug* mpsInstance;
};