#include "Walls.h"

Walls::Walls(const Vec2& pos_in)
	:
	pos(pos_in)
{
}

void Walls::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), borderColor);
	gfx.DrawRect(GetRect().GetExpanded(-borderWidth), backgroundColor);
}

RectF Walls::GetRect() const
{
	return RectF::FromCenter(pos, width / 2.0f, height / 2.0f);
}

RectF Walls::GetRectNoBorder() const
{
	return GetRect().GetExpanded(-borderWidth);
}

Vec2 Walls::GetTopLeft() const
{
	const Vec2 half = Vec2(width / 2.0f - borderWidth, height / 2.0f - borderWidth);
	return Vec2(pos - half);
}
