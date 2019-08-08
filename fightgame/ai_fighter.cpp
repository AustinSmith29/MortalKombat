#include "ai_fighter.h"
#include "ai_util.h"

#include <cmath>
#include <iostream>

static Uint32 timer_callback(Uint32 interval, void* param)
{
	bool* status = static_cast<bool*>(param);
	*status = false;
	return 0;
}

AIFighter::AIFighter(FighterAnimator& animator, std::function<void(AIFighter& ai, Fighter& other)> logic, HandlerFunc handler)
	: Fighter(animator), logic_func(logic), fightmove_handler(handler)
{
}

void AIFighter::tick(Fighter &other)
{
	if (!state_machine->is_input_locked() && !action_chosen)
	{ 
		logic_func(*this, other);
		action_chosen = true;
		SDL_AddTimer(200, timer_callback, &action_chosen);
	}
	Fighter::tick();
}

void AIFighter::do_move(FightMove& move)
{
	set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
	fightmove_handler(move, *this);
}
