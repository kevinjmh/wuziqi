#pragma once
#include <string>

//#include "ChessMan.h"
#define BOARD_SIZE 15
using namespace std;

enum COLOR{ NONE=0, BLACK = 99, WHITE = 100 };

class ChessBoard
{
public:
	ChessBoard();
	void init();
	void printBoard();
	bool isPosValid(int,int);
	bool add(int posX, int posY, COLOR col);
	string get(int posX, int posY);
	bool isGameOver(int posX, int posY, COLOR c);
	COLOR m[BOARD_SIZE][BOARD_SIZE];

};

