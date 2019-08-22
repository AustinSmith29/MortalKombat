#ifndef _MOVE_LEFT_STATE_H
#define _MOVE_LEFT_STATE_H

#include "fighter_state.h"

class MoveLeftState : public FighterState
{
public:
	MoveLeftState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif