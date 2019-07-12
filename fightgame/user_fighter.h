#ifndef _USER_FIGHTER_H
#define _USER_FIGHTER_H

#include "fighter.h"
#include "fightmove_input_handler.h"

class UserFighter 
{
public:
	void handle_input_event(SDL_Event& event, SDL_GameController* controller);

private:
	Fighter fighter;
	FightMoveInputHandler fightmove_handler;	

	void handle_button_press(Uint8 button, SDL_GameController* controller);
	void handle_button_release(Uint8 button);
};
#endif