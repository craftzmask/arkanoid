#include "Brick.h"

Brick::Brick(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
{
}

void Brick::Draw(Graphics& gfx) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded(-padding), c);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!destroyed && rect.DoTestCollision(ball.GetRect()))
	{
		const Vec2& pos = ball.GetPosition();
		if (pos.x >= rect.left && pos.x <= rect.right)
		{
			ball.ReboundY();
		}
		else
		{
			ball.ReboundX();
		}
		destroyed = true;
		return true;
	}

	return false;
}
