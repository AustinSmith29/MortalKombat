#ifndef _AI_FIGHTER_H
#define _AI_FIGHTER_H

#include "fighter.h"
#include <memory>

//TODO: AIFighter should take in a std::function that points to
// a function which drives the ai.
class AIFighter : public Fighter
{
public:
	AIFighter(FighterAnimator &animator); 
	AIFighter(const AIFighter& aifighter) = delete;
	AIFighter& operator =(const AIFighter& aifighter) = delete;

	void tick(Fighter &other);
};
#endif