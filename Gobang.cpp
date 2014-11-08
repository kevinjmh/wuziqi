#include "Gobang.h"
#include <iostream>
using namespace std;

//@description: gobang 五子棋 five-in-a-row
//@author: Manhua Jiang 2014E8017761036@ucas

Gobang::Gobang(){	

}

void Gobang::isContinue(COLOR c){
	if(stepCount>=225){
		CONTINUE=false;
		cout<<"【平局】"<<endl;
	}
	else	if(chessboard.isGameOver(posX, posY,c)){
		CONTINUE=false;
		cout<<lastPlayer<<"【>>>胜利<<<】"<<endl;
	}
	return ;
}

void Gobang::update(){
	system("cls");
	cout << "x: 退出   r：新游戏\n下棋输入范例：1a或1A\n";
	chessboard.printBoard();
}

 int Gobang::letterToNum(char a){
	 if (a>=97 && a<=122) {
		 return a - 97;
	 }else if (a >= 65 && a <= 90) {
		 return a - 65;
	 }
	 else{
		 return -1;
	 }	 
}

 int getRand(int a, int b){
	 return rand()%(b-a+1)+a;
 }

 //默认玩家黑子 电脑白子
 void Gobang::AINext(){
	 int max=-1,temp,max_x,max_y;
	 for(int x=0;x<15;x++){//遍历棋盘所有位置
          for(int y=0;y<15;y++){
			  if(chessboard.m[x][y]==0){
				temp=pointScore(x,y);
				if(max<=temp){//todo: 同分的全部存储 然后随机一个
					max=temp;
					max_x=x;
					max_y=y;
				}
			  }
		  }
	 }
	 posX=max_x;
	 posY=max_y;
 }

//AI遍历棋盘，找出最好的位置下棋
  int Gobang::pointScore(int x, int y){
	int numContinueChess, numEmpty;
    int score[8];//敌我4个方向（左斜、横、右斜、竖）评分
	memset(score,0,sizeof(score));
    int scoreRecordCount=0;
    COLOR color=WHITE;

    do{
        for (int i=-1;i<1;i++){
            for (int j=-1;j<=1;j++){
                if( (i!=0 || j!=0) && (i+j<=0)){//排除自身
                    numContinueChess=0, numEmpty=0;
                    for (int k=1;k<5;k++){ 
                        if(chessboard.isPosValid(x+k*i, y+k*j)){
                            if(chessboard.m[x+k*i][y+k*j]==color){
                                numContinueChess++;
                            }else if(chessboard.m[x+k*i][y+k*j]==0){
                                numEmpty++;break; 
                            } else break;                             
                        } else break;  
                    }
                    for (int k=-1;k>-5;k--) { //反方向的判断
                        if(chessboard.isPosValid(x+k*i, y+k*j)){
                            if(chessboard.m[x+k*i][y+k*j]==color){
                                numContinueChess++;
                            }else if(chessboard.m[x+k*i][y+k*j]==0){
                                numEmpty++;break; 
                            }else break;                            
                        } else break;  
                    }
                    //评分
					if(numContinueChess==4)     { //5个棋子，分数要高点
						return color==WHITE?  10001: 10000;  
					}else if(numContinueChess==3) {  //4个棋子 
						  if(numEmpty==1)      {
							  score[scoreRecordCount]+=50*(1+(int)color/100);     //死4 
						  }else if(numEmpty==2) {
							 return 200*(1+(int)color/100);    //活4
						  } 
					}else if(numContinueChess==2){    //3个棋子 
						  if(numEmpty==1)       {score[scoreRecordCount]+=5*(1+(int)color/100);}  //死3       
						  else if(numEmpty==2)  {score[scoreRecordCount]+=20*(1+(int)color/100);}    //活3
					}else if(numContinueChess==1){ //2个棋子  
						score[scoreRecordCount]+=(1+(int)color/100); 
					}			
                }
            }
        }
        color=BLACK;
		scoreRecordCount++;
    }while(scoreRecordCount<7);

     //....计算完两个玩家4个方向之后
    int score_max=score[0];
    for (int m = 1; m < 8; m++){
        if (score[m] > score_max)
            score_max = score[m];
    }
	return score_max;

	/*int score_sum=0;
    for(int m = 0; m < 8; m++){
        score_sum+=score[m];
    }
   
	score_sum=score_sum/8;
    return (score_max > score_sum ? score_max : score_sum);
    */
 }


 
 void Gobang::computeNextMove(COLOR c){
	  lastPlayer= (c==BLACK?"【黑方】":"〖白方〗");
	  /////
	  int dis_x=0;
	  int dis_y=0;
	  if(stepCount==1){//第一步在玩家周围随便放
		  while((dis_x==0 && dis_y==0) || !chessboard.isPosValid(posX+dis_x, posY+dis_y)){
			  dis_x=getRand(-1,1);
		      dis_y=getRand(-1,1);
		  }
		  posX=posX+dis_x;
		  posY=posY+dis_y;
	  }else{
		  //机器人算法
		  AINext();		  
	  }
	  chessboard.add(posX, posY,c);
	  /////
	  update();
	  cout<<lastPlayer<<"上一步棋在【"<<posX+1<<(char)(posY+65)<<"】"<<endl;
	  isContinue(c); 
 }

 void Gobang::nextMove(COLOR c){
	 string input;
	 lastPlayer= (c==BLACK?"【黑方】":"〖白方〗");
	 cout <<lastPlayer<< "请下棋： ";
	 do{
		 cin >> input;
		 if (input=="x"){
			 exit(0);
		 }
		 else if (input=="r"){
			 CONTINUE=false;
			 return;
		 }
		 posY = letterToNum(input[input.size() - 1]);
		 input.erase(input.length() - 1);
		 posX = atoi(input.c_str()) - 1;
	 } while (!chessboard.add(posX, posY, c));
	 update();
	 cout<<lastPlayer<<"上一步棋在【"<<posX+1<<(char)(posY+65)<<"】"<<endl;
	 isContinue(c); 
 }

 void Gobang::p2p(){
	 update();
	while (CONTINUE){
		stepCount%2==0?nextMove(BLACK):nextMove(WHITE); 
		stepCount++;
	}
 }

  void Gobang::p2c(){
	 update();
	while (CONTINUE){
		stepCount%2==0?nextMove(BLACK):computeNextMove(WHITE); 
		stepCount++;
		//cout << posX<<" "<< posY<<endl;	
	}
 }

  			 			
void Gobang::start(){
	while(1){	
		stepCount=0;
		CONTINUE=true;
		initCmd();
		//askGameMode();
		cout << "请选择游戏模式：\n0. 人机对战\n1. 双人对战\nx. 退出"<< endl;
		char choose;
		cin>>choose;
		switch(choose){
			case '0': p2c();break;
			case '1': p2p();break;
			case 'x':exit(0);
		}			
		chessboard.init();
		system ("color 03");
		system("pause");
	}
}

void Gobang::initCmd(){
	system("mode con cols=50 lines=25");
	system("title 五子棋 five-in-a-row");
	system("cls");
	system("color 3e");	
	cout << endl << " === Welcome to Five In A Row === " << endl << endl;
}

void main(){	
	Gobang gobang;
	gobang.start();
	system("pause");
}
