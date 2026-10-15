#pragma once

#include "Tracked.h"

class Event;
class EventSystem;

class EventListener : public Tracked
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void handleEvent(const Event& event) = 0;

private:
};