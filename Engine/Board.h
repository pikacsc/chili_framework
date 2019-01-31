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
	void DrawBorder();
private:
	static constexpr Color	m_borderColor = Colors::Blue;
	static constexpr int	m_dimension = 20;
	static constexpr int	m_cellPadding = 1;
	static constexpr int	m_width = 32;
	static constexpr int	m_height = 24;
	static constexpr int	m_borderWidth = 4;
	static constexpr int	m_borderPadding = 2;
	static constexpr int	m_x = 70;
	static constexpr int	m_y = 50;
	Graphics&				m_gfx;
};