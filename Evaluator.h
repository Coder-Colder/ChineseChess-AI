#pragma once
#ifndef EVALUATOR_H
#define EVALUATOR_H
#include "Chess.h"
#include "define.h"

#define VALUE_RANDMAX 2147483647
#define VALUE_RANDMIN -2147483648

//���������̹�ֵ�����غ췽������ֵ - �ڷ�������ֵ������Ϊ��¼��ǰ���״̬������
int evaluateBoard(char board[10][9]);

//���������̹�ֵ�����غ췽������ֵ - �ڷ�������ֵ�����Ż���������һ����¼����״̬��ָ�����飬����ʱ�临�Ӷȣ�
int evaluateBoard(char board[10][9], Chess * chessman[32]);

#endif // !EVALUATOR_H


