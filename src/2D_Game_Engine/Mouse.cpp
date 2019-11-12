#include "Mouse.h"


Mouse::Mouse(Rect _rect, Texture _texture,const GameObjects *_gameObjects):GameObject(_rect,_texture, _gameObjects)
{
	collider = new RectCollider(rect);
}

Mouse::~Mouse()
{
	renderer = nullptr;
}

void Mouse::Update()
{
	rect.position = Vec2(Vec2(Input::mousePos.x - 75, Input::mousePos.y - 50));
	collider->UpdatePosition(rect.position);
}

