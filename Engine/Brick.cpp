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
		gfx.DrawRect(rect, c);
	}
}

bool Brick::DoBallCollision(Ball& ball)
{
	if (!destroyed && rect.DoTestCollision(ball.GetRect()))
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}

	return false;
}
