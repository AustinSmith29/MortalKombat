#include "easy_ai.h"

#include "ai_fighter.h"
#include "fighter.h"
#include "ai_util.h"

namespace EasyAI
{
	// TODO: Yes I know this is crap... just testing to make sure things are working.
	void logic(AIFighter& ai, Fighter& other)
	{
		int distance = ai.get_position_x() - other.get_position_x();
		if (distance > 50)
		{
			std::vector<std::pair<int, FighterStateMachine::State>> random_map = {
				{10, FighterStateMachine::State::JUMP_LEFT},
				{90, FighterStateMachine::State::MOVE_LEFT}
			};
			auto state = nonuni_random_state_from<FighterStateMachine::State>(random_map);
			ai.set_state(state);
		}
		else if (distance < -50)
		{
			std::vector<std::pair<int, FighterStateMachine::State>> random_map = {
				{10, FighterStateMachine::State::JUMP_RIGHT},
				{90, FighterStateMachine::State::MOVE_RIGHT}
			};
			auto state = nonuni_random_state_from<FighterStateMachine::State>(random_map);
			ai.set_state(state);
		}
		else
		{
			double move_chance = random();
			if (move_chance <= .05)
			{
				// retreat jump
				if (distance >= 0)
				{
					ai.set_state(FighterStateMachine::JUMP_RIGHT);
				}
				else
				{
					ai.set_state(FighterStateMachine::JUMP_LEFT);
				}
			}
			else if (move_chance <= .75)
			{
				std::vector<std::pair<int, FightMove>> random_map = {
					{25, {FighterGraphics::LOW_PUNCH, 5}},
					{25, {FighterGraphics::HIGH_PUNCH, 5}}, 
					{25, {FighterGraphics::HIGH_KICK, 5}},
					{25, {FighterGraphics::LOW_KICK, 5}},
				};
				auto move = nonuni_random_state_from<FightMove>(random_map);
				ai.set_state(FighterStateMachine::State::FIGHT_MOVE, &move);
			}
			else
			{
				ai.set_state(FighterStateMachine::IDLE);
			}
		}
	}
	
}