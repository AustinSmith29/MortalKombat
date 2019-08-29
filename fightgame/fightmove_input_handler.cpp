#include "fightmove_input_handler.h"
#include "user_fighter.h"

#define FLUSH_TIME_MS 250

static Uint32 timer_callback(Uint32 interval, void* param)
{
	FightMoveInputHandler* movesource = static_cast<FightMoveInputHandler*>(param);
	movesource->flush();
	return 0;
}

FightMoveInputHandler::FightMoveInputHandler(UserFighter& fighter, std::map<ActivationKey, FightMove*> move_map) :
	fighter(fighter), move_map(move_map), first_press(false)
{
}

/* 
   Codifies button presses. Direction parameter
   simply changes if right dpad = Forward or Backward.
*/
std::string get_input(InputEvent &event, Orientation direction)
{
	std::vector<std::string> input_queue;
	auto poll = [&input_queue, event, direction](InputButton btn, std::string encoding) {
		if (event.type == EventType::BUTTON_DOWN && event.button == btn)
		{
			if (btn == InputButton::BUTTON_RIGHT && direction == Orientation::RIGHT)
				encoding = "F";
			else if (btn == InputButton::BUTTON_LEFT && direction == Orientation::LEFT)
				encoding = "F";
			else if (btn == InputButton::BUTTON_LEFT || btn == InputButton::BUTTON_RIGHT)
				encoding = "b";
			input_queue.push_back(encoding);
		}
	};
	poll(InputButton::BUTTON_UP, "U");
	poll(InputButton::BUTTON_DOWN, "D");
	poll(InputButton::BUTTON_A, "A");
	poll(InputButton::BUTTON_X, "X");
	poll(InputButton::BUTTON_Y, "Y");
	poll(InputButton::BUTTON_B, "B");
	poll(InputButton::BUTTON_RIGHT, "R");
	poll(InputButton::BUTTON_LEFT, "L");
	input_queue.push_back("I"); // idle
	return input_queue[0];
}

/*
get input from gamepad
add it to input buffer
if input buffer contains move add it to the front of buffer
return move at front of buffer
*/
void FightMoveInputHandler::process_event(InputEvent &event, FightMoveHook hook,
										  Orientation direction)
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
		fighter.perform_fightmove(move_map[key]);
	}
}

void FightMoveInputHandler::flush()
{
	first_press = false;
	input_buffer.clear();
}

FightMoveInputHandler::ActivationKey FightMoveInputHandler::make_key(FightMoveHook hook, std::string input)
{
	return std::make_pair(hook, input);
}
