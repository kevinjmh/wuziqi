#pragma once
#include "Chessboard.h"

//enum GAME_MODE{ HUMAN_VS_HUMAN = 0, HUMAN_VS_PC = 1 };

class Gobang
{
public:	
	Gobang();
	void start();
	void update();
	void p2p();
	void p2c();
	void nextMove(COLOR);
	void computeNextMove(COLOR);	
	void isContinue(COLOR);
	void AINext();
	int Gobang::pointScore(int x, int y);
	void Gobang::initCmd();
	int letterToNum(char);
	
private:
	int posX;
	int posY;
	int stepCount;
	string lastPlayer;
	bool CONTINUE;
	ChessBoard chessboard;
};

