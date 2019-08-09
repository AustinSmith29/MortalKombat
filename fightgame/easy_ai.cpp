#include "easy_ai.h"

#include "ai_fighter.h"
#include "fighter.h"
#include "ai_util.h"

namespace EasyAI
{
	void select_fightmove(AIFighter& a, Fighter& b)
	{
		std::vector<std::pair<int, FightMove>> random_map = {
			{20, {FighterGraphics::LOW_PUNCH, 5}},
			{20, {FighterGraphics::HIGH_PUNCH, 5}}, 
			{20, {FighterGraphics::HIGH_KICK, 5}},
			{20, {FighterGraphics::LOW_KICK, 5}},
			{20, {FighterGraphics::SPECIAL_0, 5}},
		};
		auto move = nonuni_random_state_from<FightMove>(random_map);
		a.do_move(move);
	}
	
	void logic(AIFighter& ai, Fighter& other)
	{
		auto distance = x_distance(ai, other);
		if (distance > 50)
		{
			std::vector<std::pair<int, Behavior::Behavior>> random_map = {
				{5, Behavior::Behavior(FightMove {FighterGraphics::SPECIAL_0, 5})},
				{10, Behavior::Behavior(Behavior::jump_towards)},
				{85, Behavior::Behavior(Behavior::move_towards)},
			};
			auto state = nonuni_random_state_from<Behavior::Behavior>(random_map);
			state(ai, other);
		}
		else
		{
			if (other.get_state()->get_state() == FighterStateMachine::State::FIGHT_MOVE && random() <= .75)
			{
				ai.set_state(FighterStateMachine::State::BLOCK);
			}
			else
			{
				std::vector<std::pair<int, Behavior::BehaviorFunc>> random_map = {
					{5, Behavior::jump_away},
					{70, select_fightmove},
					{25, Behavior::idle}
				};
				auto behavior = nonuni_random_state_from<Behavior::BehaviorFunc>(random_map);
				behavior(ai, other);
			}
		}
	}
	
}