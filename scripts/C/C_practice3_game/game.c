#define _CRT_SECURE_NO_WARNINGS

#include "game.h"//引入头文件

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int r, int c, char set)
{
	int i = 0;
	int j = 0;
	//遍历整个二维数组
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			board[i][j] = set;//将每个元素都设置为set字符（'0'或'*'）
		}
	}
}

//打印棋盘
void DisplayBoard(char board[ROWS][COLS], int r, int c)
{
	int i = 0;
	int j = 0;

	//打印列号
	for (j = 0; j <= c; j++)
	{
		printf("%d ", j);
	}
	printf("\n");

	//打印行号和棋盘内容
	for (i = 1; i <= r; i++)
	{
		printf("%d ", i);//打印行号
		for (j = 1; j <= c; j++)
		{
			printf("%c ", board[i][j]);//打印实际棋盘内容
		}
		printf("\n");
	}
	printf("\n");
}

//布置雷
void SetMine(char board[ROWS][COLS], int r, int c)
{
	int count = EASY_COUNT;//需要布置的雷数
	while (count)
	{
		//生成1~r之间的随机行号
		int x = rand() % r + 1;
		//生成1~c之间的随机列号
		int y = rand() % c + 1;

		//判断该位置是否已经布置过雷
		if (board[x][y] == '0')
		{
			board[x][y] = '1';//布置雷
			count--;//雷总数减1
		}
	}
}

//统计输入坐标周围8个格子的雷数
//此函数使用了static修饰，只在当前源文件可见
static size_t GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y] + mine[x - 1][y = 1] +
		mine[x][y - 1] + mine[x + 1][y - 1] +
		mine[x + 1][y] + mine[x + 1][y + 1] +
		mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0';
}

//排查雷
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c)
{
	int x = 0;
	int y = 0;
	int win = 0;//排出非雷的个数

	//获胜条件：排除非雷数量 = 总格数 - 雷数
	while (win < r * c - EASY_COUNT)
	{
		printf("请输入要排查的坐标:");
		scanf("%d%d", &x, &y);

		//判断坐标是否合法（在1~r和1~c之间)
		if (x >= 1 && x <= r && y >= 1 && y <= c)
		{
			//判断该坐标是否已被排查过
			if (show[x][y] == '*')
			{
				//判断是否踩到雷
				if (mine[x][y] == '1')
				{
					printf("很遗憾，你被炸死了\n");
					DisplayBoard(mine, ROW, COL);//踩雷后显示真实雷区
					break;
				}
				else
				{
					//没踩雷，统计周围雷数
					size_t count = GetMineCount(mine, x, y);
					//将雷数转换为字符并存入show数组
					show[x][y] = (char)count + '0';
					DisplayBoard(show, ROW, COL);//重新打印棋盘
					win++;//排雷成功次数+1
				}
			}
			else
			{
				printf("该坐标已经被排查过，不用重复排查\n");
			}
		}
		else
		{
			printf("输入的坐标非法，重新输入\n");
		}
	}
	//循环结束，判断是否排雷成功
	if (win == r * c - EASY_COUNT)
	{
		printf("恭喜你，排雷成功\n");
		DisplayBoard(mine, ROW, COL);//胜利后展示真实雷区
	}
}
