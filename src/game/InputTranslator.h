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

	void init();
	void cleanup();
	void handleEvent(const Event& event) override;

private:

};