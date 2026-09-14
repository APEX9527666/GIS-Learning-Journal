//阶段综合练习——扫雷游戏
//完成时间:2026--9-12~2026-9-14
//练习内容：设计二维数组和定义函数嵌套循环使用

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "game.h"//引入游戏函数声明

//打印菜单
void menu()
{
	printf("--------------------------------\n");
	printf("------------ 1.play ------------\n");
	printf("------------ 0.exit ------------\n");
	printf("--------------------------------\n");
}

//游戏主逻辑
void game()
{
	//mine数组存放地雷的信息（'1'表示雷，'0'表示非雷）
	char mine[ROWS][COLS];//存放的是雷的信息
	//show数组存放排查出雷的信息（'*'表示未排查，数字表示周围雷数）
	char show[ROWS][COLS];//存放的是排查出的雷的信息

	// 初始化随机数种子（只调用一次）
	srand((unsigned int)time(NULL));

	//初始化棋盘
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');

	//打印棋盘
	DisplayBoard(show, ROW, COL);

	//布置雷
	SetMine(mine, ROW, COL);
	//将雷的分布隐藏
	//DisplayBoard(mine, ROW, COL);

	//排雷
	FindMine(mine, show, ROW, COL);

}

int main()
{
	int input = 0;
	do 
	{
		menu();//调用菜单函数
		printf("请选择:");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			game();//进入游戏
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，重新选择\n");
			break;
		}
		//
	} while (input);//输入非0时循环，非0时退出

	return 0;
}