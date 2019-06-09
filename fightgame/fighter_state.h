#ifndef _FIGHTER_STATE
#define _FIGHTER_STATE

enum class Orientation
{
	LEFT,
	RIGHT
};

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
	virtual void enter(Fighter &fighter) = 0;
	virtual void tick(Fighter &fighter) = 0;
	virtual void exit(Fighter &fighter) = 0;

	bool is_complete();
	void finish();
	FightMoveHook get_move_hook();
protected:
	void set_move_hook(FightMoveHook hook);
private:
	bool complete{ false };
	FightMoveHook move_hook{ FightMoveHook::NONE };
};
#endif