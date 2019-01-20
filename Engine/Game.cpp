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
#include "JasonChoi_structs.h"
#include <math.h>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
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
	MovingCursor(wnd, mCursorSpeed);
}





inline bool Game::BoundaryCheck(const int& _x, const int& _y)
{
	return (_x > 0) && (800 > _x) && (_y > 0) && (600 > _y);
}

inline bool Game::BoundaryCheck(Cursor& _cursor)
{
	return (_cursor.left.x1 > 0) && (800 > _cursor.right.x2) && (_cursor.top.y2 > 0) && (600 > _cursor.bottom.y2);
}



void Game::MovingCursor(const MainWindow& wnd, const int& amount)
{
	
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		mCurrentPosition.y -= amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		mCurrentPosition.y += amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		mCurrentPosition.x -= amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		mCurrentPosition.x += amount;
	}

	mCurrentPosition.x = ClampScreenX(mCurrentPosition.x);
	mCurrentPosition.y = ClampScreenY(mCurrentPosition.y);


	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		drawTargetingBox(gfx, mCurrentPosition.x, mCurrentPosition.y, Colors::Red, 5, 5);
	if (wnd.kbd.KeyIsPressed(VK_ADD) && mCursorSpeed < 5)
		mCursorSpeed += 1;
	if (wnd.kbd.KeyIsPressed(VK_SUBTRACT) && mCursorSpeed > 0)
		mCursorSpeed -= 1;
	
}

void Game::drawLine(int _iX1, int _iY1, int _iX2, int _iY2, Graphics& _gfx, Color _color = Colors::LightGray)
{
	if (BoundaryCheck(_iX1, _iY1) && BoundaryCheck(_iX2, _iY2))
	{
		if (_iX1 > _iX2)
		{
			int temp = _iX1;
			_iX1 = _iX2;
			_iX2 = temp;
		}
		if (_iY1 > _iY2)
		{
			int temp = _iY1;
			_iY1 = _iY2;
			_iY2 = temp;
		}

		while (_iX1 <= _iX2 && _iY1 <= _iY2)
		{
			_gfx.PutPixel(_iX1, _iY1, _color);
			if (_iX1 == _iX2 && _iY1 == _iY2)
				break;
			if (_iX1 < _iX2)
				_iX1++;
			if (_iY1 < _iY2)
				_iY1++;
		}
	}
}



void Game::drawLine(const LINE& _line, Graphics& _gfx, Color _color = Colors::LightGray)
{
	int iX1 = _line.x1;
	int iY1 = _line.y1;
	int iX2 = _line.x2;
	int iY2 = _line.y2;
	if (BoundaryCheck(iX1, iY1) && BoundaryCheck(iX2, iY2))
	{
		if (iX1 > iX2)
		{
			int temp = iX1;
			iX1 = iX2;
			iX2 = temp;
		}
		if (iY1 > iY2)
		{
			int temp = iY1;
			iY1 = iY2;
			iY2 = temp;
		}

		while (iX1 <= iX2 && iY1 <= iY2)
		{
			_gfx.PutPixel(iX1, iY1, _color);
			if (iX1 == iX2 && iY1 == iY2)
				break;
			if (iX1 < iX2)
				iX1++;
			if (iY1 < iY2)
				iY1++;
		}
	}


}

void Game::drawCursor(CURSOR& _cursor, Graphics& _gfx, Color _color = Colors::LightGray)
{
	drawLine(_cursor.left.x1, _cursor.left.y1, _cursor.left.x2, _cursor.left.y2, _gfx, _color);
	drawLine(_cursor.top.x1, _cursor.top.y1, _cursor.top.x2, _cursor.top.y2, _gfx, _color);
	drawLine(_cursor.right.x1, _cursor.right.y1, _cursor.right.x2, _cursor.right.y2, _gfx, _color);
	drawLine(_cursor.bottom.x1, _cursor.bottom.y1, _cursor.bottom.x2, _cursor.bottom.y2, _gfx, _color);
}


void Game::drawCursor(Graphics& _gfx, const int& _x, const int& _y, Color _color = Colors::LightGray, int _lineGap = 10, int _lineLength = 10)
{
	CURSOR cursor = { _x,_y,_lineGap,_lineLength };
	drawLine(cursor.left, _gfx, _color);
	drawLine(cursor.top, _gfx, _color);
	drawLine(cursor.right, _gfx, _color);
	drawLine(cursor.bottom, _gfx, _color);
}



void Game::drawTargetingBox(Graphics& _gfx, const int& _x, const int& _y, Color _color = Colors::LightGray, int _lineGap = 10, int _lineLength = 10)
{
	targetingBox tBox = { _x,_y,_lineGap,_lineLength };

	drawLine(tBox.LeftTop_x, _gfx, _color);
	drawLine(tBox.LeftTop_y, _gfx, _color);
	drawLine(tBox.RightTop_x, _gfx, _color);
	drawLine(tBox.RightTop_y, _gfx, _color);
	drawLine(tBox.LeftBottom_x, _gfx, _color);
	drawLine(tBox.LeftBottom_y, _gfx, _color);
	drawLine(tBox.RightBottom_x, _gfx, _color);
	drawLine(tBox.RightBottom_y, _gfx, _color);
}


void Game::drawTargetingBox(Graphics& _gfx, targetingBox& _tBox, Color _color = Colors::LightGray)
{
	drawLine(_tBox.LeftTop_x, _gfx, _color);
	drawLine(_tBox.LeftTop_y, _gfx, _color);
	drawLine(_tBox.RightTop_x, _gfx, _color);
	drawLine(_tBox.RightTop_y, _gfx, _color);
	drawLine(_tBox.LeftBottom_x, _gfx, _color);
	drawLine(_tBox.LeftBottom_y, _gfx, _color);
	drawLine(_tBox.RightBottom_x, _gfx, _color);
	drawLine(_tBox.RightBottom_y, _gfx, _color);
}

inline bool Game::IsPointToRectCollide(const iRECT& _rect, const Position& _pos) {
	return (_rect.left.x1 <= _pos.x) && (_pos.x <= _rect.right.x2) && (_rect.top.y1 <= _pos.y) && (_pos.y <= _rect.bottom.y2);
}


bool Game::IsCursorCollideTBox(const CURSOR& _cursor,const targetingBox& _tBox)
{
	//Define area to detect collide
	POS LeftTopCorner		= { _tBox.LeftTop_x.x1,_tBox.LeftTop_y.y1 };
	POS RightTopCorner		= { _tBox.RightTop_x.x2,_tBox.LeftTop_y.y1 };
	POS LeftBottomCorner	= { _tBox.LeftBottom_x.x1,_tBox.LeftBottom_y.y2 };
	POS RightBottomCorner	= { _tBox.RightBottom_x.x2,_tBox.RightBottom_y.y2 };

	LINE areaLeft = { LeftTopCorner.x,LeftTopCorner.y, LeftBottomCorner.x,LeftBottomCorner.y };
	LINE areaTop  = { LeftTopCorner.x,LeftTopCorner.y, RightTopCorner.x,RightTopCorner.y };
	LINE areaRight = { RightTopCorner.x,RightTopCorner.y, RightBottomCorner.x,RightBottomCorner.y };
	LINE areaBottom = { LeftBottomCorner.x,LeftBottomCorner.y, RightBottomCorner.x,RightBottomCorner.y };

	iRECT rect = { areaLeft,areaTop,areaRight,areaBottom };

	//cursor POINTS
	POS _cursorLeft		= { _cursor.left.x1,_cursor.left.y1};
	POS _cursorTop		= { _cursor.top.x1,_cursor.top.y1 };
	POS _cursorRight	= { _cursor.right.x2,_cursor.right.y1 };
	POS _cursorBottom	= { _cursor.bottom.x1,_cursor.bottom.y2 };

	return IsPointToRectCollide(rect, _cursorLeft) || IsPointToRectCollide(rect, _cursorTop) || IsPointToRectCollide(rect, _cursorRight) || IsPointToRectCollide(rect, _cursorBottom);
}

int Game::ClampScreenX(const int & _x)
{
	const int left = _x - 5;
	const int right = _x + 5;
	if (left < 0)
		return 5;
	else if (right >= gfx.ScreenWidth)
		return gfx.ScreenWidth - 6;
	else
		return _x;
}

int Game::ClampScreenY(const int & _y)
{
	const int Top = _y - 5;
	const int Bottom = _y + 5;
	if (Top < 0)
		return 5;
	else if (Bottom >= gfx.ScreenHeight)
		return gfx.ScreenHeight - 6;
	else
		return _y;
}


void Game::ComposeFrame()
{

	targetingBox RedBox = { 300,300, 10,10 };
	drawTargetingBox(gfx,RedBox, Colors::Red);
	
	
	targetingBox GreenBox = { 450,450, 10,10 };
	drawTargetingBox(gfx, GreenBox, Colors::Green);


	targetingBox BlueBox = { 150,200, 10,10 };
	drawTargetingBox(gfx, BlueBox, Colors::Blue);


	mCursor = { mCurrentPosition.x, mCurrentPosition.y, 5,5 };

	if (IsCursorCollideTBox(mCursor, GreenBox))
		drawCursor(gfx, mCurrentPosition.x, mCurrentPosition.y, Colors::Green);
	if (IsCursorCollideTBox(mCursor, RedBox))
		drawCursor(gfx, mCurrentPosition.x, mCurrentPosition.y, Colors::Red);
	/*if (IsCursorCollideTBox(cursor, BlueBox))
		drawCursor(gfx, mCurrentPosition.x, mCurrentPosition.y, Colors::Blue);*/
	else
		drawCursor(gfx, mCurrentPosition.x, mCurrentPosition.y);
	
	gfx.PutPixel(mCurrentPosition.x, mCurrentPosition.y, Colors::Red);
}
