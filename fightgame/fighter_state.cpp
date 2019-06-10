#include "fighter_state.h"

bool FighterState::is_input_locked()
{
	return lock;
}

void FighterState::lock_input()
{
	lock = true;
}
void FighterState::unlock_input()
{
	lock = false;
}

FighterState::FightMoveHook FighterState::get_move_hook()
{
	return move_hook;
}

void FighterState::set_move_hook(FighterState::FightMoveHook hook)
{
	move_hook = hook;
}
