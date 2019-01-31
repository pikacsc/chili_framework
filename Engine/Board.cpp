#include "Board.h"
#include <assert.h>
Board::Board(Graphics & _gfx)
	:
	m_gfx(_gfx)
{
}

void Board::DrawCell(const LOCATION & _location, Color _color)
{
	
	assert(_location.x >= 0);
	assert(_location.x < m_width);
	assert(_location.y >= 0);
	assert(_location.y < m_height);

	const int off_x = m_x + m_borderWidth + m_borderPadding;
	const int off_y = m_y + m_borderWidth + m_borderPadding;

	m_gfx.DrawRectDim(_location.x * m_dimension + off_x + m_cellPadding, _location.y * m_dimension + off_y + m_cellPadding, m_dimension - m_cellPadding * 2, m_dimension - m_cellPadding * 2, _color);
}

int Board::GetGridWidth() const
{
	return m_width;
}

int Board::GetGridHeight() const
{
	return m_height;
}

bool Board::IsInsideBoard(const LOCATION & _location) const
{
	return _location.x >= 0 && _location.x < m_width && _location.y >= 0 && _location.y < m_height;
}

void Board::DrawBorder()
{
	const int left = m_x;
	const int top = m_y;
	const int right = left + (m_borderWidth + m_borderPadding) * 2 + m_width * m_dimension;
	const int bottom = top + (m_borderWidth + m_borderPadding) * 2 + m_height * m_dimension;

	//top
	m_gfx.DrawRect(left, top, right, top + m_borderWidth, m_borderColor);

	//left
	m_gfx.DrawRect(left, top + m_borderWidth,left + m_borderWidth,bottom-m_borderWidth, m_borderColor);

	//right
	m_gfx.DrawRect(right -m_borderWidth, top + m_borderWidth, right, bottom - m_borderWidth, m_borderColor);

	//bottom
	m_gfx.DrawRect(left, bottom- m_borderWidth, right, bottom, m_borderColor);

}
