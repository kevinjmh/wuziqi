#include "CAlgorithm.h"
#include "CJudge.h"
#include <vector>
#include<math.h>
using namespace std;

 

CPoint CAlgorithm::ComputePiecePosition(const CChessBoard& board,const CPlayer& player,CJudge& judge)
{
 CChessBoard boardtemp;
 boardtemp=board;      //���´��һ�����̱�
 int myvalue[SIZE+1][SIZE+1];
 int opponentvalue[SIZE+1][SIZE+1];
   
 int col=0;
 int row=0;
 for (col=0;col<=SIZE;col++)
 {
  for (row=0;row<=SIZE;row++ )
  {
   myvalue[col][row]=-2;
   opponentvalue[col][row]=-2;
  }
 }
    int mycolor=player.ReturnColor();
    int opponentcolor=0;        //���������ɫ
 if (black==mycolor)
 {
  opponentcolor=white;
 }
 else
  opponentcolor=black;

 


 
 
 
 

 int FValue[6][2]={{0,0},{1,4},{16,80},{400,2000},{10000,50000},{100000,100000}};
 int LValue[6][2]={{0,0},{1,4},{8,40},{200,1000},{5000,25000},{50000,50000}};
    CPoint temp;
 CPiece piece;
 for (col=1;col<=SIZE;col++)
 {
  for (row=1;row<=SIZE;row++)
  {  
   temp.SetPoint(col,row);
   if (blank==boardtemp.ReturnPieceAt(temp))    
   { piece.SetColor(mycolor);
    piece.SetPosition(temp);
    boardtemp.PlacePiece(piece);          //�ȼ����ڴ˿�λ�����Լ�������
    if (!judge.IsForbidden(boardtemp,piece))    //���̸õ�Ϊ��λʱ
    {     
       int a[4][2];
       judge.ComputeChessModel(boardtemp,piece,a);  
       for (int k=0;k<4;k++)
       {
        
        myvalue[col][row]+=FValue[a[k][0]][a[k][1]];
       }
       piece.SetColor(opponentcolor);
       boardtemp.PlacePiece(piece);           //��������ڴ˿�λ�����˶��ֵ���    
       judge.ComputeChessModel(boardtemp,piece,a);
     
       for (int k=0;k<4;k++)
       {
        
        opponentvalue[col][row]+=LValue[a[k][0]][a[k][1]]; 
       }   
    }
    boardtemp.ReturnPieceAt(temp);
            }
  }
 }//�������������ϣ�

 int mymax=-2;
 int opponentmax=-2;
 vector<CPoint> mymaxpoint;
 vector<CPoint> opponentmaxpoint;
 mymaxpoint.erase(mymaxpoint.begin(),mymaxpoint.end());
 opponentmaxpoint.erase(opponentmaxpoint.begin(),opponentmaxpoint.end());

  for (col=1;col<=SIZE;col++)
  {
   for (row=1;row<=SIZE;row++)
   {
        mymax=__max(mymax,myvalue[col][row]);  //�ҳ����������ֵ
    
   
   }
  }
  for (col=1;col<=SIZE;col++)
  {
   for (row=1;row<=SIZE;row++)
   {
       if (mymax==myvalue[col][row])
       {
        mymaxpoint.push_back(CPoint(col,row));     //��¼���ֵ������
       }
     
   
   }
  }

  for (col=1;col<=SIZE;col++)
  {
   for (row=1;row<=SIZE;row++)
   {
        opponentmax=__max(opponentmax,opponentvalue[col][row]); //�ҳ����������ֵ
    
   
   }
  }
  for (col=1;col<=SIZE;col++)
  {
   for (row=1;row<=SIZE;row++)
   {
       if (opponentmax==opponentvalue[col][row])
       {
        opponentmaxpoint.push_back(CPoint(col,row));     //��¼���ֵ������
       }
     
   
   }
  }
  
  int x0=(SIZE+1)/2;   //�������ĵ�λ��
  int y0=(SIZE+1)/2;
  int d;              //�����ĵ�����ĵ�ľ���ֵ
  CPoint dpoint;      //���������ĵ�����ĵ�
       if (mymax>=opponentmax)
    {
     d=pow((float)mymaxpoint[0].x-x0,2)+pow((float)mymaxpoint[0].y-y0,2);       //ѡ�������ĵ�����ĵ�
     dpoint=mymaxpoint[0];
     for(int k=1;k<mymaxpoint.size();k++)
     {
   
      int dtemp=pow((float)mymaxpoint[k].x-x0,2)+pow((float)mymaxpoint[k].y-y0,2);
      if (dtemp<=d)
      {
       d=dtemp;    //��С�������
       dpoint=mymaxpoint[k];
      }
     }
     return dpoint;

    }
    else
    {
     d=pow((float)opponentmaxpoint[0].x-x0,2)+pow((float)opponentmaxpoint[0].y-y0,2);       //ѡ�������ĵ�����ĵ�
     dpoint=opponentmaxpoint[0];
     for(int k=1;k<opponentmaxpoint.size();k++)
     {
   
      int dtemp=pow((float)opponentmaxpoint[k].x-x0,2)+pow((float)opponentmaxpoint[k].y-y0,2);
      if (dtemp<=d)
      {   
       d=dtemp;   ////��С�������
       dpoint=opponentmaxpoint[k];
      }
     }
     return dpoint;

    }
  
 
}