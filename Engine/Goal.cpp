#include "Goal.h"

Goal::Goal(std::mt19937& _rng, const Board & _brd, const Snake & _snake)
{
	Respawn(_rng, _brd, _snake);
}

void Goal::Respawn(std::mt19937 _rng, const Board & _brd, const Snake & _snake)
{
	std::uniform_int_distribution<int> xDist(0, _brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, _brd.GetGridHeight() - 1);

	LOCATION newLocation;
	do
	{
		newLocation.x = xDist(_rng);
		newLocation.y = yDist(_rng);

	} while (_snake.IsInTile(newLocation));

	m_location = newLocation;
}

void Goal::Draw(Board & _brd) const
{
	_brd.DrawCell(m_location, m_color);
}

const Location & Goal::GetLocation() const
{
	return m_location;
}
