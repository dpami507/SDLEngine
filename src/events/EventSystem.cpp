#include "EventSystem.h"

using namespace engine::debug;

EventSystem* EventSystem::mspInstance = nullptr;

EventSystem::EventSystem()
{
}

EventSystem::~EventSystem()
{
}

EventSystem* EventSystem::instance()
{
	return mspInstance;
}
void EventSystem::removeInstance()
{
	delete mspInstance;
	mspInstance = nullptr;
}
EventSystem* EventSystem::destroyInstance()
{
	if (mspInstance != nullptr)
	{
		removeInstance();
	}
	mspInstance = new EventSystem();
	return mspInstance;
}

bool EventSystem::init()
{
	return true;
}

void EventSystem::update()
{
	SDL_Event pEvent;
	while (SDL_PollEvent(&pEvent))
	{
		switch (pEvent.type)
		{
		case SDL_EVENT_MOUSE_MOTION:
			Debug::log() << pEvent.motion.x << ", " << pEvent.motion.y;
			break;
		case SDL_EVENT_QUIT:
			Debug::warn() << "Quiting...";
			//stop();
			break;
		case SDL_EVENT_KEY_DOWN:
			Debug::log() << "a key was pressed: " << pEvent.key.key;
			//Stop if we hit the escape button
			if (pEvent.key.key == SDLK_ESCAPE)
				Debug::warn() << "Quiting...";
			//stop();
		default:
			break;
		}
	}
}

void EventSystem::fireEvent(const Event& pEvent)
{
	// early break if the map doesn't have it
	if (!mListeners.contains(pEvent.getType())) return;

	// go through range
	auto range = mListeners.equal_range(pEvent.getType());
	for (auto i = range.first; i != range.second; ++i)
	{
		i->second->handleEvent(pEvent);
	}
}
void EventSystem::addListener(const EventType& type, EventListener* listener)
{
	mListeners.insert(std::make_pair(type, listener));
}
void EventSystem::removeListener(const EventType& type, EventListener* listener)
{
	// early break if the map doesn't have it
	if (!mListeners.contains(type)) return;

	// go through range
	auto range = mListeners.equal_range(type);
	for (auto i = range.first; i != range.second; ++i)
	{
		if (i->second == listener)
		{
			mListeners.erase(i);
			break;
		}
	}
}
void EventSystem::removeListenerFromAllEvents(EventListener* listener)
{
	bool allTheWayThrough = false;

	// go through range
	while (!allTheWayThrough)
	{
		allTheWayThrough = true;
		for (auto i = mListeners.begin(); i != mListeners.end(); ++i)
		{
			if (i->second == listener)
			{
				mListeners.erase(i);
				allTheWayThrough = false;
				break;
			}
		}
	}
}