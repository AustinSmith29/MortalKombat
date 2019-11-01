#ifndef _USER_FIGHTER_H
#define _USER_FIGHTER_H

#include "fighter.h"
#include "fightmove_input_handler.h"

#include <string>

class UserFighter : public Fighter
{
public:
	using ActivationKey = FightMoveInputHandler::ActivationKey;

	UserFighter(FighterAnimator &animator, std::map<ActivationKey, std::string> move_map);
	UserFighter(const UserFighter& userfighter) = delete;
	UserFighter& operator = (const UserFighter& userfighter) = delete;

	void handle_input_event(InputEvent& event, InputDevice& controller);

private:
	FightMoveInputHandler fightmove_handler;	

	void handle_button_press(InputButton button, InputDevice& controller);
	void handle_button_release(InputButton button, InputDevice& controller);
};
#endif