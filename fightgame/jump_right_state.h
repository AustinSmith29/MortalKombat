#ifndef _JUMP_RIGHT_STATE_H
#define _JUMP_RIGHT_STATE_H

#include "fighter_state.h"

class JumpRightState :  public FighterState
{
public:
	JumpRightState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif