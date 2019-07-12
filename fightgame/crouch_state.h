#ifndef _CROUCH_STATE_H
#define _CROUCH_STATE_H

#include "fighter_state.h"

class CrouchState : public FighterState
{
public:
	CrouchState();
	void enter(Fighter &fighter, FighterStateMachine &machine, void* data) override;
	void tick(Fighter &fighter, FighterStateMachine &machine) override;
	void exit(Fighter &fighter, FighterStateMachine &machine) override;
};

#endif