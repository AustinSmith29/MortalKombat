#include "crouch_state.h"
#include "fighter.h"

CrouchState::CrouchState()
{
	set_move_hook(FighterState::FightMoveHook::CROUCH);
}

void CrouchState::enter(Fighter& fighter, FighterStateMachine &machine, void* data)
{
	fighter.set_graphics(FighterGraphics::CROUCH);
}

void CrouchState::tick(Fighter& fighter, FighterStateMachine &machine)
{
}

void CrouchState::exit(Fighter &fighter, FighterStateMachine &machine)
{
	fighter.get_animation()->restart();
}