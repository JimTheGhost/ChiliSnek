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

#include "Board.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	rng(std::random_device()()),
	brd(gfx),
	snek({2,2}),
	goal(rng, brd, snek)
{
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
	if(!gameStarted && wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		gameStarted = true;
		snek.Respawn({2,2});
		deltaLoc = {0,1};
		gameOver = false;
	}
	if(gameOver)
	{
		return;
	}
	
	Location newDelta = deltaLoc;
	if(wnd.kbd.KeyIsPressed(VK_UP))
	{
		newDelta = {0,-1};
	}
	if(wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		newDelta = {0,1};
	}
	if(wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		newDelta = {-1,0};
	}
	if(wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		newDelta = {1,0};
	}
	if(newDelta != snek.GetTravelDir().Negate() && snek.GetLength() > 1)
	{
		deltaLoc = newDelta;
	}else if (snek.GetLength() == 1)
	{
		deltaLoc = newDelta;
	}


	
	snekMoveCounter++;
	if(snekMoveCounter>=snekMovePeriod)
	{
		const Location next = snek.GetNextHeadLocation(deltaLoc);
		if(!brd.isOnBoard(next)||snek.IsInTileExceptEnd(next))
		{
			gameOver = true;
			gameStarted = false;
			return;
		}
		if(next == goal.GetLocation())
		{
			snek.Grow();
			goal.Respawn(rng,brd,snek);
			if((snek.GetLength()%3) == 0)
			{
				snekMovePeriod -= 3;
				if (snekMovePeriod < 8)
				{
					snekMovePeriod = 8;
				}
			}
		}
		snek.MoveBy(deltaLoc);
		snekMoveCounter = 0;
		

	}

}

void Game::ComposeFrame()
{
	/*
	std::uniform_int_distribution<int> cDist(0,255);
	for(int x = 0; x < brd.GetGridWidth();x++)
	{
		for(int y = 0; y < brd.GetGridHeight();y++)
		{
			Location newLoc = {x,y};
			Color c;
			c.SetR(cDist(rng));
			c.SetG(cDist(rng));
			c.SetB(cDist(rng));
			brd.DrawCell(newLoc,c);
		}
	}
	*/

	if(!gameStarted && !gameOver)
	{
		SpriteCodex::DrawTitle(250,150,gfx);
		return;
	}
	if (gameOver)
	{
		SpriteCodex::DrawGameOver(400,300,gfx);	
	}
	snek.Draw(brd);
	goal.Draw(brd);
	brd.DrawBorder();



}
