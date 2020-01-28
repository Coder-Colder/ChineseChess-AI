#include "Human.h"
#include <iostream>
using namespace std;

void Human::play(Board &board, MOVEMENT &mvmt)
{
	cout<<"黑方走子：请输入走子方式（格式：srcx srcy tarx tary)"<<endl;
	cin>>mvmt.src.x>>mvmt.src.y>>mvmt.tar.x>>mvmt.tar.y;
	while(!board.board[mvmt.src.y][mvmt.src.x]->moveValid(mvmt.tar,board.m_board))
	{
	    cout<<"走子方式不合法！！请重新输入！"<<endl;
	    cin>>mvmt.src.x>>mvmt.src.y>>mvmt.tar.x>>mvmt.tar.y;
	}
}
