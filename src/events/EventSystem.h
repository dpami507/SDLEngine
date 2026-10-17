#pragma once
#include "Tracked.h"
#include "Debug.h"

#include "EventListener.h"

#include <map>

namespace engine::event
{
	enum EventType
	{
		INVALID = -1,
		APP_QUIT_EVENT,
		END_EVENT_TYPES,
	};

	class Event
	{
	public:
		inline Event(EventType type) : mType(type) {};
		~Event() = default;

		inline EventType getType() const { return mType; }
	private:
		EventType mType;
	};

	class EventSystem : public engine::memory::Tracked
	{
	public:
		EventSystem() = default;
		~EventSystem() { cleanup(); };

		static EventSystem* instance();
		static void removeInstance();
		static EventSystem* createInstance();

		bool init();
		void update();
		void cleanup();

		void fireEvent(const Event& pEvent);
		void addListener(const EventType& type, EventListener* listener);
		void removeListener(const EventType& type, EventListener* listener);
		void removeListenerFromAllEvents(EventListener* listener);

	private:
		static EventSystem* mspInstance;

		std::multimap<EventType, EventListener*> mListeners;
	};
}