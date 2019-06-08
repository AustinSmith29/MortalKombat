#include "move_right_state.h"
#include "fighter.h"

void MoveRightState::enter(Fighter& fighter)
{
	if (fighter.get_orientation() == Orientation::RIGHT)
	{
		fighter.set_graphics(FighterGraphics::WALK_FORWARD);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::WALK_BACKWARD);
	}
}

void MoveRightState::tick(Fighter& fighter)
{
	fighter.move_right();
}

void MoveRightState::exit(Fighter &fighter)
{

}