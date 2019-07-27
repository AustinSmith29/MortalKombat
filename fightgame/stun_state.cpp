#include "stun_state.h"
#include "fighter.h"

#include <iostream>

void StunState::enter(Fighter& fighter, FighterStateMachine& machine, void* data)
{
	std::cout << "STUN STATE ENTER!\n";
	lock_input();
	if (fighter.is_airborne())
	{
		fall = true;
	}
	else
	{
		fighter.set_graphics(FighterGraphics::STUN_HIGH);
	}
}

void StunState::tick(Fighter& fighter, FighterStateMachine& machine)
{
	if (fall)
		apply_gravity(fighter, machine);

	if (fall && has_landed(fighter))
		exit(fighter, machine);
	else if (fighter.get_animation()->is_complete())
		exit(fighter, machine);
}

void change_state(Fighter& fighter, FighterStateMachine& machine)
{

}

void StunState::exit(Fighter& fighter, FighterStateMachine& machine)
{
	unlock_input();
	fighter.get_animation()->restart();
}