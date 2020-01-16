#pragma once
#include "GameObject.h"
enum POWERUPTYPE { EXTRA, MINI, SPEED };

class PowerUps :public GameObject
{
public:

	POWERUPTYPE type;

	PowerUps(Rect _rect, Texture _texture, const GameObjects * _gameObjects, int direction);
	~PowerUps();
	void Update() override;

private:
	int speed;
	int direction;
};

