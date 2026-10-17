#pragma once
#include "EventSystem.h"
#include "Vector2.h"

#include "SDL3/SDL_events.h"

namespace engine::event
{
	enum Keys
	{
		// Control / system
		ESC = SDLK_ESCAPE,
		RETURN = SDLK_RETURN,
		SPACE = SDLK_SPACE,
		TAB = SDLK_TAB,
		BACKSPACE = SDLK_BACKSPACE,
		DELETE_KEY = SDLK_DELETE,
		INSERT = SDLK_INSERT,
		HOME = SDLK_HOME,
		END = SDLK_END,
		PAGE_UP = SDLK_PAGEUP,
		PAGE_DOWN = SDLK_PAGEDOWN,

		// Arrows
		LEFT = SDLK_LEFT,
		RIGHT = SDLK_RIGHT,
		UP = SDLK_UP,
		DOWN = SDLK_DOWN,

		// Function keys
		F1 = SDLK_F1,
		F2 = SDLK_F2,
		F3 = SDLK_F3,
		F4 = SDLK_F4,
		F5 = SDLK_F5,
		F6 = SDLK_F6,
		F7 = SDLK_F7,
		F8 = SDLK_F8,
		F9 = SDLK_F9,
		F10 = SDLK_F10,
		F11 = SDLK_F11,
		F12 = SDLK_F12,

		// Number row
		KEY_0 = SDLK_0,
		KEY_1 = SDLK_1,
		KEY_2 = SDLK_2,
		KEY_3 = SDLK_3,
		KEY_4 = SDLK_4,
		KEY_5 = SDLK_5,
		KEY_6 = SDLK_6,
		KEY_7 = SDLK_7,
		KEY_8 = SDLK_8,
		KEY_9 = SDLK_9,

		// Letters
		A = SDLK_A,
		B = SDLK_B,
		C = SDLK_C,
		D = SDLK_D,
		E = SDLK_E,
		F = SDLK_F,
		G = SDLK_G,
		H = SDLK_H,
		I = SDLK_I,
		J = SDLK_J,
		K = SDLK_K,
		L = SDLK_L,
		M = SDLK_M,
		N = SDLK_N,
		O = SDLK_O,
		P = SDLK_P,
		Q = SDLK_Q,
		R = SDLK_R,
		S = SDLK_S,
		T = SDLK_T,
		U = SDLK_U,
		V = SDLK_V,
		W = SDLK_W,
		X = SDLK_X,
		Y = SDLK_Y,
		Z = SDLK_Z,

		// Punctuation / symbols (common ones)
		MINUS = SDLK_MINUS,
		EQUALS = SDLK_EQUALS,
		LEFT_BRACKET = SDLK_LEFTBRACKET,
		RIGHT_BRACKET = SDLK_RIGHTBRACKET,
		BACKSLASH = SDLK_BACKSLASH,
		SEMICOLON = SDLK_SEMICOLON,
		APOSTROPHE = SDLK_APOSTROPHE,
		GRAVE = SDLK_GRAVE,
		COMMA = SDLK_COMMA,
		PERIOD = SDLK_PERIOD,
		SLASH = SDLK_SLASH,

		// Keypad
		KEYPAD_0 = SDLK_KP_0,
		KEYPAD_1 = SDLK_KP_1,
		KEYPAD_2 = SDLK_KP_2,
		KEYPAD_3 = SDLK_KP_3,
		KEYPAD_4 = SDLK_KP_4,
		KEYPAD_5 = SDLK_KP_5,
		KEYPAD_6 = SDLK_KP_6,
		KEYPAD_7 = SDLK_KP_7,
		KEYPAD_8 = SDLK_KP_8,
		KEYPAD_9 = SDLK_KP_9,
		KEYPAD_DIVIDE = SDLK_KP_DIVIDE,
		KEYPAD_MULTIPLY = SDLK_KP_MULTIPLY,
		KEYPAD_MINUS = SDLK_KP_MINUS,
		KEYPAD_PLUS = SDLK_KP_PLUS,
		KEYPAD_ENTER = SDLK_KP_ENTER,
		KEYPAD_PERIOD = SDLK_KP_PERIOD,

		// Locks / misc
		CAPS_LOCK = SDLK_CAPSLOCK,
		NUM_LOCK = SDLK_NUMLOCKCLEAR,
		SCROLL_LOCK = SDLK_SCROLLLOCK,
		PRINT_SCREEN = SDLK_PRINTSCREEN,
		PAUSE = SDLK_PAUSE,

		// Modifiers (explicit keys)
		LEFT_SHIFT = SDLK_LSHIFT,
		RIGHT_SHIFT = SDLK_RSHIFT,
		LEFT_CTRL = SDLK_LCTRL,
		RIGHT_CTRL = SDLK_RCTRL,
		LEFT_ALT = SDLK_LALT,
		RIGHT_ALT = SDLK_RALT,
		LEFT_GUI = SDLK_LGUI,
		RIGHT_GUI = SDLK_RGUI,
	};

	enum KeyEventType
	{
		KEY_PRESSED = END_EVENT_TYPES,
		KEY_RELEASED,
		END_KEY_EVENTS
	};
	class KeyEvent : public Event
	{
	public:
		KeyEvent(KeyEventType type, int keyCode) : mKeyCode(keyCode), Event(EventType(type)) {}
		~KeyEvent() {};

		inline int getKeyCode() const { return mKeyCode; };

	private:
		int mKeyCode;
	};

	enum MouseEventType
	{
		MOUSE_PRESSED = END_KEY_EVENTS,
		MOUSE_RELEASED,
		MOUSE_MOVE,
		END_MOUSE_EVENTS
	};
	class MouseClickEvent : public Event
	{
	public:
		MouseClickEvent(MouseEventType type, int mouseButton, engine::math::Vector2 mousePos) 
			: mMouseButton(mouseButton), mMousePos(mousePos), Event(EventType(type)) {}
		~MouseClickEvent() {};

		inline int getMouseButton() const { return mMouseButton; };
		inline engine::math::Vector2 getMousePos() const { return mMousePos; };

	private:
		int mMouseButton;
		engine::math::Vector2 mMousePos;
	};
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(MouseEventType type, engine::math::Vector2 mousePos, engine::math::Vector2 mouseDelta)
			: mMousePos(mousePos), mMouseDelta(mouseDelta), Event(EventType(type)) {
		}
		~MouseMoveEvent() {};

		inline engine::math::Vector2 getMousePos() const { return mMousePos; };
		inline engine::math::Vector2 getMouseDelta() const { return mMouseDelta; };
	private:
		engine::math::Vector2 mMousePos;
		engine::math::Vector2 mMouseDelta;
	};

}