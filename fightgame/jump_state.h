#ifndef _JUMP_STATE_H
#define _JUMP_STATE_H

#include "fighter_state.h"

class JumpState : public FighterState
{
public:
	JumpState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif
