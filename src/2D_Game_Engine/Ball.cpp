#include "Ball.h"

Ball::Ball(Rect _rect, Texture _texture, const GameObjects * _gameObjects):GameObject(_rect,_texture,_gameObjects),
direction(1,1),speed(3),lastTouched("player1"),spawn(false)
{
	collider = new CircleCollider(Circle(rect.position.x ,rect.position.y,rect.size.x / 2));
	tag = "ball";
}

Ball::~Ball(){}

void Ball::Update()
{
	rect.position = rect.position + direction * speed;
	collider->UpdatePosition(rect.position);
	
	if (rect.position.y < 20)
		direction.y = 1;
	if (rect.position.y > SCREEN_HEIGHT - 130)
		direction.y = -1;

	if (!collided) 
	{
		if (collider->Collides(*gameObjects->at("rightCollider")->GetCollider()) == Tools::CollSide::LEFT)
		{
			dynamic_cast<Player*>(gameObjects->at("player1"))->UpdateScore(100);
			dynamic_cast<Player*>(gameObjects->at("player2"))->UpdateScore(-50);
			dynamic_cast<Player*>(gameObjects->at("player2"))->UpdateHealth();
			direction={-1,1};
			rect.position = { gameObjects->at("player2")->GetRect().position.x, gameObjects->at("player2")->GetRect().position.y};
			spawn = true;
			collided = false;
		}
		else if (collider->Collides(*gameObjects->at("leftCollider")->GetCollider()) == Tools::CollSide::RIGHT) 
		{
			dynamic_cast<Player*>(gameObjects->at("player2"))->UpdateScore(100);
			dynamic_cast<Player*>(gameObjects->at("player1"))->UpdateScore(-50);
			dynamic_cast<Player*>(gameObjects->at("player1"))->UpdateHealth();
			direction = { 1, 1};
			rect.position = { gameObjects->at("player1")->GetRect().position.x +40, gameObjects->at("player1")->GetRect().position.y };
			spawn = true;
			collided = false;
		}
		else if (collider->Collides(*gameObjects->at("player1")->GetCollider()) == Tools::CollSide::RIGHT) 
		{
			lastTouched = "player1";
			direction = { 1, direction.y };
			collided = true;
		}
		else if (collider->Collides(*gameObjects->at("player2")->GetCollider()) == Tools::CollSide::LEFT) 
		{
			lastTouched = "player2";
			direction = { -1, direction.y };
			collided = true;
		}
		else 
		{
			for (auto x : *gameObjects)
			{
				if (x.second->GetTag() != "nonCollidable" &&x.second->GetTag() != "ball"&&x.second->GetTag() != "player"&&x.second->GetTag()!="PowerUp")
				{
					if (collider->Collides(*x.second->GetCollider()) != Tools::CollSide::NONE) 
					{
						lastCollided = x.second;
						if (x.second->GetTag() == "brick") { dynamic_cast<Brick*>(x.second)->UpdateBrick(lastTouched); }
						rect.position = { rect.position.x - 2 * direction.x,rect.position.y - 2 * direction.y };

						switch (collider->Collides(*x.second->GetCollider()))
						{						
						case Tools::CollSide::TOP:
							direction = { direction.x, -1 };
							collided = true;
							break;
						case Tools::CollSide::BOTTOM:
							direction = { direction.x, 1 };
							collided = true;
							break;
						case Tools::CollSide::RIGHT:
							direction = { 1, direction.y };
							collided = true;
							break;
						case Tools::CollSide::LEFT:
							direction = { -1, direction.y };
							collided = true;
							break;
							/*case Tools::CollSide::CORNERRIGHT:
								direction = { 1, direction.y};
								collided = true;
								break;
							case Tools::CollSide::CORNERLEFT:
								direction = { -1, direction.y };
								collided = true;
								break;*/
						default:
							break;
						}
					}
				}
			}
		}
	}
	if (collided == true)
		IsColliding();
}

//void Ball::IsColliding()
//{
//	bool temp = false;
//	for (auto x : *gameObjects) 
//	{
//		if (x.second->GetTag() != "nonCollidable"&& x.second->GetTag()!="ball") 
//		{
//			if (collider->Collides(*x.second->GetCollider()) != Tools::CollSide::NONE)
//				temp = true;
//		}
//	}
//	collided = temp;
//}

void Ball::IsColliding()
{
	if(collider->Collides(*lastCollided->GetCollider())== Tools::CollSide::NONE)
	collided = false;
}

bool Ball::GetSpawn(){ return spawn; }

void Ball::SetSpawn(){ spawn = false;}

int Ball::GetLastTouched() {
	if (lastTouched=="player1")
		return -1;
	else
		return 1;
}
