#include "cage.h"
#include "fighter.h"
#include "projectile_factory.h"

#include <map>

#define ANIMATIONS "data/johnnycage/animations/"

static Uint32 projectile_callback(Uint32 interval, void* param)
{
	Fighter *fighter = static_cast<Fighter*>(param);
	// if fighter has been hit before the projectile should launch... we
	// don't want it to launch.
	if (fighter->get_state()->get_state() != FighterStateMachine::State::FIGHT_MOVE) //ewww.. get_state()->get_state()
		return 0;
	auto projectile = ProjectileFactory::create(fighter->get_position_x(),
								fighter->get_position_y() - 50,
								fighter->get_orientation(),
								CAGE_PROJECTILE);
	fighter->add_projectile(std::move(projectile));
	return 0;
}

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
	anim_sources[FighterGraphics::SPECIAL_0] = loader.load_animation(ANIMATIONS "cage_fireball_throw.xml");

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
	moves[FightMoveInputHandler::make_key(CROUCH, "X,")] = { FighterGraphics::CROUCH_KICK_LOW, 5 };
	moves[FightMoveInputHandler::make_key(CROUCH, "A,")] = { FighterGraphics::CROUCH_KICK_HIGH, 5 };
	moves[FightMoveInputHandler::make_key(STAND, "D,F,A,")] = { FighterGraphics::SPECIAL_0, 5 };
	moves[FightMoveInputHandler::make_key(STAND, "D,Y,")] = { FighterGraphics::UPPERCUT, 5 };
	return moves;
}

void handle_fightmove(FightMove move, Fighter &fighter)
{
	if (move.animation == FighterGraphics::SPECIAL_0)
	{
		SDL_AddTimer(450, projectile_callback, &fighter);
	}
	fighter.set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
}
