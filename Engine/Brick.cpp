#include "Brick.h"
#include "assert.h"
#include <cmath>

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

bool Brick::CheckBallCollision(const Ball& ball) const
{
	return !destroyed && rect.DoTestCollision(ball.GetRect());
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));

	const Vec2& pos = ball.GetPosition();
	if (std::signbit(ball.GetVelocity().x) == std::signbit((ball.GetPosition() - rect.GetCenter()).x))
	{
		ball.ReboundY();
	}
	else if (pos.x >= rect.left && pos.x <= rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}

	destroyed = true;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
