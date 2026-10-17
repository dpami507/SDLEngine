#pragma once
#include "EventListener.h"
#include "EventSystem.h"

#include "InputEvents.h"

using namespace engine::debug;
using namespace engine::event;

class InputTranslator : public EventListener
{
public:
	InputTranslator() = default;
	~InputTranslator() { cleanup(); };

	void init()
	{
		EventSystem::instance()->addListener(EventType(MOUSE_MOVE), this);
		EventSystem::instance()->addListener(EventType(MOUSE_PRESSED), this);
		EventSystem::instance()->addListener(EventType(MOUSE_RELEASED), this);

		EventSystem::instance()->addListener(EventType(KEY_PRESSED), this);
		EventSystem::instance()->addListener(EventType(KEY_RELEASED), this);
	}
	void cleanup()
	{

	}
	void handleEvent(const Event& event) override
	{
		if (event.getType() == KEY_PRESSED)
		{
			const KeyEvent keyEvent = static_cast<const KeyEvent&>(event);
			Debug::log() << "a key was pressed: " << keyEvent.getKeyCode();

			if (keyEvent.getKeyCode() == ESC)
			{
				EventSystem::instance()->fireEvent(Event(APP_QUIT_EVENT));
			}
		}
		if (event.getType() == KEY_RELEASED)
		{
			const KeyEvent keyEvent = static_cast<const KeyEvent&>(event);
			Debug::log() << "a key was released: " << keyEvent.getKeyCode();
		}
		if (event.getType() == MOUSE_MOVE)
		{
			const MouseMoveEvent mouseEvent = static_cast<const MouseMoveEvent&>(event);
			Debug::log() << "Mouse pos: " << mouseEvent.getMousePos();
			Debug::log() << "Mouse delta: " << mouseEvent.getMouseDelta();
		}
		if (event.getType() == MOUSE_PRESSED)
		{
			const MouseClickEvent mouseEvent = static_cast<const MouseClickEvent&>(event);
			Debug::log() << "Mouse was pressed: " << mouseEvent.getMouseButton();
			Debug::log() << "Mouse pos: " << mouseEvent.getMousePos();
		}
		if (event.getType() == MOUSE_RELEASED)
		{
			const MouseClickEvent mouseEvent = static_cast<const MouseClickEvent&>(event);
			Debug::log() << "Mouse was rleased: " << mouseEvent.getMouseButton();
			Debug::log() << "Mouse pos: " << mouseEvent.getMousePos();
		}
	}

private:

};