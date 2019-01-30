#pragma once
#include "Board.h"


class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const LOCATION&);
		void InitBody();
		void Follow(const Segment&);
		void MoveBy(const LOCATION&);
		void Draw(Board&) const;
		const LOCATION& GetLocation() const;
	private:
		LOCATION m_location;
		Color	 m_color;
	};

public:
	Snake(const LOCATION&);
	void MoveBy(const LOCATION&);
	LOCATION GetNextHeadLocation(const LOCATION&) const;
	void Grow();
	void Draw(Board&) const;
	bool IsInTileExceptEnd(const LOCATION&) const;
	bool IsInTile(const LOCATION&) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::Green;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;

};