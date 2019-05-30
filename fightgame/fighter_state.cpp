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

FighterState change_state(FighterState from, FighterState::State to, FighterState::Action action)
{
	if (state_transitions[from.state][to] && !from.locked_state && !from.locked_action)
	{
		auto new_state = FighterState(to, action);
		return new_state;
	}
	return from;
}

FighterState change_action(FighterState state, FighterState::Action to)
{
	if (action_transitions[state.state][to] && !state.locked_action)
	{
		auto new_state = FighterState(state.state, to);
		return new_state;
	}
	return state;
}

void lock_state(FighterState& state)
{
	state.locked_state = true;
}

void unlock_state(FighterState& state)
{
	state.locked_state = false;
}

void lock_action(FighterState& state)
{
	state.locked_action = true;
}

void unlock_action(FighterState& state)
{
	state.locked_action = false;
}
