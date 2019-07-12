#include "block_state.h"
#include "fighter.h"

void BlockState::enter(Fighter& fighter, FighterStateMachine &machine, void* data)
{
	fighter.set_graphics(FighterGraphics::BLOCK);
}

void BlockState::tick(Fighter& fighter, FighterStateMachine &machine)
{

}

void BlockState::exit(Fighter& fighter, FighterStateMachine &machine)
{
	fighter.get_animation()->restart();
}