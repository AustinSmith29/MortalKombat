#include "uppercut_effect.h"

void UppercutEffect::enter(Fighter& fighter)
{
	fighter.jump();
	if (fighter.get_orientation() == Orientation::RIGHT)
	{
		fighter.set_velocity_x(-2);
	}
	else
	{
		fighter.set_velocity_x(2);
	}
	fighter.set_graphics(FighterGraphics::FALL);
}

bool UppercutEffect::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}

void UppercutEffect::exit(Fighter& fighter)
{
	fighter.set_velocity_x(0);
}

FighterStateMachine::State UppercutEffect::get_next_state()
{
	return FighterStateMachine::State::IDLE;
}