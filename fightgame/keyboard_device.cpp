#include "keyboard_device.h"

#include <map>

static std::map<InputButton, SDL_Scancode> translations = {
	{InputButton::BUTTON_A, SDL_SCANCODE_A},
	{InputButton::BUTTON_X, SDL_SCANCODE_S},
	{InputButton::BUTTON_Y, SDL_SCANCODE_D},
	{InputButton::BUTTON_B, SDL_SCANCODE_F},
	{InputButton::BUTTON_UP, SDL_SCANCODE_UP},
	{InputButton::BUTTON_DOWN, SDL_SCANCODE_DOWN},
	{InputButton::BUTTON_LEFT, SDL_SCANCODE_LEFT},
	{InputButton::BUTTON_RIGHT, SDL_SCANCODE_RIGHT},
	{InputButton::BUTTON_BACK, SDL_SCANCODE_ESCAPE},
	{InputButton::BUTTON_START, SDL_SCANCODE_RETURN},
	{InputButton::BUTTON_LEFTSHOULDER, SDL_SCANCODE_LSHIFT},
	{InputButton::BUTTON_RIGHTSHOULDER, SDL_SCANCODE_RSHIFT},
};

InputEvent KeyboardDevice::get_input(SDL_Event& event)
{
	InputEvent evnt = { EventType::NONE, InputButton::NONE };

	if (event.type == SDL_KEYDOWN) evnt.type = EventType::BUTTON_DOWN;
	if (event.type == SDL_KEYUP) evnt.type = EventType::BUTTON_UP;

	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
	{
		for (auto item : translations)
		{
			if (event.key.keysym.scancode == item.second)
			{
				evnt.button = item.first;
			}
		}
	}
	return evnt;
}

bool KeyboardDevice::is_button_down(InputButton btn)
{
	if (btn == InputButton::NONE)
		return false;

	SDL_Scancode key = translations[btn];
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[key])
		return true;
	return false;
}