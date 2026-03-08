#include "Debug.h"

Debug* Debug::mpsInstance = nullptr;

//Create static instance
Debug* Debug::createInstance()
{
	mpsInstance = new Debug();
	return mpsInstance;
}
//Get static instance
Debug* Debug::instnace()
{
	if (mpsInstance == nullptr)
	{
		createInstance();
	}

	return mpsInstance;
}
//Remove and cleanup static instance
void Debug::removeInstance()
{
	delete mpsInstance;
	mpsInstance = nullptr;
}

Debug::Debug()
{
	// constructor
}
Debug::~Debug()
{
	// deconstructor
}

/*
Logs to the console
@param DebugColor: color for text to be
@param prefix: prefix at begining of log default is "[LOG]"
*/
DebugStream Debug::log(DebugColor color, std::string prefix)
{
	return DebugStream(prefix, color);
}
/*
Logs a warning to the console in yellow
*/
DebugStream Debug::warning()
{
	return DebugStream("[WARNING]", YELLOW);
}
/*
Logs an error to the console in red
*/
DebugStream Debug::error()
{
	return DebugStream("[ERROR]", RED);
}

//Print when destroyed
DebugStream::~DebugStream()
{
	//Set color
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), mColor);
	//Print prefix then message
	std::cout << mPrefix << " " << mBuffer.str() << "\n";
	//Set color to default
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_COLOR);
}