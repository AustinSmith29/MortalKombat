#ifndef _STANDARD_EFFECT_H
#define _STANDARD_EFFECT_H

#include "effect.h"
#include "audio.h"

#include <memory>

class StandardEffect : public Effect
{
public:
	StandardEffect();
	void enter(Fighter& fighter) override;
	bool is_complete(Fighter& fighter) override;
	void exit(Fighter& fighter) override;
	FighterStateMachine::State get_next_state() override;
private:
	FighterStateMachine::State next_state;
	bool fall{ false };
	bones::AudioClip* soundeffect;
};
#endif