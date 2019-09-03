#include "cage.h"
#include "fighter.h"
#include "projectile_factory.h"
#include "fighter_animator.h"
#include "common_fightmoves.h"
#include "projectile_fightmove.h"

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
	anim_sources[FighterGraphics::CROUCH_BLOCK] = loader.load_animation(ANIMATIONS "cage_block_low.xml");
	anim_sources[FighterGraphics::LOW_PUNCH] = loader.load_animation(ANIMATIONS "cage_punch_low_right.xml");
	anim_sources[FighterGraphics::LOW_KICK] = loader.load_animation(ANIMATIONS "cage_kick_low.xml");
	anim_sources[FighterGraphics::HIGH_PUNCH] = loader.load_animation(ANIMATIONS "cage_punch_high_right.xml");
	anim_sources[FighterGraphics::HIGH_KICK] = loader.load_animation(ANIMATIONS "cage_kick_high.xml");
	anim_sources[FighterGraphics::STUN_HIGH] = loader.load_animation(ANIMATIONS "cage_stun_high.xml");
	anim_sources[FighterGraphics::STUN_LOW] = loader.load_animation(ANIMATIONS "cage_stun_low.xml");
	anim_sources[FighterGraphics::CROUCH_KICK_LOW] = loader.load_animation(ANIMATIONS "cage_kick_crouch_low.xml");
	anim_sources[FighterGraphics::CROUCH_KICK_HIGH] = loader.load_animation(ANIMATIONS "cage_kick_crouch_high.xml");
	anim_sources[FighterGraphics::FALL] = loader.load_animation(ANIMATIONS "cage_fall.xml");
	anim_sources[FighterGraphics::UPPERCUT] = loader.load_animation(ANIMATIONS "cage_uppercut.xml");
	anim_sources[FighterGraphics::THROW_TRY] = loader.load_animation(ANIMATIONS "cage_throw_try.xml");
	anim_sources[FighterGraphics::THROW_COMPLETE] = loader.load_animation(ANIMATIONS "cage_throw_complete.xml");
	anim_sources[FighterGraphics::THROWN] = loader.load_animation(ANIMATIONS "cage_thrown.xml");
	anim_sources[FighterGraphics::SPECIAL_0] = loader.load_animation(ANIMATIONS "cage_fireball_throw.xml");

	return anim_sources;
}

std::map <FightMoveInputHandler::ActivationKey, FightMove*> load_moves()
{
	std::map <FightMoveInputHandler::ActivationKey, FightMove*> moves;
	const FightMoveHook STAND = FightMoveHook::STAND;
	const FightMoveHook CROUCH = FightMoveHook::CROUCH;
	moves[FightMoveInputHandler::make_key(STAND, "X,")] = &low_punch;
	moves[FightMoveInputHandler::make_key(STAND, "Y,")] = &high_punch;
	moves[FightMoveInputHandler::make_key(STAND, "A,")] = &low_kick;
	moves[FightMoveInputHandler::make_key(STAND, "B,")] = &high_kick;
	moves[FightMoveInputHandler::make_key(CROUCH, "X,")] = &crouch_kick_low;
	moves[FightMoveInputHandler::make_key(CROUCH, "A,")] = &crouch_kick_high;
	moves[FightMoveInputHandler::make_key(STAND, "D,F,A,")] = &cage_projectile_fightmove;
	//moves[FightMoveInputHandler::make_key(STAND, "D,Y,")] = &uppercut;
	moves[FightMoveInputHandler::make_key(STAND, "D,Y,")] = &throw_enemy;
	moves[FightMoveInputHandler::make_key(STAND, "F,D,F,")] = &throw_enemy;
	return moves;
}
