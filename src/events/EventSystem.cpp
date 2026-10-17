#include "EventSystem.h"
#include "InputEvents.h"

#include "SDL3/SDL_events.h"

using namespace engine::debug;
using namespace engine::math;

namespace engine::event
{
	EventSystem* EventSystem::mspInstance = nullptr;

	EventSystem* EventSystem::instance()
	{
		return mspInstance;
	}
	void EventSystem::removeInstance()
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
	EventSystem* EventSystem::createInstance()
	{
		mspInstance = new EventSystem();
		return mspInstance;
	}

	bool EventSystem::init()
	{
		Debug::log(DBG_BLUE, "[INIT]") << "Event System Inititialized";
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
				fireEvent(MouseMoveEvent(MOUSE_MOVE,
					Vector2(pEvent.motion.x, pEvent.motion.y), Vector2(pEvent.motion.xrel, pEvent.motion.yrel)));
				break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				fireEvent(MouseClickEvent(MOUSE_PRESSED, pEvent.button.button, Vector2(pEvent.motion.x, pEvent.motion.y)));
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				fireEvent(MouseClickEvent(MOUSE_RELEASED, pEvent.button.button, Vector2(pEvent.motion.x, pEvent.motion.y)));
				break;
			case SDL_EVENT_QUIT:
				fireEvent(Event(APP_QUIT_EVENT));
				break;
			case SDL_EVENT_KEY_DOWN:
				fireEvent(KeyEvent(KeyEventType(KEY_PRESSED), pEvent.key.key));
				break;
			case SDL_EVENT_KEY_UP:
				fireEvent(KeyEvent(KeyEventType(KEY_RELEASED), pEvent.key.key));
				break;
			default:
				break;
			}
		}
	}
	void EventSystem::cleanup()
	{
		Debug::log(DBG_YELLOW, "[CLEANUP]") << "Cleaning up Event System";
		mListeners.clear();
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
}