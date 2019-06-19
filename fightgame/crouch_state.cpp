#include "crouch_state.h"
#include "fighter.h"

CrouchState::CrouchState()
{
	set_move_hook(FighterState::FightMoveHook::CROUCH);
}

void CrouchState::enter(Fighter& fighter)
{
	fighter.set_graphics(FighterGraphics::CROUCH);
}

void CrouchState::tick(Fighter& fighter)
{
}

void CrouchState::exit(Fighter &fighter)
{
	fighter.get_animation()->restart();
}