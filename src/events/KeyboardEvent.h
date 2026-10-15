#pragma once
#include "EventSystem.h"

enum KeyEventType
{
	PRESSED = END_EVENT_TYPES,
	RELEASED,
	END_KEY_EVENTS
};

class KeyEvent : public Event
{
public:
	KeyEvent(KeyEventType type, int keyCode) : mKeyCode(keyCode), Event(EventType(type)) {}
	~KeyEvent() {};
	
	inline int getKeyCode() const { return mKeyCode; }

private:
	int mKeyCode;
};