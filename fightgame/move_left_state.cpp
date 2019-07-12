#include "move_left_state.h"
#include "fighter.h"

void MoveLeftState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
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

void MoveLeftState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.move_left();
	fighter.get_animation()->loop();
}

void MoveLeftState::exit(Fighter& fighter, FighterStateMachine &machine)
{

}