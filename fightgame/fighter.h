#ifndef _FIGHTER_H
#define _FIGHTER_H

#include "graphics.h"
#include "movesource.h"
#include "fighter_state.h"

enum class FighterGraphics
{
	IDLE,
	CROUCH,
	JUMP,
	JUMP_FORWARD,
	JUMP_BACKWARD,
	WALK_FORWARD,
	WALK_BACKWARD,
	BLOCK_STAND,
	BLOCK_CROUCH,
	FIGHT_MOVE
};

class Fighter
{
public:

	Fighter();
	Fighter(Fighter& rhs) = delete;
	Fighter(Fighter&& rhs) = delete;

	void handle_input_event(SDL_Event& event);
	void handle_input_state(SDL_GameController* controller);

	virtual void load_resources(bones::GraphicsLoader& loader) = 0;
	virtual void process_move(Move& move) = 0;

	/* Gets the top left coords of starting position of current animation frame.
	 * Needed to adjust collision box positions and drawing positions.
	 */
	int topleft_x();
	int topleft_y();

	void set_graphics(FighterGraphics graphics);
	void flip_orientation();
	void tick();
	void draw(SDL_Renderer* renderer);

	friend class Collider;

protected:
	int x, y;
	int x_vel, y_vel;
	int health;
	MoveSource move_source;
	bones::Animation* current_animation;

private:
	void handle_button_press(Uint8 button);
};
#endif