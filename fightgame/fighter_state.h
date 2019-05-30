#ifndef _FIGHTER_STATE
#define _FIGHTER_STATE

struct FighterState
{
	enum State
	{
		STAND = 0,
		CROUCH,
		JUMP,
		THROWN,
		KNOCKED
	} state;
	enum Action
	{
		NONE = 0,
		BLOCK,
		STUN,
		MOVELEFT,
		MOVERIGHT,
		ATTACK
	} action;
	FighterState() = default;
	FighterState(State s, Action a) { state = s; action = a; locked = false; }
	bool locked;
};

FighterState change_state(FighterState from, FighterState::State to, FighterState::Action action);
FighterState change_action(FighterState state, FighterState::Action to);
void lock_state(FighterState& state);
void unlock_state(FighterState& state);
#endif