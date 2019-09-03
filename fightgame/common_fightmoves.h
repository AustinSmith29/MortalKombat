#ifndef COMMON_FIGHTMOVES_H
#define COMMON_FIGHTMOVES_H

#include "basic_fightmove.h"
#include "uppercut_fightmove.h"
#include "throw_fightmove.h"

extern BasicFightMove low_punch;
extern BasicFightMove high_punch;
extern BasicFightMove low_kick;
extern BasicFightMove high_kick;
extern BasicFightMove crouch_kick_low;
extern BasicFightMove crouch_kick_high;
extern UppercutFightMove uppercut;
extern ThrowFightMove throw_enemy;
// THESE ARE NOT BASICFIGHTMOVES... JUST FOR TESTING
extern BasicFightMove special_1;

#endif