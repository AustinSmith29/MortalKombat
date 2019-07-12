#include "move_right_state.h"
#include "fighter.h"

void MoveRightState::enter(Fighter& fighter, FighterStateMachine &machine, void *data)
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

void MoveRightState::tick(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.move_right();
	fighter.get_animation()->loop();
}

void MoveRightState::exit(Fighter &fighter, FighterStateMachine &machine)
{

}