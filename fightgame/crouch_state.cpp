#include "crouch_state.h"
#include "fighter.h"

CrouchState::CrouchState(FighterStateMachine& machine)
	: FighterState(machine, FightMoveHook::CROUCH)
{
}

void CrouchState::enter(void* data)
{
	fighter.set_graphics(FighterGraphics::CROUCH);
}

void CrouchState::tick()
{
}

void CrouchState::exit()
{
	fighter.get_animation()->restart();
}