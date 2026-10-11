//深入理解指针（1）
//完成时间：2026-10-8~2026-10-9
//练习内容：初始指针

#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>

//指针变量
//%p 是专门用来打印地址的

//int main()
//{
//	int a = 10;
//	//&a;//& -- 取地址操作符，取出的是a的地址
//	//printf("%p\n", &a);
//	int* p = &a;//p就是指针变量，指针变量就是用来存放地址的变量
//
//	return 0;
//}



//解引用操作符
//int main()
//{
//	int a = 100;
//	int* p = &a;
//	printf("%d\n", a);//*是解引用操作符，*p的意思是通过p里边存放的地址，找到p指向的对象，也就是a，所以*p就是a
//	
//	*p = 10;
//	printf("%d\n", a);
//
//	return 0;
//}



//指针变量的大小与类型无关
//int main()
//{
//	int a = 10;
//	printf("%p\n", &a);
//	//printf("%zu\n", sizeof(char*));
//	//printf("%zu\n", sizeof(short*));
//	//printf("%zu\n", sizeof(int*));
//	//printf("%zu\n", sizeof(long *));
//	//printf("%zu\n", sizeof(long long*));
//	//printf("%zu\n", sizeof(float*));
//	//printf("%zu\n", sizeof(double*));
//
//	return 0;
//}



//void*指针
//int main()
//{
//	char ch = 'w';
//	//int*pc = &ch;//char*
//	int a = 10;
//	void* pv1 = &ch;
//	void* pv2 = &a;
//	//*pv2;
//	//pv2++;
//
//	return 0;
//}



//指针运算
//int main()
//{
//	char arr[] = "abcdef";
//	//[a b c d e f \0]
//	size_t len = strlen(arr);//统计的是\0之前的字符个数
//	printf("%zu\n", len);
//
//	return 0;
//}