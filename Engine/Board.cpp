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

	m_gfx.DrawRectDim(_location.x * m_dimension, _location.y * m_dimension,m_dimension,m_dimension, _color);
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
