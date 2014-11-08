#pragma once
class ChessMan
{
public:
	ChessMan();
	ChessMan(int, int);
	void SetPoint(int, int);
	void operator=(const ChessMan&);
	bool operator==(const ChessMan&);
	int x;
	int y;
	int color;
	//inline string toString()
};

