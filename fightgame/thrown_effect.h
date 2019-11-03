#ifndef _THROWN_EFFECT_H
#define _THROWN_EFFECT_H

#include "audio.h"
#include "effect.h"

#include <memory>

class ThrownEffect : public Effect
{
public:
	ThrownEffect();
	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	FighterStateMachine::State get_next_state() override;

private:
	std::unique_ptr<bones::AudioClip> hurtsound;
};

#endif