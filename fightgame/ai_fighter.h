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
	using HandlerFunc = std::function<void(FightMove,Fighter&)>;

	AIFighter(FighterAnimator &animator, std::function<void(AIFighter& ai, Fighter& other)> logic, HandlerFunc handler); 
	AIFighter(const AIFighter& aifighter) = delete;
	AIFighter& operator =(const AIFighter& aifighter) = delete;

	void tick(Fighter &other);
	void do_move(FightMove& move);
private:
	std::function<void(AIFighter& ai, Fighter& other)> logic_func;
	HandlerFunc fightmove_handler;
	bool action_chosen{ false };
};
#endif