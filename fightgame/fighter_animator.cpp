#include "fighter_animator.h"

FighterAnimator::FighterAnimator(bones::GraphicsLoader& loader, std::map<FighterGraphics, std::string> links) :
	current_animation(nullptr)
{
	for (auto &graphic : links)
	{
		auto animation = loader.load_animation(graphic.second);
		animations[graphic.first] = animation;
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