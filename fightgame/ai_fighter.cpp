#include "ai_fighter.h"
#include <cmath>

AIFighter::AIFighter(FighterAnimator &animator) : Fighter(animator)
{
}

void AIFighter::tick(Fighter &other)
{
	int distance = abs(other.get_position_x() - get_position_x());
	if (distance < 50)
	{
		if (!state_machine->is_input_locked())
		{
			FightMove move = { FighterGraphics::LOW_PUNCH , 5 };
			set_state(FighterStateMachine::FIGHT_MOVE, &move);
		}
	}
	Fighter::tick();
}