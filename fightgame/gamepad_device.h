#ifndef _GAMEPAD_DEVICE_H
#define _GAMEPAD_DEVICE_H

#include "input_device.h"
#include <memory>

struct GamepadDeleterFunctor{
	void operator()(SDL_GameController* controller) {
		SDL_GameControllerClose(controller);
	}
};

class GamepadDevice : public InputDevice
{
public:
	GamepadDevice(SDL_GameController* controller);

	InputEvent get_input(SDL_Event& event) override;
	bool is_button_down(InputButton button) override;

private:
	std::unique_ptr <SDL_GameController, GamepadDeleterFunctor> controller;
};

#endif