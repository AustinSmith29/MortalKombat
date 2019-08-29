#ifndef _UPPERCUT_FIGHTMOVE
#define _UPPERCUT_FIGHTMOVE

#include "fightmove.h"

/* TODO: Delete this class and Extract apply_effect to seperate 
         Effect. Do the Type Class pattern.
*/
class UppercutFightMove : public FightMove
{
public:
	UppercutFightMove() = default;
	UppercutFightMove(int damage);

	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override {};
	void apply_effect(Fighter& fighter) override;
private:
	int damage;
};

static UppercutFightMove uppercut(5);
#endif