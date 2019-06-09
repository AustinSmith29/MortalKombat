#include "fighter_state.h"

static bool state_transitions[5][5] = {
	{true, true, true, true, true},
	{true, true, false, true, true },
	{true, false, true, false, true },
	{true, true, false, true, true},
	{true, true, false, false, true },
};

static bool action_transitions[5][6] = {
	{true, true, true, true, true, true},
	{true, true, true, false, false, true},
	{true, false, true, true, true, true},
	{true, false, false, false, false, false},
	{true, false, false, false, false, false},
};

bool FighterState::is_complete()
{
	return complete;
}

void FighterState::finish()
{
	complete = true;
}

FighterState::FightMoveHook FighterState::get_move_hook()
{
	return move_hook;
}

void FighterState::set_move_hook(FighterState::FightMoveHook hook)
{
	move_hook = hook;
}
