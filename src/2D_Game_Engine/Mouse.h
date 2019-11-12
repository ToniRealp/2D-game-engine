#pragma once
#include "GameObject.h"
class Mouse : public GameObject
{
public:
	Mouse(Rect _rect, Texture _texture,const GameObjects * _gameObjects);
	~Mouse();
	void Update() override;
};

