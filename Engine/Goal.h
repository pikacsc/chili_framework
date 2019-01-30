#pragma once
#include "Snake.h"
#include "Board.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937&, const Board&, const Snake&);

	void Respawn(std::mt19937, const Board&, const Snake&);

	void Draw(Board&) const;

	const Location& GetLocation() const;

private:
	static constexpr Color	m_color = Colors::Red;
	LOCATION				m_location;
};