#include "common_fightmoves.h"
#include "standard_effect.h"
#include "fighter_animator.h"

std::shared_ptr<Effect> standard_effect = std::make_shared<StandardEffect>();
BasicFightMove low_punch(FighterGraphics::LOW_PUNCH, 5, standard_effect);
BasicFightMove high_punch(FighterGraphics::HIGH_PUNCH, 5, standard_effect);
BasicFightMove low_kick(FighterGraphics::LOW_KICK, 5, standard_effect);
BasicFightMove high_kick(FighterGraphics::HIGH_KICK, 5, standard_effect);
BasicFightMove crouch_kick_low(FighterGraphics::CROUCH_KICK_LOW, 5, standard_effect);
BasicFightMove crouch_kick_high(FighterGraphics::CROUCH_KICK_HIGH, 5, standard_effect);
UppercutFightMove uppercut(5);
ThrowFightMove throw_enemy;
// THESE ARE NOT BASICFIGHTMOVES... JUST FOR TESTING
BasicFightMove special_1(FighterGraphics::SPECIAL_1, 5, standard_effect);
