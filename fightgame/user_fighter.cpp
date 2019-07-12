#include "user_fighter.h"

void UserFighter::handle_input_event(SDL_Event& event, SDL_GameController* controller)
{
	if (current_state->is_input_locked())
		return;
	move_source.process_event(event, orientation);
	if (event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		handle_button_press(event.cbutton.button, controller);
	}
	if (event.type == SDL_CONTROLLERBUTTONUP)
	{
		handle_button_release(event.cbutton.button);
	}
}

void UserFighter::handle_button_press(Uint8 button, SDL_GameController* controller)
{
	if (button == SDL_CONTROLLER_BUTTON_DPAD_UP)
	{
		if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			change_state_if_open(&jump_right_state);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			change_state_if_open(&jump_left_state);
		}
		else
		{
			change_state_if_open(&jump_state);
		}
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		change_state_if_open(&move_right_state);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		change_state_if_open(&move_left_state);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
	{
		change_state_if_open(&crouch_state);
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		change_state_if_open(&block_state);
	}
}

void UserFighter::handle_button_release(Uint8 button)
{
	change_state_if_open(&idle_state);
}
}