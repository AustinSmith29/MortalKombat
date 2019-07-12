#include "cage.h"

#include <map>

#define ANIMATIONS "data/johnnycage/animations/"

std::map<FighterGraphics, bones::Animation> load_graphics(bones::GraphicsLoader& loader)
{
	std::map <FighterGraphics, bones::Animation> anim_sources;
	anim_sources[FighterGraphics::IDLE] = loader.load_animation(ANIMATIONS "cage_idle.xml");
	anim_sources[FighterGraphics::CROUCH] = loader.load_animation(ANIMATIONS "cage_crouch.xml");
	bones::Animation walk_forward = loader.load_animation(ANIMATIONS "cage_walk.xml");
	anim_sources[FighterGraphics::WALK_FORWARD] = walk_forward;
	anim_sources[FighterGraphics::WALK_BACKWARD] = walk_forward.reverse();
	anim_sources[FighterGraphics::JUMP] = loader.load_animation(ANIMATIONS "cage_jump_up.xml");
	bones::Animation jump_forward = loader.load_animation(ANIMATIONS "cage_jump_move.xml");
	anim_sources[FighterGraphics::JUMP_FORWARD] = jump_forward;
	anim_sources[FighterGraphics::JUMP_BACKWARD] = jump_forward.reverse();
	anim_sources[FighterGraphics::BLOCK] = loader.load_animation(ANIMATIONS "cage_block.xml");
	return anim_sources;
}

std::map <FightMoveInputHandler::ActivationKey, FightMove> load_moves()
{
	std::map <FightMoveInputHandler::ActivationKey, FightMove> moves;
	return moves;
}

void handle_fightmove(FightMove move)
{

}
