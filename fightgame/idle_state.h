#ifndef _IDLE_STATE_H
#define _IDLE_STATE_H

#include "fighter_state.h"

class IdleState : public FighterState
{
public:
	IdleState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif