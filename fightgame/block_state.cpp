#include "block_state.h"
#include "fighter.h"

void BlockState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::BLOCK_STAND);
}

void BlockState::tick(Fighter& fighter)
{

}

void BlockState::exit(Fighter& fighter)
{
	fighter.get_animation()->restart();
}