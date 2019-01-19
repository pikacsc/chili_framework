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
}





bool BoundaryCheck(const int& _x, const int& _y)
{
	if (_x < 0)
		return false;
	if (800 < _x)
		return false;
	if (_y < 0)
		return false;
	if (600 < _y)
		return false;
	return true;
}


POS		currentPosition;
CURSOR	Cursor;
int		Speed = 1;


void MovingCursor(const MainWindow& wnd, const int& amount)
{
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		currentPosition.y -= amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		currentPosition.y += amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		currentPosition.x -= amount;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		currentPosition.x += amount;
	}
}

void drawLine(int _iX1, int _iY1, int _iX2, int _iY2, Graphics& _gfx, Color _color = Colors::LightGray)
{
	BoundaryCheck(_iX1, _iY1);
	BoundaryCheck(_iX2, _iY2);

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



void drawLine(const LINE& _line, Graphics& _gfx, Color _color = Colors::LightGray)
{
	int iX1 = _line.x1;
	int iY1 = _line.y1;
	int iX2 = _line.x2;
	int iY2 = _line.y2;
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

void drawCursor(CURSOR& _cursor, Graphics& _gfx, Color _color = Colors::LightGray)
{
	drawLine(_cursor.left.x1, _cursor.left.y1, _cursor.left.x2, _cursor.left.y2, _gfx, _color);
	drawLine(_cursor.top.x1, _cursor.top.y1, _cursor.top.x2, _cursor.top.y2, _gfx, _color);
	drawLine(_cursor.right.x1, _cursor.right.y1, _cursor.right.x2, _cursor.right.y2, _gfx, _color);
	drawLine(_cursor.bottom.x1, _cursor.bottom.y1, _cursor.bottom.x2, _cursor.bottom.y2, _gfx, _color);
}


void drawCursor(Graphics& _gfx, const int& _x, const int& _y, Color _color = Colors::LightGray, int _lineGap = 10, int _lineLength = 10)
{
	CURSOR cursor = { _x,_y,_lineGap,_lineLength };
	drawLine(cursor.left, _gfx, _color);
	drawLine(cursor.top, _gfx, _color);
	drawLine(cursor.right, _gfx, _color);
	drawLine(cursor.bottom, _gfx, _color);
}



void drawTargetingBox(Graphics& _gfx, const int& _x, const int& _y, Color _color = Colors::LightGray, int _lineGap = 10, int _lineLength = 10)
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


void drawTargetingBox(Graphics& _gfx, targetingBox& _tBox, Color _color = Colors::LightGray)
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

inline bool IsPointToRectCollide(const iRECT& _rect, const Position& _pos) {
	return (_rect.left.x1 <= _pos.x) && (_pos.x <= _rect.right.x2) && (_rect.top.y1 <= _pos.y) && (_pos.y <= _rect.bottom.y2);
}


bool IsCursorCollideTBox(const CURSOR& _cursor,const targetingBox& _tBox)
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


	if (IsPointToRectCollide(rect, _cursorLeft))
		return true;
	if (IsPointToRectCollide(rect, _cursorTop))
		return true;
	if (IsPointToRectCollide(rect, _cursorRight))
		return true;
	if (IsPointToRectCollide(rect, _cursorBottom))
		return true;
	return false;
}


void Game::ComposeFrame()
{


	targetingBox YellowBox = { 300,300, 10,10 };
	CURSOR cursor = { currentPosition.x, currentPosition.y, 5,5 };


	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		drawTargetingBox(gfx, currentPosition.x, currentPosition.y, Colors::Red, 5, 5);
	if (wnd.kbd.KeyIsPressed(VK_ADD) && Speed < 5)
		Speed += 1;
	if (wnd.kbd.KeyIsPressed(VK_SUBTRACT) && Speed > 0)	
		Speed -= 1;
	if (IsCursorCollideTBox(cursor,YellowBox))
		drawCursor(gfx, currentPosition.x, currentPosition.y,Colors::Red);
	else
		drawCursor(gfx, currentPosition.x, currentPosition.y);
	drawTargetingBox(gfx,YellowBox, Colors::Yellow);
	
	MovingCursor(wnd, Speed);
	gfx.PutPixel(currentPosition.x, currentPosition.y, Colors::Red);
}
