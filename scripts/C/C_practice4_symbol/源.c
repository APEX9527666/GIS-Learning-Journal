#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//计算机组成原理，二进制及操作符练习
//完成时间：2026-9-29~2026-9-30
//练习内容：掌握各种进制操作，运用各种操作符

//练习1：不能创建临时变量，实现两个整数的交换
//首先，我们先想想如何实现两个整数的交换，C语言中的'='是把右边的值赋给左边，左边原来的值就被覆盖、丢失了
//所以不能直接赋值，我们想象有两个瓶子，一个装着醋，另一个装着酱油，如果需要交换两个容器，可以在找一个瓶子
//先把醋腾到空瓶子里，再把酱油倒进原来的醋瓶，再把醋倒入原来的酱油瓶，代码实现如下：
//int main()
//{
//    int a = 0;
//    int b = 0;
//    scanf("%d %d", &a, &b);//a=10 b=20
//    printf("交换前：a = %d b = %d\n", a, b);
//
//    //交换
//    //err
//    //a = b;
//    //b = a;
//    int c = 0;
//    c = a;
//    a = b;
//    b = c;
//
//    printf("交换后：a = %d b = %d\n", a, b);
//    return 0;
//}

//同样，也可以这么写
//int main()
//{
//    int a = 0;
//    int b = 0;
//    scanf("%d %d", &a, &b);//a=10 b=20
//    printf("交换前: a = %d b = %d\n", a, b);
//
//    //交换
//    a = a + b;
//    b = a - b;
//    a = a - b;
//
//    printf("交换后: a = %d b = %d\n", a, b);
//    return 0;
//}

//不过，我们发现，对于int整数型存储是有界的，当数字较大时可能会出现初始a和b能存储
//但是二者相加后的和过大，超出int字符所能存储的最大字节，此时会造成溢出的问题

//我们可以用“异或”写法根治此问题
//异或的特点：
//0 ^ a = a
//a ^ a = 0
//异或是支持交换律的
//
//3 ^ 3 ^ 5 = 5
//3 ^ 5 ^ 3 = 5

//int main()
//{
//    int a = 0;
//    int b = 0;
//    scanf("%d %d", &a, &b);//a=10 b=20
//    printf("交换前: a = %d b = %d\n", a, b);
//
//    //交换
//    a = a ^ b;//a' = a ^ b
//    b = a ^ b;//b = a' ^ b = a ^ b ^ b = a
//    a = a ^ b;//a = a' ^ b = a ^ b ^ a = b
//
//    printf("交换后: a = %d b = %d\n", a, b);
//    return 0;
//}



//练习2：求一个整数存储在内存中二进制中1的个数
//想实现这个效果，就求出每一位，看看是不是1，然后统计
//想要得到一个数的最低的二进制位：
//num & 1 就能得到num的二进制中的最低位，代码如下;
//int main()
//{
//    int num = 0;
//    int count = 0;
//    scanf("%d", &num);
//
//    int i = 0;
//    for (i = 0; i < 32; i++)
//    {
//        if (((num >> i) & 1) == 1)
//            count++;
//    }
//
//    printf("%d\n", count);
//    return 0;
//}

//但这个代码的效率不高，因为要逐个计算，进阶写法可以用 n = n & (n - 1)
//int main()
//{
//	int num = 0;
//	int count = 0;
//	scanf("%d", &num);
//
//	while (num)
//	{
//		num = num & (num - 1);
//		count++;
//	}
//
//	printf("%d\n", count);
//
//	return 0;
//}



//练习3：将13二进制的第5位修改为1，然后再改回0
//编写代码将13二进制序列的第5位修改为1，然后再改回0
//00000000000000000000000000001101
//00000000000000000000000000010000
//00000000000000000000000000011101
//
//int main()
//{
//	int n = 13;
//	int k = 5;
//	n |= (1 << (k - 1));
//	printf("%d\n", n);//29
//	//00000000000000000000000000011101
//	//11111111111111111111111111101111
//	//00000000000000000000000000001101
//
//	n &= ~(1 << (k - 1));
//	printf("%d\n", n);//13
//	return 0;
//}
//



//练习4：自定义结构体及访问
//struct Student
//{
//	char name[20];//名字
//	int age;//年龄
//	float score;//成绩
//};
//
//struct Student
//{
//	char name[20];//名字
//	int age;//年龄
//	float score;//成绩
//} s6, s7, s8;//全局变量
//
//struct Book
//{
//	char name[20];
//	float price;
//	int id;
//};
//
////全局变量
//struct Student s4;
//struct Student s5;
//
//int main()
//{
//	//int num1 = 0;
//	//局部变量
//	struct Student s1;
//	struct Student s2;
//	struct Student s3;
//
//	return 0;
//}

//
//
//struct Student
//{
//	char name[20];//名字
//	int age;//年龄
//	float score;//成绩
//};
//
//struct Test
//{
//	int n;
//	char c;
//	struct Student s;
//	double d;
//};
//
//int main()
//{
//	struct Student s3 = { 0 };
//
//	struct Student s1 = {"lisi", 18, 85.5f};
//	struct Student s2 = {.score = 65.5f, .age = 12, .name = "王五"};
//	struct Test t = { 100, 'q', {"zhangsan", 19, 90.0f}, 3.14};
//	//打印结构体的数据
//	printf("%s %d %.1f\n", s1.name, s1.age, s1.score);
//	printf("%d %c %s %d %.1f %.2f\n", t.n, t.c, t.s.name, t.s.age, t.s.score, t.d);
//	//结构体变量.成员名
//	//结构体成员访问操作符
//
//	s1.age = 28;
//	printf("%s %d %.1f\n", s1.name, s1.age, s1.score);
//
//	return 0;
//}

//char 类型的取值范围是：-128~127
//
//int main()
//{
//	char a = 10;
//	//00000000000000000000000000001010
//	//00001010 - a   截断
//	char b = 120;
//	//00000000000000000000000001111000
//	//01111000 - b
//	char c = 0;
//	//
//	c = a + b;
//	//00001010 - a
//	//
//	//01111000 - b
//	//00000000000000000000000000001010
//	//00000000000000000000000001111000
//	//00000000000000000000000010000010
//	//10000010 - c
//	//11111111111111111111111110000010
//	//10000000000000000000000001111101
//	//10000000000000000000000001111110
//	printf("%d\n", c);//-126
//
//	//%d 是以10进制的形式打印有符号的正数
//	//%u 是以10进制的形式打印无符号的正数
//	return 0;
//}


//#include <stdio.h>
//
//int fun()
//{
//    static int count = 1;
//    return ++count;
//}
//
//int main()
//{
//    int answer;
// 
//    answer = fun() - fun() * fun();
//
//    printf("%d\n", answer);//输出多少？
//    return 0;
//}
//

#include <stdio.h>
int main()
{
    int i = 1;
    int ret = (++i) + (++i) + (++i);

    printf("%d\n", ret);//?

    printf("%d\n", i);//4

    return 0;
}