#pragma once
#include <string>
#include <map>
#include "Types.h"
#include "Renderer.h"
#include "Collision.h"
#include "Input.h"

class GameObject;
typedef std::map<std::string, GameObject*> GameObjects;

//GameObject* find(GameObjects gameObjects, std::string key )
//{
//	for (size_t i = 0; i < gameObjects.size(); i++)
//	{
//		if(gameObjects[i].first==key)
//			return gameObjects[i].second;
//	}
//}

class GameObject
{
protected:
	std::string tag;
	Texture texture;
	Rect rect;
	Renderer *renderer;
	const GameObjects *gameObjects;
	Collision* collider;

public:
	bool deleteMe;
	GameObject();
	GameObject(Rect _rect, Texture _texture, const GameObjects * _gameObjects, std::string _tag = "");
	~GameObject();

	virtual void Render();
	virtual void Update()=0;
	void UpdateGameObjects(GameObjects *_gameObjects);
	Collision* GetCollider();
	std::string GetTag();
	Rect GetRect();
};
