#ifndef _FIGHTER_ANIMATOR_H
#define _FIGHTER_ANIMATOR_H

#include "graphics.h"

#include <array>
#include <map>

enum FighterGraphics
{
	IDLE,
	CROUCH,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD,
	WALK_FORWARD,
	WALK_BACKWARD,

	BLOCK,
	HIGH_PUNCH,
	LOW_PUNCH,
	HIGH_KICK,
	LOW_KICK,
	LEG_SWEEP,
	UPPERCUT,
	ROUNDHOUSE,

	CROUCH_BLOCK,
	CROUCH_PUNCH,
	CROUCH_KICK_LOW,
	CROUCH_KICK_HIGH,

	JUMP_KICK,

	SPECIAL_0,
	SPECIAL_1,
	SPECIAL_2,
	SPECIAL_3,
	SPECIAL_4,

	TOTAL
};

class FighterAnimator
{
public:
	FighterAnimator(bones::GraphicsLoader &loader, std::map<FighterGraphics, std::string>);

	void set_graphics(FighterGraphics graphics);
	void flip_orientation();
	void play(SDL_Renderer* renderer, int x, int y);

private:
	bones::Animation* current_animation;
	std::array<bones::Animation, FighterGraphics::TOTAL> animations;
};
#endif