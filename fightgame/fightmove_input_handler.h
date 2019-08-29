#ifndef _FIGHTMOVE_INPUT_HANDLER_H
#define _FIGHTMOVE_INPUT_HANDLER_H

#include "fighter_state.h"
#include "fightmove.h"
#include "input_device.h"

#include <string>
#include <vector>
#include <map>
#include <functional>

class UserFighter;
class FightMoveInputHandler
{
public:
	using ActivationKey = std::pair<FightMoveHook, std::string>;

	FightMoveInputHandler(UserFighter &handler, std::map<ActivationKey, FightMove*> move_map);
	FightMoveInputHandler(const FightMoveInputHandler& handler) = delete;
	FightMoveInputHandler& operator = (const FightMoveInputHandler& handler) = delete;

	void process_event(InputEvent &event, FightMoveHook hook, Orientation direction);
	void flush();

	static ActivationKey make_key(FightMoveHook hook, std::string input);

private:
	std::vector<std::string> input_buffer;
	std::map<ActivationKey, FightMove*> move_map;
	UserFighter& fighter;
	bool first_press; /// start flush timer once this is true
};
#endif