#pragma once
#include "Types.h"
#include <math.h>

namespace Tools
{
	enum class CollSide { NONE, TOP, BOTTOM, LEFT, RIGHT, CORNERRIGHT, CORNERLEFT, COLL };

	float DotProduct(FVec2 vec1, FVec2 vec2);
	float Modulus(FVec2);
	FVec2 Normalize(FVec2 vec);
	FVec2 Transpose(FVec2 vec);
	
	CollSide CollisionRectRect(Rect, Rect );
	CollSide CollisionRectCircle(Rect, Circle);
	CollSide IsCollisionCircleRect(Circle, Rect);
	CollSide IsCollisionCircleCirlce(Circle, Circle);
	CollSide IsCollisionRectHorizontalLine(Rect rect, Vec2 line);

	bool IsCollisionRectRect(Rect, Rect);
	bool HoverColision(Rect, Vec2);
};

