#pragma once
#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "Chess.h"
#include "define.h"

#define VALUE_RANDMAX 2147483647
#define VALUE_RANDMIN -2147483648

//对整个棋盘估值，返回红方棋力估值 - 黑方棋力估值，参数为记录当前棋局状态的棋盘
int evaluateBoard(char board[10][9]);

//对整个棋盘估值，返回红方棋力估值 - 黑方棋力估值，（优化：参数多一个记录棋子状态的指针数组，降低时间复杂度）
int evaluateBoard(char board[10][9], Chess * chessman[32]);

#endif // !EVALUATOR_H


