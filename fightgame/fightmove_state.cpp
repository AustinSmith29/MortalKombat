#include "fightmove_state.h"
#include "fighter.h"

void FightMoveState::enter(Fighter& fighter)
{
	lock_input();
	fighter.set_graphics(FighterGraphics::FIGHT_MOVE);
}

void FightMoveState::tick(Fighter& fighter)
{
	if (fighter.get_animation()->is_complete())
	{
		unlock_input();
		exit(fighter);
	}
}

void FightMoveState::exit(Fighter& fighter)
{
	fighter.get_animation()->restart();
	auto hook = fighter.get_fight_move_hook();
	if (fighter.get_fight_move_hook() == FightMoveHook::CROUCH)
	{
		fighter.set_graphics(FighterGraphics::CROUCH);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::IDLE);
	}
}