#pragma once
#include "Types.h"
class Input
{
public:
	Input();
	~Input();
	static Vec2 mousePos;
	static bool isClicked;
	static bool W;
	static bool A;
	static bool S;
	static bool D;
	static bool P;
	static bool UP;
	static bool DOWN;
	static bool LEFT;
	static bool RIGHT;
	static bool ESC;
	static bool SPACE;
};

