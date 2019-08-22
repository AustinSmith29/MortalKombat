#ifndef _MOVE_RIGHT_STATE_H
#define _MOVE_RIGHT_STATE_H

#include "fighter_state.h"

class MoveRightState : public FighterState
{
public:
	MoveRightState(FighterStateMachine& machine);
	void enter(void *data) override;
	void tick() override;
	void exit() override;
};
#endif