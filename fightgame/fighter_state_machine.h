#ifndef _FIGHTER_STATE_MACHINE_H
#define _FIGHTER_STATE_MACHINE_H

#include "all_fight_states.h"

#include <array>

class Fighter;
class FighterStateMachine
{
public:
	enum State {
		IDLE,
		CROUCH,
		MOVE_RIGHT,
		MOVE_LEFT,
		FIGHT_MOVE,
		JUMP,
		JUMP_RIGHT,
		JUMP_LEFT,
		BLOCK,
		TOTAL
	};

	FighterStateMachine(Fighter& fighter);
	FighterStateMachine(const FighterStateMachine& machine) = delete;
	FighterStateMachine& operator = (const FighterStateMachine& machine) = delete;

	~FighterStateMachine();

	void change_to(State new_state, void *data);
	FighterState::FightMoveHook get_fightmove_hook();
	bool is_input_locked();
	FighterState* get_previous_state();
	void tick();

private:
	std::array<FighterState*, State::TOTAL> states;
	FighterState* current_state;
	FighterState* prev_state;
	Fighter& fighter;
};
#endif