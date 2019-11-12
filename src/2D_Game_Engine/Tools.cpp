#include "Tools.h"

FVec2 Tools::Normalize(FVec2 vec) {

	float mag = sqrt(pow(vec.x, 2) + pow(vec.y, 2));
	return(FVec2{ vec.x /= mag, vec.y /= mag });

}

FVec2 Tools::Transpose(FVec2 vec) {
	return(FVec2{ vec.y,-vec.x });
}

float Tools::DotProduct(FVec2 vec1, FVec2 vec2) {

	return(vec1.x*vec2.x + vec1.y*vec2.y);

}

float Tools::Modulus(FVec2 vec)
{
	return sqrt(pow(vec.x,2)+pow(vec.y,2));
}

bool Tools::HoverColision(Rect _rect, Vec2 vec) {

	if (_rect.position.x<vec.x && _rect.position.x + _rect.size.x>vec.x) {
		if (_rect.position.y<vec.y && _rect.position.y + _rect.size.x>vec.y)
			return true;
	}
	return false;

}

Tools::CollSide Tools::IsCollisionRectHorizontalLine(Rect rect, Vec2 line)
{
	if (abs(rect.position.y - line.y) < rect.size.y)
		return CollSide::COLL;
	else
		return CollSide::NONE;
}

Tools::CollSide Tools::CollisionRectRect(Rect rect1, Rect rect2) {

	float tCollision = abs(rect2.position.y + rect2.size.y - rect1.position.y);
	float bCollision = abs(rect2.position.y - (rect1.position.y + rect1.size.y));
	float rCollision = abs(rect1.position.x + rect1.size.x - rect2.position.x);
	float lCollision = abs(rect2.position.x + (rect2.size.x - rect1.position.x));

	if (rect1.position.x < rect2.position.x + rect2.size.x &&
		rect1.position.x + rect1.size.x > rect2.position.x &&
		rect1.position.y < rect2.position.y + rect2.size.y &&
		rect1.size.y + rect1.position.y > rect2.position.y) 
	{
			if (tCollision < bCollision && tCollision < rCollision && tCollision < lCollision)
				return(CollSide::TOP);
			if (bCollision < tCollision && bCollision < rCollision && bCollision < lCollision)
				return(CollSide::BOTTOM);
			if (rCollision < bCollision && rCollision < tCollision && rCollision < lCollision)
				return(CollSide::RIGHT);
			if (lCollision < bCollision && lCollision < rCollision && lCollision < tCollision)
				return(CollSide::LEFT);
		
	}
	
	return (CollSide::NONE);
}

Tools::CollSide Tools::CollisionRectCircle(Rect rect, Circle circle )
{
	rect.position.x += rect.size.x / 2;
	rect.position.y += rect.size.y / 2;
	circle.position.x += circle.radius;
	circle.position.y += circle.radius;

	if (abs(rect.position.x - circle.position.x) < rect.size.x / 2 + circle.radius &&
		abs(rect.position.y - circle.position.y) < rect.size.y / 2 + circle.radius) 
	{
		if (rect.position.x - rect.size.x / 2 < circle.position.x && circle.position.x < rect.position.x + rect.size.x / 2)
		{
			if (circle.position.y - rect.position.y < 0)
				return CollSide::TOP;
			else
				return CollSide::BOTTOM;
		}
		else if (rect.position.y - rect.size.y / 2 < circle.position.y && circle.position.y < rect.position.y + rect.size.y / 2)
		{
			if (circle.position.x - rect.position.x > 0)
				return CollSide::RIGHT;
			else
				return CollSide::LEFT;
		}
		/*else {

			if (circle.position.x < rect.position.x)
				return CollSide::CORNERLEFT;
			else
				return CollSide::CORNERRIGHT;
		}*/
	}
		return (CollSide::NONE);
}

Tools::CollSide Tools::IsCollisionCircleRect(Circle circle, Rect rect)
{
	rect.position.x += rect.size.x / 2;
	rect.position.y += rect.size.y / 2;
	circle.position.x += circle.radius;
	circle.position.y += circle.radius;

	if (abs(circle.position.x - rect.position.x) < rect.size.x / 2 + circle.radius / 2 &&
		abs(rect.position.y - circle.position.y) < rect.size.y / 2 + circle.radius / 2)
	{
		return CollSide::COLL;
	}

	return CollSide::NONE;
}

Tools::CollSide Tools::IsCollisionCircleCirlce(Circle circle1, Circle circle2)
{
	if (circle1.position.x - circle2.position.x < circle1.radius + circle2.radius && circle1.position.y - circle2.position.y < circle1.radius + circle2.radius)
		return Tools::CollSide::COLL;
	else
		return Tools::CollSide::NONE;
}

bool Tools::IsCollisionRectRect(Rect rect1, Rect rect2) {

	if (abs(rect1.position.x - rect2.position.x) < (rect1.size.x / 2 + rect2.size.x / 2) && abs(rect1.position.y - rect2.position.y) < (rect1.size.y / 2 + rect2.size.y / 2))
		return true;
	else
		return false;
}