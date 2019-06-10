#include "move_left_state.h"
#include "fighter.h"

void MoveLeftState::enter(Fighter& fighter)
{
	if (fighter.get_orientation() == Orientation::LEFT)
	{
		fighter.set_graphics(FighterGraphics::WALK_FORWARD);
	}
	else
	{
		fighter.set_graphics(FighterGraphics::WALK_BACKWARD);
	}
}

void MoveLeftState::tick(Fighter& fighter)
{
	fighter.move_left();
	if (fighter.get_animation()->is_complete())
	{
		fighter.get_animation()->restart();
	}
}

void MoveLeftState::exit(Fighter& fighter)
{

}