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
	MoveSource* movesource = static_cast<MoveSource*>(param);
	movesource->flush();
	return 0;
}

MoveSource::MoveSource(Fighter *fighter)
{
	owner = fighter;
	first_press = false;
}

MoveSource::~MoveSource()
{
	input_buffer.clear();
	move_map.clear();
	owner = nullptr;
}

void MoveSource::bind_move(std::string key, Move move)
{
	move_map[key] = move;
}

void MoveSource::load_moves_from_file(std::string filename, bones::GraphicsLoader &loader)
{
	std::ifstream in(filename);
	if (!in)
	{
		throw std::runtime_error("Could not open animation file: " + filename);
	}
	std::stringstream ss;
	ss << in.rdbuf();
	in.close();
	std::string data(ss.str());

	xml_document<> doc;
	doc.parse<0>(&(data[0]));
	xml_node<>* root = doc.first_node();
	for (xml_node<>* move = root->first_node(); move; move = move->next_sibling())
	{
		std::string name = move->first_attribute("name")->value();
		std::string key = move->first_attribute("key")->value();
		std::string anim_file = move->first_attribute("animation")->value();
		bones::Animation animation = loader.load_animation(anim_file);
		Move move_obj;
		move_obj.animation = animation;
		move_obj.damage = 0;
		move_obj.name = name;
		move_map[key] = move_obj;
	}
}

/* 
   Codifies button presses. Direction parameter
   simply changes if right dpad = Forward or Backward.
*/
std::string get_input(SDL_Event &event, int direction)
{
	std::vector<std::string> input_queue;
	auto poll = [&input_queue, event, direction](SDL_GameControllerButton btn, std::string encoding) {
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == btn)
		{
			if (btn == SDL_CONTROLLER_BUTTON_DPAD_RIGHT && direction == DIRECTION_RIGHT)
				encoding = "F";
			else if (btn == SDL_CONTROLLER_BUTTON_DPAD_LEFT && direction == DIRECTION_LEFT)
				encoding = "F";
			else if (btn == SDL_CONTROLLER_BUTTON_DPAD_LEFT || btn == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				encoding = "B";
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
void MoveSource::process_event(SDL_Event &event, int direction)
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

	std::string key;
	for (const auto& piece : input_buffer) key += (piece + ",");
	if (move_map.find(key) != move_map.end())
	{
		owner->process_move(move_map[key]);
	}
}

void MoveSource::flush()
{
	first_press = false;
	input_buffer.clear();
}
