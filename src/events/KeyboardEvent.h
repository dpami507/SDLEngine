#include "EventSystem.h"

enum KeyEventType
{
	PRESSED = EventType::END_EVENT_TYPES,
	RELEASED,
	END_KEY_EVENTS
};

class KeyEvent : public Event
{
public:
	KeyEvent(KeyEventType type, uint32_t keyCode) : mKeyCode(keyCode), Event(type) {}
	~KeyEvent();
	
	inline uint32_t getKeyCode() const { return mKeyCode; }

private:
	SDL_Keycode mKeyCode;
};

KeyEvent::KeyEvent()
{
}

KeyEvent::~KeyEvent()
{
}