#ifndef _JUMP_RIGHT_STATE_H
#define _JUMP_RIGHT_STATE_H

#include "jump_state.h"

class JumpRightState :  public JumpState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
private:
	void update_position(Fighter& fighter) override;
};
#endif