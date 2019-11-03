#include "uppercut_effect.h"

UppercutEffect::UppercutEffect() : hitsound(new bones::AudioClip("data/sounds/hitsounds/mk2-00100.mp3")),
hurtsound(new bones::AudioClip("data/sounds/male/mk2-00633.mp3"))
{
}

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
	hitsound->play();
	hurtsound->play();
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