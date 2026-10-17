#include "EventListener.h"
#include "EventSystem.h"

namespace engine::event
{
	EventListener::EventListener()
	{
	}

	EventListener::~EventListener()
	{
		EventSystem::instance()->removeListenerFromAllEvents(this);
	}
}