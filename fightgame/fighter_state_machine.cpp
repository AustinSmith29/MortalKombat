#include "fighter_state_machine.h"

FighterStateMachine::FighterStateMachine(Fighter& owner) : fighter(owner)
{
	states[State::IDLE] = IdleState();
	states[State::CROUCH] = CrouchState();
	states[State::MOVE_RIGHT] = MoveRightState();
	states[State::MOVE_LEFT] = MoveLeftState();
	states[State::FIGHT_MOVE] = FightMoveState();
	states[State::JUMP] = JumpState();
	states[State::JUMP_RIGHT] = JumpRightState();
	states[State::JUMP_LEFT] = JumpLeftState();
	states[State::BLOCK] = BlockState();
	current_state = &states[State::IDLE];
}

void FighterStateMachine::change_to(State new_state)
{
	current_state->exit(fighter);
	current_state = &states[new_state];
	current_state->enter(fighter);
}

void FighterStateMachine::tick()
{
	current_state->tick(fighter);
}