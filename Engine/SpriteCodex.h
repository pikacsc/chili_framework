#pragma once

#include "Graphics.h"
#include "Board.h"

class SpriteCodex
{
public:
	static void DrawGameOver( int x,int y,Graphics& gfx );
	static void DrawTitle( int x,int y,Graphics& gfx );
	static void DrawBorder(Board& _brd,Graphics& _gfx);
};