#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "RectF.h"
#include "Vec2.h"

class Walls
{
public:
	Walls() = default;
	Walls(const Vec2& pos_in);
	void Draw(Graphics& gfx) const;
	RectF GetRect() const;
	RectF GetRectNoBorder() const;
	Vec2 GetTopLeft() const;

private:
	static constexpr float width = 500.0f;
	static constexpr float height = 550.0f;
	static constexpr float borderWidth = 10.0f;
	static constexpr Color backgroundColor = Colors::Black;
	static constexpr Color borderColor = Colors::Blue;
	Vec2 pos;
};