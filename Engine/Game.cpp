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
#include "DrawingObjects.h"
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	mDude = { 400,300 };


	//PooInitialize
	for (int i = 0; i < mPooCount; i++)
	{
		POO newPoo = { GetRandomNumber(mLevelScreenGap,mScreenWidth),GetRandomNumber(mLevelScreenGap,mScreenHeight),true};
		mPooVector.push_back(newPoo);
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
	if (IsGameOver())
	{
		DrawGameOver(400,300,gfx);
	}
	else
	{
		DrawWall(mScreenWidth, mScreenHeight,gfx);
		DrawDude(mDude, gfx);
		for (int i = 0; i < mPooCount; i++)
		{
			if (mPooVector[i].IsActive == true)
				DrawPoo(mPooVector[i], gfx);
		}
	}
}

void Game::MovingDude()
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
		mDude.y -= mDude.speed;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		mDude.y += mDude.speed;
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		mDude.x -= mDude.speed;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		mDude.x += mDude.speed;
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		ResetGame();
}

void Game::EattingPoo()
{
	const int gap = 15;
	for (int i = 0; i < mPooCount; i++)
	{
		if (mPooVector[i].x + gap > mDude.x && mPooVector[i].x - gap < mDude.x && mPooVector[i].y - gap < mDude.y && mPooVector[i].y + gap > mDude.y)
		{
			mPooVector[i].IsActive = false;
		}
	}
}

void Game::RenewPooVector()
{
	mLevelScreenGap += 10;
	mScreenWidth -= mLevelScreenGap;
	mScreenHeight -= mLevelScreenGap;
	for (int i = 0; i < mPooCount; i++)
	{
		POO newPoo = { GetRandomNumber(mLevelScreenGap,mScreenWidth-50),GetRandomNumber(mLevelScreenGap,mScreenHeight-50),true };
		mPooVector.push_back(newPoo);
	}
	mPooCount += mPooCount;
	for (int i = 0; i < mPooCount; i++)
	{
		mPooVector[i].IsActive = true;
		mPooVector[i].x = GetRandomNumber(mLevelScreenGap + 50, mScreenWidth - 50);
		mPooVector[i].y = GetRandomNumber(mLevelScreenGap + 50, mScreenHeight - 50);
	}
	mDude.x = 400;
	mDude.y = 300;
}

bool Game::IsGameClear()
{
	int deadPooCount = 0;
	for (int i = 0; i < mPooCount; i++)
	{
		if (mPooVector[i].IsActive == false)
		{
			deadPooCount++;
		}
	}
	return (deadPooCount == mPooCount);
}

bool Game::IsGameOver()
{
	return  mDude.x < mLevelScreenGap || mDude.x > mScreenWidth || mDude.y < mLevelScreenGap || mDude.y > mScreenHeight;
}



int Game::GetRandomNumber(const int& _a, const int& _b)
{
	//<random>, recommended way
	using namespace std;
	random_device rd;
	mt19937 mersenne(rd()); //mt19937 : 32bit random nubmer
	uniform_int_distribution<> dice(_a, _b); //equal chance value, random number between 1 and 6 
	return dice(mersenne);
}

void Game::ResetGame()
{
	mDude.x = 400;
	mDude.y = 300;
	mDude.speed = 1;
	mScreenWidth = 750;
	mScreenHeight = 550;
	mLevelScreenGap = 50;
	mPooCount = 3;
	mPooVector.resize(mPooCount);
	for (int i = 0; i < mPooCount; i++)
	{
		mPooVector[i].IsActive = true;
		mPooVector[i].x = GetRandomNumber(mLevelScreenGap + 50, mScreenWidth - 50);
		mPooVector[i].y = GetRandomNumber(mLevelScreenGap + 50, mScreenHeight - 50);
	}
}



void Game::ComposeFrame()
{
	MovingDude();
	EattingPoo();
	if (IsGameClear())
	{
		RenewPooVector();
		mDude.speed += 4;
	}
}
