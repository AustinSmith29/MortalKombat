#ifndef _CROUCH_STATE_H
#define _CROUCH_STATE_H

#include "fighter_state.h"

class CrouchState : public FighterState
{
public:
	CrouchState(FighterStateMachine& machine);
	void enter(void* data) override;
	void tick() override;
	void exit() override;
};

#endif