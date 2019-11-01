#ifndef _CAGE_H
#define _CAGE_H

#include "fighter_animator.h"
#include "fightmove_input_handler.h"

#include <string>
#include <map>

std::map <FighterGraphics, bones::Animation> load_graphics(bones::GraphicsLoader& loader);
std::map <FightMoveInputHandler::ActivationKey, std::string> load_moves();

#endif