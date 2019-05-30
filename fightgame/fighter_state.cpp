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
	{true, false, true, false, false, true},
	{true, false, false, false, false, false},
	{true, false, false, false, false, false},
};

FighterState change_state(FighterState from, FighterState::State to, FighterState::Action action)
{
	if (state_transitions[from.state][to])
	{
		return FighterState(to, action);
	}
	return from;
}

FighterState change_action(FighterState state, FighterState::Action to)
{
	if (action_transitions[state.state][to])
	{
		return FighterState(state.state, to);
	}
	return state;
}
