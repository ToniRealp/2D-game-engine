#include "Collider.h"


Collider::Collider(Rect _rect, const GameObjects * _gameObjects):GameObject(_rect,Texture("empty", "../../res/img/ball.png"),_gameObjects)
{
	collider = new RectCollider(_rect);
}

Collider::~Collider(){}

void Collider::Update()
{
	collider->UpdatePosition(rect.position);
}

void Collider::Render()
{
}
