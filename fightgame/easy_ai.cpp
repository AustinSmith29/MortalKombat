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
			double jump_chance = random();
			if (jump_chance > .90)
			{
				ai.set_state(FighterStateMachine::JUMP_LEFT);
			}
			else
			{
				ai.set_state(FighterStateMachine::MOVE_LEFT);
			}
		}
		else if (distance < -50)
		{
			double jump_chance = random();
			if (jump_chance > .90)
			{
				ai.set_state(FighterStateMachine::JUMP_RIGHT);
			}
			else
			{
				ai.set_state(FighterStateMachine::MOVE_RIGHT);
			}
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
			else if (move_chance <= .25)
			{
				FightMove move = { FighterGraphics::LOW_PUNCH , 5 };
				ai.set_state(FighterStateMachine::FIGHT_MOVE, &move);
			}
			else if (move_chance <= .50)
			{
				FightMove move = { FighterGraphics::HIGH_PUNCH, 5 };
				ai.set_state(FighterStateMachine::FIGHT_MOVE, &move);
			}
			else if (move_chance <= .75)
			{
				FightMove move = { FighterGraphics::HIGH_KICK, 5 };
				ai.set_state(FighterStateMachine::FIGHT_MOVE, &move);
			}
			else if (move_chance <= .85)
			{
				FightMove move = { FighterGraphics::LOW_KICK, 5 };
				ai.set_state(FighterStateMachine::FIGHT_MOVE, &move);
			}
			else
			{
				ai.set_state(FighterStateMachine::IDLE);
			}
		}
	}
	
}