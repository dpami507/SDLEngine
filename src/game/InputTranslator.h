#pragma once
#include "EventListener.h"
#include "EventSystem.h"

#include "KeyboardEvent.h"

using namespace engine::debug;

class InputTranslator : public EventListener
{
public:
	InputTranslator() = default;
	~InputTranslator() { cleanup(); };

	void init()
	{
		EventSystem::instance()->addListener(KEYBOARD_EVENT, this);
		EventSystem::instance()->addListener(MOUSE_EVENT, this);
	}
	void cleanup()
	{

	}
	void handleEvent(const Event& event) override
	{
		if (event.getType() == KEYBOARD_EVENT)
		{
			const KeyEvent keyEvent = static_cast<const KeyEvent&>(event);
			Debug::log() << "a key was pressed: " << keyEvent.getKeyCode();
			//Stop if we hit the escape button
			if (keyEvent.getKeyCode() == SDLK_ESCAPE)
				Debug::warn() << "Quiting...";
			//stop();
		}
	}

private:

};