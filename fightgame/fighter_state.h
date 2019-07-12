#ifndef _FIGHTER_STATE
#define _FIGHTER_STATE

enum class Orientation
{
	LEFT,
	RIGHT
};

class FighterStateMachine;
class Fighter;
class FighterState
{
public:
	enum class FightMoveHook {
		NONE,
		STAND,
		CROUCH,
		JUMP
	};
	virtual void enter(Fighter &fighter, FighterStateMachine &machine, void* data) = 0;
	virtual void tick(Fighter &fighter, FighterStateMachine &machine) = 0;
	virtual void exit(Fighter &fighter, FighterStateMachine &machine) = 0;

	bool is_input_locked();
	void lock_input();
	void unlock_input();
	FightMoveHook get_move_hook();
protected:
	void set_move_hook(FightMoveHook hook);
private:
	bool lock{ false };
	FightMoveHook move_hook{ FightMoveHook::STAND };
};
#endif