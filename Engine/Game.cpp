/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brickSound(L"Sounds\\arkbrick.wav"),
	padSound(L"Sounds\\arkpad.wav"),
	pad(Vec2(400.0f, 500.0f)),
	ball(Vec2(530.0f, 500.0f), Vec2(-300.0f, -300.0f)),
	walls(Vec2(400.0f, 300.0f))
{
	Vec2 topLeft = Vec2(20.0f, 20.0f) + walls.GetTopLeft();
	Color colors[4] = {Colors::Blue, Colors::Green, Colors::Red, Colors::Yellow};
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight), brickWidth, brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		// takes 16ms to render 1 frame, so split 16ms 
		// into smaller steps to similate better each frame
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (!isGameover)
	{
		ball.Update(dt);
		pad.Update(dt, wnd.kbd);
		pad.DoWallsCollision(walls.GetRectNoBorder());

		if (ball.DoWallsCollision(walls.GetRectNoBorder()))
		{
			pad.ResetCooldown();
			brickSound.Play();
		}

		if (pad.DoBallCollision(ball))
		{
			padSound.Play();
		}

		bool collisionHappened = false;
		float curColDistSq;
		int indexColDist = 0;

		for (int i = 0; i < nBricks; i++)
		{
			if (bricks[i].CheckBallCollision(ball))
			{
				const float newColDistSq = (ball.GetPosition() - bricks[i].GetCenter()).GetLengthSq();

				if (collisionHappened)
				{
					if (newColDistSq < curColDistSq)
					{
						curColDistSq = newColDistSq;
						indexColDist = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					indexColDist = i;
					collisionHappened = true;
				}
			}
		}

		if (collisionHappened)
		{
			pad.ResetCooldown();
			bricks[indexColDist].ExecuteBallCollision(ball);
			brickSound.Play();
		}

		if (ball.GetRect().bottom >= Graphics::ScreenHeight)
		{
			isGameover = true;
		}
	}
}

void Game::ComposeFrame()
{
	walls.Draw(gfx);
	pad.Draw(gfx);

	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}

	ball.Draw(gfx);

	if (isGameover)
	{
		SpriteCodex::DrawGameOver(358, 268, gfx);
	}
}
