#ifndef UPPERCUT_EFFECT_H
#define UPPERCUT_EFFECT_H

#include "effect.h"

class UppercutEffect : public Effect
{
public: 
	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	FighterStateMachine::State get_next_state() override;
};
#endif