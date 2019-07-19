#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "fighter_animator.h"
#include "fighter_state_machine.h"
#include <memory>

class Fighter
{
public:
	Fighter(FighterAnimator &animator);
	Fighter(const Fighter& other);
	Fighter& operator = (const Fighter& other) = delete;

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	Orientation get_orientation();
	bones::Animation* get_animation();
	FighterStateMachine* get_state();
	void set_state(FighterStateMachine::State state, void* data = nullptr);

	void move_left();
	void move_right();

	int get_velocity_x();
	void set_velocity_x(int val);
	int get_velocity_y();
	void set_velocity_y(int val);
	
	int get_position_x();
	void set_position_x(int val);
	int get_position_y();
	void set_position_y(int val);

	void set_graphics(FighterGraphics graphics);
	void flip_orientation();
	void face(int x);

	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	FighterAnimator animator;
	std::unique_ptr<FighterStateMachine> state_machine;
	Orientation orientation;
};
#endif