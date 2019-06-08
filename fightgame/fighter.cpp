#include "fighter.h"

Fighter::Fighter() : move_source(this)
{
	x = y = 0;
	x_vel = y_vel = 0;
	health = 100;
}

int Fighter::topleft_x()
{
	int w = current_animation->get_current_frame().sheet_clip.w;
	int topleft = x - (w / 2);
	return topleft;
}

int Fighter::topleft_y()
{
	int h = current_animation->get_current_frame().sheet_clip.h;
	int topleft = y - h;
	return topleft;
}

void Fighter::flip_orientation()
{

}

void Fighter::tick()
{
}

void Fighter::draw(SDL_Renderer* renderer)
{
	// "Anchor" of every frame is the bottom-middle.
	// This fixes the animation jumping around on the screen. 
	int draw_x = topleft_x();
	int draw_y = topleft_y();
	current_animation->play_animation(renderer, draw_x, draw_y);
}

void Fighter::handle_input_event(SDL_Event &event)
{
	move_source.process_event(event, DIRECTION_RIGHT);
	if (event.type == SDL_CONTROLLERBUTTONDOWN)
	{
		auto button = event.cbutton.button;
		if (button == SDL_CONTROLLER_BUTTON_DPAD_UP)
		{
		}
		if (button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		{
		}
	}
}

void Fighter::handle_button_press(Uint8 button)
{
	if (button == SDL_CONTROLLER_BUTTON_DPAD_UP)
	{
	}
}

void Fighter::handle_input_state(SDL_GameController* controller)
{
}