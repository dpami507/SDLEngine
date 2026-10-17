#pragma once
#include "Tracked.h"

namespace engine::event
{
	class Event;
	class EventSystem;

	class EventListener : public engine::memory::Tracked
	{
	public:
		EventListener();
		virtual ~EventListener();

		virtual void handleEvent(const Event& event) = 0;

	private:
	};
}