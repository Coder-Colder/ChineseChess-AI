#include "Board.h"
#include <iostream>
#include <assert.h>
using namespace std;

/*
        0      1      2      3      4      5      6      7      8
    0   車-----馬-----相-----仕-----帥-----仕-----相-----馬-----車
        |      |      |      |  \   |   /  |      |      |      |
        |      |      |      |    \ | /    |      |      |      |
    1   +------+------+------+------+------+------+------+------+-
        |      |      |      |    / | \    |      |      |      |  
        |      |      |      |  /   |   \  |      |      |      |
    2   +------砲-----+------+------+------+------+------砲-----+-
        |      |      |      |      |      |      |      |      |  红
        |      |      |      |      |      |      |      |      |
    3   卒-----+------卒-----+------卒-----+------卒-----+------卒
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    4   +------+------+------+------+------+------+------+------+-
        |         楚                          汉                |
        |                河                          界         |
    5   +------+------+------+------+------+------+------+------+-
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    6   兵-----+------兵-----+------兵-----+------兵-----+------兵
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |  黑
    7   +------炮-----+------+------+------+------+------炮-----+-
        |      |      |      |  \   |   /  |      |      |      |
        |      |      |      |    \ | /    |      |      |      |
    8   +------+------+------+------+------+------+------+------+-
        |      |      |      |    / | \    |      |      |      |
        |      |      |      |  /   |   \  |      |      |      |
    9   车-----马-----象-----士-----将-----士-----象-----马-----车
*/

Board::Board()
{
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            board[i][j] = nullptr;
            m_board[i][j] = 0;
        }
    }
    /*board[0][0] = new R_Car();
    board[0][8] = new R_Car();
    board[9][0] = new B_Car();
    board[9][8] = new B_Car();

    board[0][1] = new R_Horse();
    board[0][7] = new R_Horse();
    board[9][1] = new B_Horse();
    board[9][7] = new B_Horse();

    board[0][2] = new R_Bishop();
    board[0][6] = new R_Bishop();
    board[9][2] = new B_Bishop();
    board[9][6] = new B_Bishop();

    board[0][3] = new R_Guard();
    board[0][5] = new R_Guard();
    board[9][3] = new B_Guard();
    board[9][5] = new B_Guard();

    board[0][4] = new R_King();
    board[9][4] = new B_King();

    board[2][1] = new R_Cannon();
    board[2][7] = new R_Cannon();
    board[7][1] = new B_Cannon();
    board[7][7] = new B_Cannon();

    board[3][0] = new R_Pawn();
    board[3][2] = new R_Pawn();
    board[3][4] = new R_Pawn();
    board[3][6] = new R_Pawn();
    board[3][8] = new R_Pawn();
    board[6][0] = new B_Pawn();
    board[6][2] = new B_Pawn();
    board[6][4] = new B_Pawn();
    board[6][6] = new B_Pawn();
    board[6][8] = new B_Pawn();*/

    m_board[0][0] = R_CAR;
    m_board[0][8] = R_CAR;
    m_board[9][0] = B_CAR;
    m_board[9][8] = B_CAR;

    m_board[0][1] = R_HORSE;
    m_board[0][7] = R_HORSE;
    m_board[9][1] = B_HORSE;
    m_board[9][7] = B_HORSE;

    m_board[0][2] = R_BISHOP;
    m_board[0][6] = R_BISHOP;
    m_board[9][2] = B_BISHOP;
    m_board[9][6] = B_BISHOP;

    m_board[0][3] = R_GUARD;
    m_board[0][5] = R_GUARD;
    m_board[9][3] = B_GUARD;
    m_board[9][5] = B_GUARD;

    m_board[0][4] = R_KING;
    m_board[9][4] = B_KING;

    m_board[2][1] = R_CANNON;
    m_board[2][7] = R_CANNON;
    m_board[7][1] = B_CANNON;
    m_board[7][7] = B_CANNON;

    m_board[3][0] = R_PAWN;
    m_board[3][2] = R_PAWN;
    m_board[3][4] = R_PAWN;
    m_board[3][6] = R_PAWN;
    m_board[3][8] = R_PAWN;
    m_board[6][0] = B_PAWN;
    m_board[6][2] = B_PAWN;
    m_board[6][4] = B_PAWN;
    m_board[6][6] = B_PAWN;
    m_board[6][8] = B_PAWN;

}

void Board::display()
{
    cout<<"  ";
    for(int i = 0; i < 9; i++)
        cout<<i<<"      ";
    cout<<endl;
    for(int i = 0; i < 10; i++)
    {
        cout<<i<<" ";
        for(int j = 0; j < 9; j++)
        {
            switch (m_board[i][j])
            {
            case R_KING:cout<<"帥";
                break;
            case B_KING:cout<<"将";
                break;
            case R_GUARD:cout<<"仕";
                break;
            case B_GUARD:cout<<"士";
                break;
            case R_HORSE:cout<<"馬";
                break;
            case B_HORSE:cout<<"马";
                break;
            case R_BISHOP:cout<<"相";
                break;
            case B_BISHOP:cout<<"象";
                break;
            case R_CANNON:cout<<"砲";
                break;
            case B_CANNON:cout<<"炮";
                break;
            case R_CAR:cout<<"車";
                break;
            case B_CAR:cout<<"车";
                break;
            case R_PAWN:cout<<"卒";
                break;
            case B_PAWN:cout<<"兵";
                break;
            case NoChess:cout<<"+-";
                break;
            default:
                assert(0);
            }
            if(j != 8)cout<<"-----";
        }
        cout<<endl;
        switch (i)
        {
        case 9:
            break;
        case 0:
        case 7:
            cout<<"  |      |      |      |  \\   |   /  |      |      |      |"<<endl;
            cout<<"  |      |      |      |    \\ | /    |      |      |      |"<<endl;
            break;
        case 1:
        case 8:
            cout<<"  |      |      |      |    / | \\    |      |      |      |"<<endl;
            cout<<"  |      |      |      |  /   |   \\  |      |      |      |"<<endl;
            break;
        case 4:
            cout<<"  |         楚                          汉                |"<<endl;
            cout<<"  |                河                          界         |"<<endl;
            break;
        case 2:
            cout<<"  |      |      |      |      |      |      |      |      |  红"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            break;
        case 6:
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |  黑"<<endl;
            break;
        default:
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            cout<<"  |      |      |      |      |      |      |      |      |"<<endl;
            break;
        }
    }
}

void Board::Next(MOVEMENT & move)
{
    
}

bool Board::getRKing(CHESSPOS & pos)
{
    return false;
}
bool Board::getBKing(CHESSPOS & pos)
{
    return false;
}
