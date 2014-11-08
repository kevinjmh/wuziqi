#ifndef  COrganizer_H_H_H_
#define COrganizer_H_H_H_
#include "CShow.h"
#include "CPlayer.h"
#include "CPoint.h"


class COrganizer
{
public:
 void DecideGameMode(CShow &show);
 int ReturnMode();
 void DecideWhoGoFirst(CPlayer& p1,CPlayer& p2);

 string ReturnPlayer1Name();
 string ReturnPlayer2Name();
 int ReturnFlagTurn();
 CPoint GetInputPosition();
 void ExchangeFlag();
 char GetIsContinueResult();

private:
 int mode;         //1���˶�ս��2�˻���ս
 string player1name;   //1���������
 string player2name;   //2���������
 int flagturn;
};

#endif