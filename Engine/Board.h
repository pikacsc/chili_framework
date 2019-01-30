#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& _gfx);
	void DrawCell(const LOCATION& _location, Color _color);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const LOCATION&) const;
private:
	static constexpr int	m_dimension = 20;
	static constexpr int	m_width = 25;
	static constexpr int	m_height = 25;
	Graphics&				m_gfx;
};