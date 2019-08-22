#ifndef _JUMP_LEFT_STATE_H
#define _JUMP_LEFT_STATE_H

#include "fighter_state.h"

class JumpLeftState : public FighterState
{
public:
	JumpLeftState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif