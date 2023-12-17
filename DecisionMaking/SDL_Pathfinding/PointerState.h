#pragma once
typedef void (*func_t)();

class PointerState
{
protected:
	func_t enter;
	func_t exit;
	func_t update;
public:
	PointerState(func_t enter, func_t exit, func_t update);
	void Enter();
	void Exit();
	void Update();
};

