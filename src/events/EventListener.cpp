#include "EventListener.h"
#include "EventSystem.h"

using namespace engine::event;

EventListener::EventListener()
{
}

EventListener::~EventListener()
{
	EventSystem::instance()->removeListenerFromAllEvents(this);
}