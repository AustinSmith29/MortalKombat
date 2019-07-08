#include "fighter_animator.h"

FighterAnimator::FighterAnimator(std::map<FighterGraphics, bones::Animation> links) :
	current_animation(nullptr)
{
	for (auto &graphic : links)
	{
		animations[graphic.first] = graphic.second;
	}
	set_graphics(FighterGraphics::IDLE);
}

void FighterAnimator::set_graphics(FighterGraphics graphics)
{
	current_animation = &animations[graphics];
}

void FighterAnimator::flip_orientation()
{
	for (auto &a : animations)
	{
		a = a.flip();
	}
}

void FighterAnimator::play(SDL_Renderer* renderer, int x, int y)
{
	current_animation->play_animation(renderer, x, y);
}

bones::Animation* FighterAnimator::get_current_animation()
{
	return current_animation;
}