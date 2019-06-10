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
	if (fighter.get_animation()->is_complete())
		fighter.get_animation()->restart();
}

void MoveRightState::exit(Fighter &fighter)
{

}