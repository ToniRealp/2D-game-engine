#pragma once
#include "GameObject.h"
#include "Player.h"
#include <sstream>
class DynText :
	public GameObject
{
public:

	DynText(Rect _rect,const GameObjects * _gameObjects, Player *player, Font font,std::string _tag = "");
	~DynText();
	void Update() override;

private:

	Player *player;
	Font font;
	int score;

};

