#include "Tracked.h"
#include "SDL3/SDL_events.h"
#include "Debug.h"

#include "EventListener.h"

#include <map>

enum EventType
{
	INVALID = -1,
	MOUSE_EVENT,	// Holds position and maybe delta, mouse released and mouse down
	KEYBOARD_EVENT,		 // Released / Pressed, key code
	END_EVENT_TYPES,
};
class Event
{
public:
	inline Event(EventType type) : mType(type) { };
	~Event() = default;

	inline EventType getType() const { return mType; }
private:
	EventType mType;
};

class EventSystem : public Tracked
{
public:
	EventSystem();
	~EventSystem();

	static EventSystem* instance();
	static void removeInstance();
	static EventSystem* destroyInstance();

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