#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF(float left_in, float right_in, float top_in, float bottom_in);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, float width, float height);
	bool DoTestCollision(const RectF& rect) const;
public:
	float top;
	float bottom;
	float left;
	float right;
};