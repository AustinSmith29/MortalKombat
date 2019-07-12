#ifndef _JUMP_LEFT_STATE_H
#define _JUMP_LEFT_STATE_H

#include "jump_state.h"

class JumpLeftState : public JumpState
{
public:
	void enter(Fighter& fighter, FighterStateMachine &machine, void *data) override;
	void tick(Fighter& fighter, FighterStateMachine &machine) override;
	void exit(Fighter& fighter, FighterStateMachine &machine) override;
private:
	void update_position(Fighter& fighter) override;
};
#endif