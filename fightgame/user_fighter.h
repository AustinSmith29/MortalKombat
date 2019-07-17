#ifndef _USER_FIGHTER_H
#define _USER_FIGHTER_H

#include "fighter.h"
#include "fightmove_input_handler.h"

class UserFighter : public Fighter
{
public:
	using HandlerFunc = FightMoveInputHandler::HandlerFunc;
	using ActivationKey = FightMoveInputHandler::ActivationKey;

	UserFighter(FighterAnimator &animator, HandlerFunc handler, std::map<ActivationKey, FightMove> move_map);
	UserFighter(const UserFighter& userfighter) = delete;
	UserFighter& operator = (const UserFighter& userfighter) = delete;

	void handle_input_event(SDL_Event& event, SDL_GameController* controller);

private:
	FightMoveInputHandler fightmove_handler;	

	void handle_button_press(Uint8 button, SDL_GameController* controller);
	void handle_button_release(Uint8 button);
};
#endif