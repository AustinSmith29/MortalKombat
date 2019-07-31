#include "easy_ai.h"

#include "ai_fighter.h"
#include "fighter.h"
#include "ai_util.h"

namespace EasyAI
{
	void select_fightmove(Fighter& a, Fighter& b)
	{
		std::vector<std::pair<int, FightMove>> random_map = {
			{25, {FighterGraphics::LOW_PUNCH, 5}},
			{25, {FighterGraphics::HIGH_PUNCH, 5}}, 
			{25, {FighterGraphics::HIGH_KICK, 5}},
			{25, {FighterGraphics::LOW_KICK, 5}},
		};
		auto move = nonuni_random_state_from<FightMove>(random_map);
		a.set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
	}
	
	void logic(AIFighter& ai, Fighter& other)
	{
		auto distance = x_distance(ai, other);
		if (distance > 50)
		{
			std::vector<std::pair<int, Behavior::BehaviorFunc>> random_map = {
				{10, Behavior::jump_towards},
				{90, Behavior::move_towards}
			};
			auto state = nonuni_random_state_from<Behavior::BehaviorFunc>(random_map);
			state(ai, other);
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