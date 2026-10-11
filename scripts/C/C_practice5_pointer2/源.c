//深入理解指针2
//完成时间：2026-10-11~2026-10-12
//练习内容：conest修饰指针、野指针、传址调用

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

//conest深入了解
//int main()
//{
//	const int n = 10;//常变量 - 具有常属性的变量（不能被修改了）骨子里还是一个变量
//	n = 100;
//	printf("%d\n", n);
//
//	const int n = 10;//C99语言之前，这个n不能放在数组的大小指定的位置
//	int arr[n];
//	arr[0] = 1;
//
//	const int n = 10;
//
//	int* p = &n;
//	*p = 100;
//
//	printf("%d\n", n);
//
//	return 0;
//}
//这个代码无法运行，因为const把n变成常属性的

//int main()
//{
//	const int n = 10;
//
//	int* p = &n;
//	*p = 100;
//
//	printf("%d\n", n);
//
//	return 0;
//}
//但是这个代码却能正常输出100
//这个代码很危险，因为这里通过定义一个指针p来接收常量n的地址，并强行通过指针p把n所在的内存值改了
//为什么这里修改没有报错呢？这是因为当程序执行 int* p = &n; 时，因为使用了取地址符&，编译器被迫在栈内存上为n分配真正的内存空间
//而栈内存是可读可写的，执行 *p = 100; 时，程序在运行期直接修改了这块栈内存上的数据
//但如果把 const int n = 10; 放到全局作用域（在函数外），它会被存在只读内存中，执行 *p = 100; 时程序会直接崩溃



//assert断言是常用的防御型编程手段
//#include <assert.h>
//int main()
//{
//	int a = 10;
//	int* p = NULL;
//	//....
//
//
//	assert(p != NULL);
//	printf("%d\n", *p);
//	//if (p != NULL)
//	//{
//	//	//...
//	//}
//
//	return 0;
//}
//由于p是空指针，所以assert在此处终止了程序，打印如下：
//Assertion failed: p != NULL, file E:\GIS_Learning\scripts\C\C_practice5_pointer2\源.c, line 58
//assert用于捕捉程序员自己的逻辑错误，并只在调试阶段起作用
//可以通过定义NDEBUG把asert展开为((void)0)(什么都不做)以便调试程序




//任务：写一个函数用来交换两个整型

//这是拿到题目最开始的想法
//void Swap1(int x, int y)
//{
//	int z = x;
//	x = y;
//	y = z;
//}
//
//int main()
//{
//	int a = 0;
//	int b = 0;
//	scanf("%d %d", &a, &b);
//	//交换
//	printf("交换前: a = %d b = %d\n", a, b);
//	
//	Swap1(a, b);
//
//	printf("交换后: a = %d b = %d\n", a, b);
//
//	return 0;
//}
//执行后发现交换前后数字没有改变，接下来通过调试寻找和发现问题
//在调试界面给a、b、&a、&b添加监视，初始状态正常，问题出现在函数内部
//F11进入函数，添加监视x、y、&x、&y的值，发现x、y的地址于a、b不同，x、y有自己独立空间
//再监视z，通过运行发现函数内部的x、y可以正常交换，但是无法影响a、b

//此时，需要函数里的x、y与函数外的a、b建立联系，可以运行指针

void Swap2(int*p1, int*p2)
{
	int tmp = *p1;//tmp = a;
	*p1 = *p2;//a = b
	*p2 = tmp;//b = tmp
}

int main()
{
	int a = 0;
	int b = 0;
	scanf("%d %d", &a, &b);
	//交换
	printf("交换前: a = %d b = %d\n", a, b);
	
	Swap2(&a, &b);

	printf("交换后: a = %d b = %d\n", a, b);

	return 0;
}
//正确运行