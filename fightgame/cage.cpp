#include "cage.h"
#include "fighter.h"

#include <map>
#include <iostream>

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

	return anim_sources;
}

std::map <FightMoveInputHandler::ActivationKey, FightMove> load_moves()
{
	std::map <FightMoveInputHandler::ActivationKey, FightMove> moves;
	const FighterState::FightMoveHook STAND = FighterState::FightMoveHook::STAND;
	const FighterState::FightMoveHook CROUCH = FighterState::FightMoveHook::CROUCH;
	moves[FightMoveInputHandler::make_key(STAND, "X,")] = { FighterGraphics::LOW_PUNCH, 5 };
	moves[FightMoveInputHandler::make_key(STAND, "Y,")] = { FighterGraphics::HIGH_PUNCH, 5 };
	moves[FightMoveInputHandler::make_key(STAND, "A,")] = { FighterGraphics::LOW_KICK, 5 };
	moves[FightMoveInputHandler::make_key(STAND, "B,")] = { FighterGraphics::LOW_KICK, 5 };
	moves[FightMoveInputHandler::make_key(CROUCH, "X,")] = { FighterGraphics::LOW_PUNCH, 5 };
	moves[FightMoveInputHandler::make_key(CROUCH, "A,")] = { FighterGraphics::LOW_KICK, 5 };
	return moves;
}

void handle_fightmove(FightMove move, Fighter &fighter)
{
	fighter.set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
}
