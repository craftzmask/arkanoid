#pragma once

#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "SpriteCodex.h"

class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& vel_in);
	void Update(float dt);
	bool DoWallsCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	void Draw(Graphics& gfx) const;
	RectF GetRect() const;
	Vec2 GetVelocity() const;
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
};