#include "ai_util.h"
#include "fighter.h"

#include <random>
#include <algorithm>
#include <cmath>

static std::default_random_engine generator;
static std::uniform_real_distribution<double> distribution(0.0, 1.0);

double random()
{
	return distribution(generator);
}

unsigned int x_distance(Fighter& a, Fighter& b)
{
	return abs(a.get_position_x() - b.get_position_x());
}

static bool on_left(Fighter& subject, Fighter& target)
{
	if (subject.get_position_x() - target.get_position_x() < 0)
		return true;
	return false;
}

namespace Behavior
{
	void jump_towards(Fighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::JUMP_LEFT);
		}
	}

	void jump_away(Fighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::JUMP_LEFT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::JUMP_RIGHT);
		}
	}

	void move_towards(Fighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::MOVE_RIGHT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::MOVE_LEFT);
		}
	}

	void move_away(Fighter& subject, Fighter& target)
	{
		if (on_left(subject, target))
		{
			subject.set_state(FighterStateMachine::State::MOVE_LEFT);
		}
		else
		{
			subject.set_state(FighterStateMachine::State::MOVE_RIGHT);
		}
	}

	void idle(Fighter& subject, Fighter& target)
	{
		subject.set_state(FighterStateMachine::State::IDLE);
	}
}
