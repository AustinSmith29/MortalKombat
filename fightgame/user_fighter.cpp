#include "user_fighter.h"

UserFighter::UserFighter(Fighter& fighter, HandlerFunc handler, std::map<ActivationKey, FightMove> move_map)
	: fighter(&fighter), fightmove_handler(handler, move_map)
{

}

void UserFighter::handle_input_event(SDL_Event& event, SDL_GameController* controller)
{
	if (fighter->get_state()->is_input_locked())
		return;
	fightmove_handler.process_event(event, fighter->get_state()->get_fightmove_hook(), fighter->get_orientation());
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
			fighter->set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
		else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			fighter->set_state(FighterStateMachine::State::JUMP_LEFT);
		}
		else
		{
			fighter->set_state(FighterStateMachine::State::JUMP);
		}
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
	{
		fighter->set_state(FighterStateMachine::State::MOVE_RIGHT);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
	{
		fighter->set_state(FighterStateMachine::State::MOVE_LEFT);
	}
	else if (button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
	{
		fighter->set_state(FighterStateMachine::State::CROUCH);
	}
	else if (button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		fighter->set_state(FighterStateMachine::State::BLOCK);
	}
}

void UserFighter::handle_button_release(Uint8 button)
{
	fighter->set_state(FighterStateMachine::State::IDLE);
}

void UserFighter::tick()
{
	fighter->tick();
}

void UserFighter::draw(SDL_Renderer* renderer)
{
	fighter->draw(renderer);
}