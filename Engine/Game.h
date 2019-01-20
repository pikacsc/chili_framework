/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "JasonChoi_structs.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();

	
	bool BoundaryCheck(const int &, const int &);
	bool BoundaryCheck(Cursor &);
	void MovingCursor(const MainWindow &, const int &);
	void drawLine(int, int, int, int, Graphics &, Color);
	void drawLine(const LINE &, Graphics &, Color);
	void drawCursor(CURSOR &, Graphics &, Color);
	void drawCursor(Graphics &, const int &, const int &, Color, int, int);
	void drawTargetingBox(Graphics &, const int &, const int &, Color, int, int);
	void drawTargetingBox(Graphics &, targetingBox &, Color);
	bool IsPointToRectCollide(const iRECT &, const Position &);
	bool IsCursorCollideTBox(const CURSOR &, const targetingBox &);
	int	 ClampScreenX(const int&);
	int	 ClampScreenY(const int&);


private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/

	POS		mCurrentPosition;
	CURSOR	mCursor;
	int		mCursorSpeed = 1;

};

