#include "GameObject.h"

GameObject::GameObject():texture("",""),rect(Vec2(0,0),Vec2(0,0)) {}

GameObject::GameObject(Rect _rect, Texture _texture,const GameObjects *_gameObjects, std::string _tag):rect(_rect),texture(_texture),gameObjects(_gameObjects), tag(_tag), deleteMe(false)
{
	renderer = Renderer::Instance();
	renderer->LoadTexture(texture);	
}

GameObject::~GameObject()
{
	delete collider;
	collider = nullptr;
	renderer = nullptr;
	gameObjects = nullptr;
}

void GameObject::Render() {
	renderer->PushImage(texture.id, rect);
}

void GameObject::UpdateGameObjects(GameObjects *_gameObjects)
{
	gameObjects = _gameObjects;
}

Collision * GameObject::GetCollider()
{
	return collider;
}

std::string GameObject::GetTag()
{
	return tag;
}

Rect GameObject::GetRect()
{
	return rect;
}
