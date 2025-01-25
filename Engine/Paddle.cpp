#include "Paddle.h"
#include <cmath>

Paddle::Paddle(const Vec2& pos_in)
	:
	pos(pos_in)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, Colors::Red);
	rect.left += wingWidth;
	rect.right -= wingWidth;
	gfx.DrawRect(rect, Colors::White);
}

bool Paddle::DoBallCollision(Ball& ball) const
{
	const RectF& rect = ball.GetRect();

	if (GetRect().DoTestCollision(rect))
	{
		if (std::signbit(ball.GetVelocity().x) == std::signbit((ball.GetPosition() - pos).x))
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
		return true;
	}

	return false;
}

void Paddle::DoWallsCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left <= walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	
	if (rect.right >= walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Update(float dt, Keyboard& kbd)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}

	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, width / 2.0f, height / 2.0f);
}
