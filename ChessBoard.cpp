#include "ChessBoard.h"
#include <iostream>

ChessBoard::ChessBoard(){
	init();
}

void ChessBoard::init(){
	for(int x=0;x<15;x++){//������������λ��
          for(int y=0;y<15;y++){
			  m[x][y]=NONE;
		  }
	}
}


bool ChessBoard::isGameOver(int posX, int posY, COLOR c){
	int number=0;  
	for (int i=-1;i<1;i++){
		for (int j=-1;j<=1;j++){
			if( (i!=0 || j!=0) && (i+j<=0)){//�ų�����
				for (int k=1;k<5;k++){ 
				    if(isPosValid(posX+k*i, posY+k*j) && m[posX+k*i][posY+k*j]==c){
						number++;
					} else {
						break;
					} 
				}
				for (int k=-1;k>-5;k--) { //��������ж�
					if(isPosValid(posX+k*i, posY+k*j) && m[posX+k*i][posY+k*j]==c){
						number++;
					} else {
						break;
					}  
				}
				if(number>=4) {
                     return true;  
                }
                else{
                     number=0;
                }
			}
		}
	}
	return false;
}

bool ChessBoard::isPosValid(int posX, int posY){
	//cout << posX<<" "<< posY<<endl;
	if (0 <= posX && posX<BOARD_SIZE && 0 <= posY && posY<BOARD_SIZE){
		return true;
	}
	else{
		return false;
	}
}

bool ChessBoard::add(int posX, int posY, COLOR col){
	if (!isPosValid(posX, posY)){
		cout << "λ������������������룺 ";
		return false;
	}
	if (m[posX][posY] == BLACK || m[posX][posY] == WHITE){
		cout << "��ǰλ���������ӣ����������룺 ";
		return false;
	}
	m[posX][posY] = col;
	return true;
}

string ChessBoard::get(int posX, int posY){
	//try{
		//COLOR item = m.at(posX).at(posY);
		COLOR item = m[posX][posY];
			if (item == BLACK){
				return "��";
			}
			else if (item == WHITE)	{
				return "��";
			}
		//}
		//catch (exception e)
		else{
		if (posX==14){
			if (posY==0)	{
				return "��";
			}
			else if (posY == 14)	{
				return "��";
			}
			else{
				return "��";
			}
		}
		else if (posX == 0)	{
			if (posY == 0){
				return "��";
			}
			else if (posY == 14){
				return "��";
			}
			else{
				return "��";
			}
		}
		else if (posY == 0)	{
			return "��";
		}
		else if (posY == 14){
			return "��";
		}
		else{
			return "��";
		}		
	}
}

void ChessBoard::printBoard(){
	cout << endl;
	for (int i = BOARD_SIZE-1; i>=0; i--){
		printf("\t%2d", i+1);
		for (int j = 0; j<BOARD_SIZE; j++){
			cout << get(i, j);
		}
		cout << endl;
	}
	cout << "\t  A B C D E F G H I J K L M N O\n" << endl;
}
