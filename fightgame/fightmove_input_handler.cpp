#include "movesource.h"
#include "fighter.h"
#include "rapidxml.hpp"

#include <stdexcept>
#include <fstream>
#include <sstream>

#define FLUSH_TIME_MS 250

using namespace rapidxml;

static Uint32 timer_callback(Uint32 interval, void* param)
{
	FightMoveInputHandler* movesource = static_cast<FightMoveInputHandler*>(param);
	movesource->flush();
	return 0;
}

FightMoveInputHandler::FightMoveInputHandler(HandlerFunc func, std::map<ActivationKey, FightMove> move_map)
{
}

/* 
   Codifies button presses. Direction parameter
   simply changes if right dpad = Forward or Backward.
*/
std::string get_input(SDL_Event &event, Orientation direction)
{
	std::vector<std::string> input_queue;
	auto poll = [&input_queue, event, direction](SDL_GameControllerButton btn, std::string encoding) {
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == btn)
		{
			if (btn == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && direction == Orientation::RIGHT)
				encoding = "F";
			else if (btn == SDL_CONTROLLER_BUTTON_DPAD_LEFT && direction == Orientation::LEFT)
				encoding = "F";
			else if (btn == SDL_CONTROLLER_BUTTON_DPAD_LEFT || btn == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				encoding = "b";
			input_queue.push_back(encoding);
		}
	};
	poll(SDL_CONTROLLER_BUTTON_DPAD_UP, "U");
	poll(SDL_CONTROLLER_BUTTON_DPAD_DOWN, "D");
	poll(SDL_CONTROLLER_BUTTON_A, "A");
	poll(SDL_CONTROLLER_BUTTON_X, "X");
	poll(SDL_CONTROLLER_BUTTON_Y, "Y");
	poll(SDL_CONTROLLER_BUTTON_B, "B");
	poll(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, "R");
	poll(SDL_CONTROLLER_BUTTON_DPAD_LEFT, "L");
	input_queue.push_back("I"); // idle
	return input_queue[0];
}

/*
get input from gamepad
add it to input buffer
if input buffer contains move add it to the front of buffer
return move at front of buffer
*/
void FightMoveInputHandler::process_event(SDL_Event &event, FighterState::FightMoveHook hook, Orientation direction)
{
	auto input = get_input(event, direction);
	if (input != "I")
	{
		input_buffer.push_back(input);
		if (!first_press)
		{
			first_press = true;
			SDL_AddTimer(FLUSH_TIME_MS, timer_callback, this);
		}
	}

	std::string input_seq;
	for (const auto& piece : input_buffer) input_seq += (piece + ",");
	auto key = std::make_pair(hook, input_seq);
	if (move_map.find(key) != move_map.end())
	{
		handler(move_map[key]);
	}
}

void FightMoveInputHandler::flush()
{
	first_press = false;
	input_buffer.clear();
}
