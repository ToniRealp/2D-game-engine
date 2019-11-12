#pragma once
#include "GameObject.h"
#include "Player.h"
#include "Brick.h"
class Ball :
	public GameObject
{
public:

	Ball(Rect _rect, Texture _texture, const GameObjects * _gameObjects);
	~Ball();
	void Update() override;
	bool GetSpawn();
	void SetSpawn();
	int GetLastTouched();
	
private:

	int speed;
	Vec2 direction;	
	bool collided = false;
	std::string lastTouched;
	bool spawn;
	GameObject *lastCollided;

	void IsColliding();

};

