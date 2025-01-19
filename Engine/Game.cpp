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
	ball(Vec2(400.0f, 500.0f), Vec2(300.0f, -300.0f)),
	walls(0.0f, 800.0f, 0.0f, 600.0f)
{
	Vec2 topLeft = Vec2(40.0f, 40.0f);
	Color colors[4] = {Colors::Blue, Colors::Green, Colors::Red, Colors::Yellow};
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		Color c = colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			bricks[i] = Brick(RectF(topLeft + Vec2(x * brickWidth, y * brickHeight),brickWidth, brickHeight), c);
			i++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	ball.Update(dt);
	pad.Update(dt, wnd.kbd);
	pad.DoWallsCollision(walls);
	
	if (ball.DoWallsCollision(walls))
	{
		brickSound.Play();
	}

	if (pad.DoBallCollision(ball))
	{
		padSound.Play();
	}

	for (Brick& b : bricks)
	{
		if (b.DoBallCollision(ball))
		{
			brickSound.Play();
			break;
		}
	}
}

void Game::ComposeFrame()
{
	pad.Draw(gfx);

	for (const Brick& b : bricks)
	{
		b.Draw(gfx);
	}

	ball.Draw(gfx);
}
