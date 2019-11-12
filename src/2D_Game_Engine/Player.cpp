#include "Player.h"


Player::Player(Rect _rect, Texture _texture, const GameObjects * _gameObjects,std::string tag, int num, int _movSpeed):GameObject(_rect,_texture,_gameObjects, tag),
playerNum(num),score(0), movementSpeed(_movSpeed), health(3),healthTexture("platform", "../../res/img/platform.png"),colliderPosition(_rect)
{
	baseSpeed = movementSpeed = 5;
	colliderPosition = { rect.position.x + rect.size.x / 2 - rect.size.y / 2 , rect.position.y - rect.size.x / 2 + rect.size.y / 2,rect.size.y,rect.size.x };
	collider = new RectCollider(colliderPosition);
	renderer->LoadTexture(healthTexture);
	pActive = false;
}

Player::~Player(){}

void Player::Update()
{
	colliderPosition = { rect.position.x + rect.size.x / 2 - rect.size.y / 2 , rect.position.y - rect.size.x / 2 + rect.size.y / 2,rect.size.y,rect.size.x };
	collider->UpdatePosition(colliderPosition.position);

	switch (playerNum)
	{
	case 1:
		if (Input::W) state = PlayerState::UP;
		else if (Input::S) state = PlayerState::DOWN;
		else state = PlayerState::IDLE;
		break;

	case 2:
		if (Input::UP) state = PlayerState::UP;
		else if (Input::DOWN) state = PlayerState::DOWN;
		else state = PlayerState::IDLE;
		break;

	default:
		break;
	}

	switch (state)
	{
	case Player::PlayerState::UP:
		if (collider->Collides(*gameObjects->at("topCollider")->GetCollider())!=Tools::CollSide::BOTTOM)
		rect.position.y -= movementSpeed;
		break;

	case Player::PlayerState::DOWN:
		if (collider->Collides(*gameObjects->at("bottomCollider")->GetCollider()) != Tools::CollSide::TOP)
		rect.position.y += movementSpeed;
		break;

	case Player::PlayerState::IDLE:
		break;

	default:
		break;
	}

	for (auto& i : *gameObjects)
	{
		if (i.second->GetTag() == "PowerUp")
		{
			if (collider->Collides(*i.second->GetCollider())!=Tools::CollSide::NONE)
			{
				std::cout << "pu" << std::endl;
				pTime = 600;
				pActive = true;
				switch (dynamic_cast<PowerUps*>(i.second)->type)
				{
				case POWERUPTYPE::EXTRA:
					std::cout << "extra" << std::endl;
					rect.size.x = 75;
					//collider->UpdateSize(rect.size);
					break;
				case POWERUPTYPE::MINI:
					std::cout << "mini" << std::endl;
					rect.size.x = 45;
					//collider->UpdateSize(rect.size);
					break;
				case POWERUPTYPE::SPEED:
					std::cout << "speed" << std::endl;
					movementSpeed = baseSpeed * 1.2f;
					break;
				default:
					break;

				}
				i.second->deleteMe = true;
			}
		}
	}


	if (pActive)
	{
		pTime -= 1;
		if (pTime<=0)
		{
			ResetPowerUps();
		}
	}

}

void Player::Render()
{
	renderer->PushRotatedImage(texture.id, rect, 90);
	
	for (int i = 0; i < health; i++)
	{
		switch (playerNum) 
		{
		case 1:
			renderer->PushImage(healthTexture.id, { 100 + i * 50,560,40,10 });
			break;
		case 2:
			renderer->PushImage(healthTexture.id, { 490 + i * 50,560,40,10 });
			break;

		}
	}
}

int Player::GetScore(){	return score;}

int Player::GetPlayerNum(){	return playerNum;}

void Player::UpdateScore(int _score) { score += _score; if (score<0) {	score = 0; } }

void Player::UpdateHealth(){ health--; }

int Player::GetHealth()
{
	return health;
}

void Player::ResetPowerUps()
{
	std::cout << "reset" << std::endl;
	pActive = false;
	rect.size.x = 60;
	movementSpeed = baseSpeed;
}
