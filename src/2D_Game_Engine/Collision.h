#pragma once

#include "Types.h"
#include "Tools.h"

class RectCollider;
class CircleCollider;

class Collision
{
public:
	
	Collision();
	~Collision();

	virtual Tools::CollSide Collides(Collision const& col) const = 0;
	virtual Tools::CollSide Collides(CircleCollider const& circle) const = 0;
	virtual Tools::CollSide Collides(RectCollider const& rect) const = 0;
	virtual void UpdatePosition(Vec2 _position) = 0;
	virtual void UpdateSize(Vec2 _size) = 0;

};

class RectCollider :
	public Collision
{
private:

	Tools::CollSide Collides(CircleCollider const& circle) const override;
	Tools::CollSide Collides(RectCollider const& rect) const override;

public:

	Rect rect;
	RectCollider(Rect);
	~RectCollider();
	Tools::CollSide Collides(Collision const& col) const override;
	void UpdatePosition(Vec2) override;
	void UpdateSize(Vec2) override;
};

class CircleCollider :
	public Collision
{
private:

	Tools::CollSide Collides(CircleCollider const& circle) const override;
	Tools::CollSide Collides(RectCollider const& rect) const override;

public:

	Circle circle;
	CircleCollider(Circle _circle);
	~CircleCollider();
	Tools::CollSide Collides(Collision const& col) const override;
	void UpdatePosition(Vec2) override;
	void UpdateSize(Vec2) override;
};
