#ifndef _AI_FIGHTER_H
#define _AI_FIGHTER_H

#include "fighter.h"
#include <memory>
#include <functional>

//TODO: AIFighter should take in a std::function that points to
// a function which drives the ai.
class AIFighter : public Fighter
{
public:
	AIFighter(FighterAnimator &animator, std::function<void(AIFighter& ai, Fighter& other)> logic); 
	AIFighter(const AIFighter& aifighter) = delete;
	AIFighter& operator =(const AIFighter& aifighter) = delete;

	void tick();
	void driver(Fighter& other);
private:
	std::function<void(AIFighter& ai, Fighter& other)> logic_func;
	bool action_chosen{ false };
};
#endif