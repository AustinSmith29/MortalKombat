#include "standard_effect.h"

StandardEffect::StandardEffect() : hitsound(new bones::AudioClip("data/sounds/hitsounds/mk2-00100.mp3")),
hurtsound(new bones::AudioClip("data/sounds/male/mk2-00618.mp3"))
{
}

void StandardEffect::enter(Fighter& fighter)
{
	if (fighter.is_airborne())
	{
		fighter.set_graphics(FighterGraphics::FALL);
		fall = true;
		next_state = FighterStateMachine::State::IDLE;
		// knock back fighter in direction of hit
		if (fighter.get_orientation() == Orientation::RIGHT)
			fighter.set_velocity_x(-2);
		else
			fighter.set_velocity_x(2);
	}
	else if (fighter.get_state()->get_previous_state()->get_move_hook() == FightMoveHook::CROUCH)
	{
		fighter.set_graphics(FighterGraphics::STUN_LOW);
		next_state = FighterStateMachine::State::CROUCH;
	}
	else
	{
		fighter.set_graphics(FighterGraphics::STUN_HIGH);
		next_state = FighterStateMachine::State::IDLE;
	}
	hitsound->play();
	hurtsound->play();
}

bool StandardEffect::is_complete(Fighter& fighter)
{
	if (fall && !fighter.is_airborne())
		return true;
	else if (!fall && fighter.get_animation()->is_complete())
		return true;
	return false;
}

void StandardEffect::exit(Fighter& fighter)
{
	fighter.set_velocity_x(0);
	fighter.set_velocity_y(0);
	fall = false;
}

FighterStateMachine::State StandardEffect::get_next_state()
{
	return next_state;
}