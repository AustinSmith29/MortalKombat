#ifndef _INPUT_DEVICE_H
#define _INPUT_DEVICE_H

#include <SDL.h>

enum class InputButton
{
	NONE,
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_LEFTSHOULDER,
	BUTTON_RIGHTSHOULDER,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT
};

enum class EventType
{
	NONE,
	BUTTON_DOWN,
	BUTTON_UP
};

struct InputEvent
{
	EventType type;
	InputButton button;
};

class InputDevice
{
public:
	virtual ~InputDevice() = default;
	virtual InputEvent get_input(SDL_Event& event) = 0;
	virtual bool is_button_down(InputButton button) = 0;
};
#endif