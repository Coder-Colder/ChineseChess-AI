#include "board.h"
#include <iostream>
#include <cassert>
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
        |      |      |      |      |      |      |      |      |        红
        |      |      |      |      |      |      |      |      |
    3   兵-----+------兵-----+------兵-----+------兵-----+------兵
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    4   +------+------+------+------+------+------+------+------+-
        |         楚                          汉                |
        |                河                          界         |
    5   +------+------+------+------+------+------+------+------+-
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |
    6   卒-----+------卒-----+------卒-----+------卒-----+------卒
        |      |      |      |      |      |      |      |      |
        |      |      |      |      |      |      |      |      |        黑
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
            board[i][j] = NoChess;
        }
    }
    
    board[0][0] = R_CAR1;
    board[0][8] = R_CAR2;
    board[9][0] = B_CAR1;
    board[9][8] = B_CAR2;

    board[0][1] = R_HORSE1;
    board[0][7] = R_HORSE2;
    board[9][1] = B_HORSE1;
    board[9][7] = B_HORSE2;

    board[0][2] = R_BISHOP1;
    board[0][6] = R_BISHOP2;
    board[9][2] = B_BISHOP1;
    board[9][6] = B_BISHOP2;

    board[0][3] = R_GUARD1;
    board[0][5] = R_GUARD2;
    board[9][3] = B_GUARD1;
    board[9][5] = B_GUARD2;

    board[0][4] = R_KING;
    board[9][4] = B_KING;

    board[2][1] = R_CANNON1;
    board[2][7] = R_CANNON2;
    board[7][1] = B_CANNON1;
    board[7][7] = B_CANNON2;

    board[3][0] = R_PAWN1;
    board[3][2] = R_PAWN2;
    board[3][4] = R_PAWN3;
    board[3][6] = R_PAWN4;
    board[3][8] = R_PAWN5;
    board[6][0] = B_PAWN1;
    board[6][2] = B_PAWN2;
    board[6][4] = B_PAWN3;
    board[6][6] = B_PAWN4;
    board[6][8] = B_PAWN5;

}

void Board::moveNext(MOVEMENT & move)
{
    int src_x = move.src.x;
    int src_y = move.src.y;
    int dst_x = move.tar.x;
    int dst_y = move.tar.y;

    int src_chess_id = board[src_y][src_x];
    int dst_chess_id = board[dst_y][dst_x];

    if(is_Chess(dst_chess_id))
        chess[dst_chess_id]->exist = false;
    chess[src_chess_id]->setPos(move.tar);
    
    board[dst_y][dst_x] = board[src_y][src_x];
    board[src_y][src_x] = NoChess;
}

bool Board::getRKing(CHESSPOS & pos)
{
    for(int i = 0; i <= 2; i++)
    {
        for(int j = 3; j <= 5; j++)
            if(board[i][j] == R_KING)
            {
                pos.x = j;
                pos.y = i;
                return true;
            }
    }
    return false;
}
bool Board::getBKing(CHESSPOS & pos)
{
    for(int i = 0; i <= 2; i++)
    {
        for(int j = 3; j <= 5; j++)
            if(board[i][j] == B_KING)
            {
                pos.x = j;
                pos.y = i;
                return true;
            }
    }
    return false;
}
