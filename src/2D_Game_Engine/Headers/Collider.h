#pragma once
#include "GameObject.h"
class Collider :
	public GameObject
{
public:
	Collider(Rect _rect,const GameObjects *_gameObjects);
	~Collider();
	void Update() override;
	void Render() override;
};

