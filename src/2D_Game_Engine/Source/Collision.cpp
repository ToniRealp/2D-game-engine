#include "../Headers/Collision.h"

#pragma region Collision

Collision::Collision(){}

Collision::~Collision(){}

#pragma endregion

#pragma region RectCollider

RectCollider::RectCollider(Rect _rect) :rect(_rect) {}

RectCollider::~RectCollider(){}

Tools::CollSide RectCollider::Collides(CircleCollider const & circle) const
{
	return Tools::CollisionRectCircle(rect, circle.circle);
}

Tools::CollSide RectCollider::Collides(RectCollider const & _rect) const
{
	return Tools::CollisionRectRect(rect, _rect.rect);
}

Tools::CollSide RectCollider::Collides(Collision const & col) const
{
	return col.Collides(*this);
}

void RectCollider::UpdatePosition(Vec2 _pos)
{
	rect.position = _pos;
}

void RectCollider::UpdateSize(Vec2 _size)
{
	rect.size = _size;
}

#pragma endregion

#pragma region CircleCollider

CircleCollider::CircleCollider(Circle _circle) :circle(_circle) {}

CircleCollider::~CircleCollider(){}

Tools::CollSide CircleCollider::Collides(CircleCollider const & _circle) const
{
	return Tools::IsCollisionCircleCirlce(circle, _circle.circle);
}

Tools::CollSide CircleCollider::Collides(RectCollider const & rect) const
{
	return Tools::IsCollisionCircleRect(circle, rect.rect);
}

Tools::CollSide CircleCollider::Collides(Collision const & col) const
{
	return col.Collides(*this);
}

void CircleCollider::UpdatePosition(Vec2 _pos)
{
	circle.position = _pos;
}
void CircleCollider::UpdateSize(Vec2 _size)
{

}

#pragma endregion