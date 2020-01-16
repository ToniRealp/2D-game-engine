#pragma once
#include "GameObject.h"
class Background :
	public GameObject
{
public:
	Background(Rect _rect, Texture _texture, const GameObjects * _gameObjects, std::string _tag="" );
	~Background();
	void Update() override;
};

