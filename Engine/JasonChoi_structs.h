#pragma once

enum MOVE_DIR
{
	eLEFT_TOP = 1,
	eLEFT_BOTTOM = 2,
	eRIGHT_TOP = 3,
	eRIGHT_BOTTOM = 4
};


typedef struct _tagSquare
{
	int		x;
	int		y;
	int		r;
	int		g;
	int		b;
	bool	IsActive = true;
} SQUARE;


typedef struct _tagPoo
{
	int		x;
	int		y;
	bool	IsActive = true;
	int		eDir;
} POO;


typedef struct _tagDude
{
	int x;
	int y;
	int speed = 1;
} DUDE;

