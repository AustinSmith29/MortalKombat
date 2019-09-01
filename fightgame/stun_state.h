#ifndef _STUN_STATE_H
#define _STUN_STATE_H

#include "fighter_state.h"

class Effect;
class StunState :  public FighterState
{
public:
	StunState(FighterStateMachine& machine);
	void enter(void* data) override;
	void tick() override;
	void exit() override;
private:
	int next_state;
	Effect* effect;
};

#endif