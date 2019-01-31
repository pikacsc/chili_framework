#include "Snake.h"
#include <assert.h>

Snake::Snake(const LOCATION & _location)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = 
	{
		{10,100,32},
		{10,130,48},
		{10,160,48},
		{10,130,48}
	};

	for (int i = 0; i < nSegmentsMax; ++i)
	{
		segments[i].InitBody(bodyColors[i%nBodyColors]);
	}

	segments[0].InitHead(_location);
}

void Snake::MoveBy(const LOCATION & _deltaLocation)
{
	for (int i = nSegments - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(_deltaLocation);
}

LOCATION Snake::GetNextHeadLocation(const LOCATION & _deltaLocation) const
{
	LOCATION l(segments[0].GetLocation());
	l.Add(_deltaLocation);
	return l;
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		++nSegments;
	}
}

void Snake::Draw(Board & _brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(_brd);
	}
}

bool Snake::IsInTileExceptEnd(const LOCATION & _target) const
{
	for (int i = 0; i < nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == _target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const LOCATION & _target) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == _target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const LOCATION & _location)
{
	m_location = _location;
	m_color = Snake::headColor;
}

void Snake::Segment::InitBody( Color _color)
{
	m_color = _color;
}

void Snake::Segment::Follow(const Segment & _next)
{
	m_location = _next.m_location;
}

void Snake::Segment::MoveBy(const LOCATION & _deltaLocation)
{
	assert(abs(_deltaLocation.x) + abs(_deltaLocation.y) == 1);
	m_location.Add(_deltaLocation);
}

void Snake::Segment::Draw(Board & _brd) const
{
	_brd.DrawCell(m_location, m_color);
}

const LOCATION& Snake::Segment::GetLocation() const
{
	return m_location;
}
