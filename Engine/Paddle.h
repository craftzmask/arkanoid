#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(const Vec2& pos_in);
	void Draw(Graphics& gfx) const;
	bool DoBallCollision(Ball& ball);
	void DoWallsCollision(const RectF& walls);
	void Update(float dt, Keyboard& kbd);
	RectF GetRect() const;
	void ResetCooldown();
private:
	static constexpr float speed = 300.0f;
	static constexpr float width = 80.0f;
	static constexpr float height = 20.0f;
	static constexpr float wingWidth = 10.0f;
	Vec2 pos;
	bool isCooldown = false;
};