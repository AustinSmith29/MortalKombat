#include "thrown_effect.h"

ThrownEffect::ThrownEffect() : hurtsound(new bones::AudioClip("data/sounds/male/mk2-00665.mp3"))
{

}

void ThrownEffect::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::THROWN);
	fighter.set_velocity_y(-8);
	if (fighter.get_orientation() == Orientation::RIGHT)
	{
		fighter.set_velocity_x(3);
	}
	else
	{
		fighter.set_velocity_x(-3);
	}
	hurtsound->play();
}

bool ThrownEffect::is_complete(Fighter& fighter)
{
	return fighter.get_animation()->is_complete();
}

void ThrownEffect::exit(Fighter& fighter)
{
	fighter.set_velocity_x(0);
}

FighterStateMachine::State ThrownEffect::get_next_state()
{
	return FighterStateMachine::State::IDLE;
}