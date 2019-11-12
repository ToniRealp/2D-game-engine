#include "Brick.h"


Brick::Brick(Rect _rect, Texture _texture, const GameObjects * _gameObjects, std::string tag, int _score, BrickType _type) :GameObject(_rect, _texture, _gameObjects, tag),
score(_score), type(_type), currentTexture(0,0,0,0), frameSize(0,0), transition(false), player(""),colliderPosition(_rect)
{
	colliderPosition = { rect.position.x + rect.size.x / 2 - rect.size.y / 2 , rect.position.y - rect.size.x / 2 + rect.size.y / 2,rect.size.y,rect.size.x };
	collider = new RectCollider(colliderPosition);
	Vec2 textSize = renderer->GetTextureSize(texture.id);
	frameSize.x = textSize.x / 5;
	frameSize.y = textSize.y / 3;
	switch (type)
	{
	case BrickType::NORMAL:
		currentTexture = { 0, 0, frameSize.x, frameSize.y };
		break;
	case BrickType::HEAVY:
		currentTexture = { 0, frameSize.y, frameSize.x, frameSize.y };
		break;
	case BrickType::FIX:
		currentTexture = { 0, frameSize.y*2, frameSize.x, frameSize.y };
		break;
	default:
		break;
	}
}

Brick::~Brick(){}

void Brick::Update()
{
	collider->UpdatePosition(colliderPosition.position);
	frames++;
}

void Brick::Render()
{
	renderer->PushRotatedSprite(texture.id, currentTexture, rect, 90);

	if (transition && frames>=10)
	{
		frames = 0;
		switch (type)
		{
		case BrickType::NORMAL:
			currentTexture.position.x +=frameSize.x;
			if (currentTexture.position.x>=frameSize.x*5)
			{
				dynamic_cast<Player*>(gameObjects->at(player))->UpdateScore(score);
				deleteMe=true;
			}
			break;
		case BrickType::HEAVY:
			currentTexture.position.x += frameSize.x;
			if (currentTexture.position.x == frameSize.x * 2 || currentTexture.position.x == frameSize.x * 4)
			{
				transition = false;
			}
			else if (currentTexture.position.x >= frameSize.x * 5)
			{
				dynamic_cast<Player*>(gameObjects->at(player))->UpdateScore(score);
				deleteMe = true;
			}
			break;
		case BrickType::FIX:
			currentTexture.position.x += frameSize.x;
			if (currentTexture.position.x >= frameSize.x * 5)
			{
				transition = false;
				currentTexture.position.x = 0;
			}
			break;
		default:
			break;
		}
	}

}

void Brick::UpdateBrick(std::string _player) {
	player = _player;
	transition = true;
	frames = 0;
}