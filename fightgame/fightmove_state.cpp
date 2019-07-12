#include "fightmove_state.h"
#include "fighter.h"

void FightMoveState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
{
	lock_input();
	move = *static_cast<FightMove*>(data);
	fighter.set_graphics(move.animation);
}

void FightMoveState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	if (fighter.get_animation()->is_complete())
	{
		unlock_input();
		exit(fighter, machine);
	}
}

void FightMoveState::exit(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.get_animation()->restart();
	auto hook = machine.get_previous_state()->get_move_hook();
	if (hook == FightMoveHook::CROUCH)
	{
		fighter.set_graphics(FighterGraphics::CROUCH);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::IDLE);
	}
}