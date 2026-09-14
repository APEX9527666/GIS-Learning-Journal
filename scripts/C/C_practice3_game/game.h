#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//设置雷的数量
#define EASY_COUNT 10

//实际棋盘的行和列
#define ROW 9
#define COL 9

//为了方便边界雷的计算，将行和列扩大一圈（行、列均+1）
#define ROWS ROW+2
#define COLS COL+2

//初始化棋盘
//board: 二维数组, r: 行, c: 列, char set: 初始化的字符
void InitBoard(char board[ROWS][COLS], int r, int c, char set);

//打印棋盘
//board: 二维数组, r: 行, c: 列, int c: 列数
void DisplayBoard(char board[ROWS][COLS], int r, int c);

//布置雷
//board: 二维数组, r : 行, c : 列, int c : 雷的数量
void SetMine(char board[ROWS][COLS], int r, int c);

//排查雷
//mine: 存放雷的数组, show: 展示给玩家的数组, r: 行, c: 列
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c);
