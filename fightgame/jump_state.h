#ifndef _JUMP_STATE_H
#define _JUMP_STATE_H

#include "fighter_state.h"

class JumpState : public FighterState
{
public:
	void enter(Fighter& fighter) override;
	void tick(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
protected:
	virtual void update_position(Fighter& fighter);
	void apply_gravity(Fighter& fighter);
	void start_jump(Fighter& fighter);
	void finish_jump(Fighter& fighter);
	bool has_landed(Fighter& fighter);
private:
	int frame_counter{ 0 };
	const int GRAVITY{ 1 };
	const int FRAME_DELAY{ 2 };
	const int FLOOR_Y_POSITION{ 350 };
	void decrease_y_velocity(Fighter& fighter);
};
#endif