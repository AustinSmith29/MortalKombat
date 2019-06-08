#ifndef _MOVE_RIGHT_STATE_H
#define _MOVE_RIGHT_STATE_H

#include "fighter_state.h"

class MoveRightState : public FighterState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
};
#endif