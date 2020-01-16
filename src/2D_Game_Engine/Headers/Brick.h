#pragma once
#include "GameObject.h"
#include "Player.h"
#include <chrono>
enum class BrickType { NORMAL, HEAVY, FIX };
class Brick :
	public GameObject
{
public:
	Brick(Rect _rect, Texture _texture, const GameObjects * _gameObjects, std::string tag, int _score, BrickType _type);
	~Brick();
	void Update() override;
	void Render() override;
	void UpdateBrick(std::string);
private:
	int frames;
	bool transition;
	int score;
	std::string player;
	BrickType type;
	Rect currentTexture;
	Vec2 frameSize;
	Rect colliderPosition;

};

