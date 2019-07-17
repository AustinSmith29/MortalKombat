#include "user_fighter.h"

UserFighter::UserFighter(FighterAnimator& animator, HandlerFunc handler, std::map<ActivationKey, FightMove> move_map)
	: Fighter(animator), fightmove_handler(handler, move_map)
{

}

void UserFighter::handle_input_event(SDL_Event& event, SDL_GameController* controller)
{
	if (state_machine->is_input_locked())
		return;
	fightmove_handler.process_event(event, state_machine->get_fightmove_hook(), 
		                            get_orientation(), *this);
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
			set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			set_state(FighterStateMachine::State::JUMP_LEFT);
		}
		else
		{
			set_state(FighterStateMachine::State::JUMP);
		}
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		set_state(FighterStateMachine::State::MOVE_RIGHT);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		set_state(FighterStateMachine::State::MOVE_LEFT);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
	{
		set_state(FighterStateMachine::State::CROUCH);
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		set_state(FighterStateMachine::State::BLOCK);
	}
}

void UserFighter::handle_button_release(Uint8 button)
{
	set_state(FighterStateMachine::State::IDLE);
}
