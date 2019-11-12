#pragma once
#include "Scene.h"
#include "Button.h"
#include "Mouse.h"

class Menu :public Scene
{
	
public:
	Menu(bool*);
	~Menu();
	void Update() override;
private:
	bool *music;
	Button *musicOn, *musicOff;
};

