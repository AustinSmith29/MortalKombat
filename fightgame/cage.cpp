#include "cage.h"

#include <map>

#define ANIMATIONS "data/johnnycage/animations/"

void JohnnyCage::load_resources(bones::GraphicsLoader& loader)
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
	move_source.bind_owner(this);
	move_source.load_moves_from_file("data/johnnycage/moves.xml", loader);
	x = 150;
	y = 350;
	x_vel = y_vel = 0;
}

void JohnnyCage::process_move(Move& move)
{
	perform_fight_move(move.animation);
}
