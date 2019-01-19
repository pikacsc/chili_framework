#pragma once


struct Position
{
	int x = 400;
	int y = 400;
} typedef POS;


struct Line
{
	int x1;
	int y1;
	int x2;
	int y2;
} typedef LINE;


struct Cursor
{
	int x;
	int y;
	int lineGap;
	int lineLength;
	LINE left = { (x - lineGap - lineLength),y,(x - lineGap),y };
	LINE top = { x,(y - lineGap - lineLength),x,(y - lineGap) };
	LINE right = { (x + lineGap),y,(x + lineGap + lineLength),y };
	LINE bottom = { x,(y + lineGap),x,(y + lineGap + lineLength) };
} typedef CURSOR;

struct iRect
{
	Line left;
	Line top;
	Line right;
	Line bottom;
} typedef iRECT;


struct targetingBox
{
	int x;
	int y;
	int lineGap;
	int lineLength;
	LINE LeftTop_x = { (x - lineGap - lineLength),(y - lineGap - lineLength),(x - lineGap),(y - lineGap - lineLength) };
	LINE LeftTop_y = { (x - lineGap - lineLength),(y - lineGap - lineLength),(x - lineGap - lineLength),(y - lineGap) };

	LINE RightTop_x = { (x + lineGap + lineLength),(y - lineGap - lineLength),(x + lineGap),(y - lineGap - lineLength) };
	LINE RightTop_y = { (x + lineGap + lineLength),(y - lineLength),(x + lineGap + lineLength),(y - lineGap - lineLength) };

	LINE LeftBottom_x = { (x - lineGap - lineLength),(y + lineGap + lineLength),(x - lineGap),(y + lineGap + lineLength) };
	LINE LeftBottom_y = { (x - lineGap - lineLength),(y + lineGap),(x - lineGap - lineLength),(y + lineGap + lineLength) };

	LINE RightBottom_x = { (x + lineGap),(y + lineGap + lineLength),(x + lineGap + lineLength),(y + lineGap + lineLength) };
	LINE RightBottom_y = { (x + lineGap + lineLength),(y + lineGap),(x + lineGap + lineLength),(y + lineGap + lineLength) };
};