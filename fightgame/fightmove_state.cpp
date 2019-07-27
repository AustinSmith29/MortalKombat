#include "fightmove_state.h"
#include "fighter.h"

void FightMoveState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
{
	lock_input();
	move = *static_cast<FightMove*>(data);
	fighter.set_graphics(move.animation);
	auto hook = machine.get_previous_state()->get_move_hook();
	if (hook == FightMoveHook::CROUCH)
	{
		next_state = FighterStateMachine::State::CROUCH;
	}
	else
	{
		next_state = FighterStateMachine::State::IDLE;
	}
}

void FightMoveState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	bones::Animation* animation = fighter.get_animation();
	if (fighter.get_animation()->is_complete())
	{
		unlock_input();
		machine.change_to((FighterStateMachine::State)next_state, nullptr);
	}
}

void FightMoveState::exit(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.get_animation()->restart();
}