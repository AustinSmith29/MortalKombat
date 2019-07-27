#ifndef _STUN_STATE_H
#define _STUN_STATE_H

#include "jump_state.h"

class StunState :  public JumpState
{
public:
	void enter(Fighter& fighter, FighterStateMachine& machine, void* data) override;
	void tick(Fighter& fighter, FighterStateMachine& machine) override;
	void exit(Fighter& fighter, FighterStateMachine& machine) override;
private:
	bool fall{ false };
	int next_state;
};

#endif