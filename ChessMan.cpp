#include "ChessMan.h"

ChessMan::ChessMan()
{
}

ChessMan::ChessMan(int a, int b)
{
	SetPoint(a, b);
}

void ChessMan::SetPoint(int a, int b)
{
	x = a;
	y = b;
}

void ChessMan::operator=(const ChessMan& p)
{
	x = p.x;
	y = p.y;
}

bool ChessMan::operator ==(const ChessMan& p)
{
	if (x == p.x && y == p.y)
		return true;
	else
		return false;
}
