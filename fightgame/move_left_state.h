#ifndef _MOVE_LEFT_STATE_H
#define _MOVE_LEFT_STATE_H

#include "fighter_state.h"

class MoveLeftState : public FighterState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
};
#endif