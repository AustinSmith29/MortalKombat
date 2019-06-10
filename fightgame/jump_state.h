#ifndef _JUMP_STATE_H
#define _JUMP_STATE_H

#include "fighter_state.h"

class JumpState : public FighterState
{
public:
	void enter(Fighter* fighter);
	void tick(Fighter* fighter);
	void exit(Fighter* fighter);
};
#endif
