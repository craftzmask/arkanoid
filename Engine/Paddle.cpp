#include "Paddle.h"

Paddle::Paddle(const Vec2& pos_in)
	:
	pos(pos_in)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetRect(), Colors::White);
}

bool Paddle::DoBallCollision(Ball& ball) const
{
	if (ball.GetVelocity().y > 0.0f && GetRect().DoTestCollision(ball.GetRect()))
	{
		ball.ReboundY();
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
