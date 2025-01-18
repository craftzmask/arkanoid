#include "RectF.h"

RectF::RectF(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2& topLeft, float width, float height)
	:
	RectF(topLeft, topLeft + Vec2(width, height))
{
}

bool RectF::DoTestCollision(const RectF& rect) const
{
	return
		left <= rect.right &&
		right >= rect.left &&
		top <= rect.bottom &&
		bottom >= rect.top;
}

RectF RectF::FromCenter(const Vec2& center, float halfWidth, float halfHeight)
{
	const Vec2 half = Vec2(halfWidth, halfHeight);
	return RectF(center - half, center + half);
}
