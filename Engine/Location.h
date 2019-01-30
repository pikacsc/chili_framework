#pragma once

class Location
{
public:
	int x;
	int y;


	void Add(const Location& _val)
	{
		x += _val.x;
		y += _val.y;
	}

	bool operator == (const Location& _rhs) const
	{
		return x == _rhs.x && y == _rhs.y;
	}

} typedef LOCATION;