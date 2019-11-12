#pragma once
#include "GameObject.h"
#include "Background.h"
#include "PowerUps.h"
#include <queue>
class Player :
	public GameObject
{
private:

	enum class PlayerState {UP,DOWN,IDLE};
	PlayerState state = PlayerState::IDLE;
	int movementSpeed, baseSpeed;
	int playerNum;
	int score;
	int health;
	float pTime;
	bool pActive;
	Texture healthTexture;
	Rect colliderPosition;

	void ResetPowerUps();

public:

	Player(Rect _rect, Texture _texture, const GameObjects * _gameObjects, std::string tag, int num, int _movSpeed);
	~Player();

	void Update() override;
	void Render() override;
	void UpdateScore(int _score);
	void UpdateHealth();
	int GetHealth();
	int GetScore();
	int GetPlayerNum();

};

