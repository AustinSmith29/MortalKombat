#ifndef _KEYBOARD_DEVICE_H
#define _KEYBOARD_DEVICE_H

#include "input_device.h"

class KeyboardDevice : public InputDevice
{
public:
	InputEvent get_input(SDL_Event& event) override;
	bool is_button_down(InputButton button) override;
};
#endif