#include "../Headers/PowerUps.h"


PowerUps::PowerUps(Rect _rect, Texture _texture, const GameObjects * _gameObjects, int _direction):GameObject(_rect,_texture,_gameObjects,"PowerUp") 
{
	collider = new RectCollider(Rect(rect.position, rect.size));
	int random;
	random = rand() % 3;
	switch (random)
	{
	case 0:
		type = POWERUPTYPE::EXTRA;
		break;
	case 1:
		type = POWERUPTYPE::MINI;
		break;
	case 2:
		type = POWERUPTYPE::SPEED;
		break;
	default:
		break;
	}
	direction = _direction;
	speed = 3;
}


PowerUps::~PowerUps()
{}


void PowerUps::Update() {
	rect.position.x = rect.position.x + direction * speed;
	collider->UpdatePosition(rect.position);


}