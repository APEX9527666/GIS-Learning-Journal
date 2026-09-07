//猜数字游戏
//完成时间：2026-9-7
//练习内容：C语言分支和循环

//游戏要求：
//1：电脑⾃动⽣成1~100的随机数
//2： 玩家猜数字，猜数字的过程中，根据猜测数据的⼤⼩给出⼤了或⼩了的反馈，直到猜对，游戏结束
//
//1，随机数生成
//1.1 rand
//C语言提供了⼀个函数叫rand，这函数是可以⽣成随机数的，函数原型如下所⽰：
//int rand(void);
//
//rand函数会返回⼀个伪随机数，这个随机数的范围是在0~RAND_MAX之间，这个RAND_MAX的⼤⼩是
//依赖编译器上实现的，但是⼤部分编译器上是32767.
//rand函数的使⽤需要包含⼀个头⽂件是：stdlib.h
//
//测试：
//#include <stdio.h>
//#include <stdlib.h>
//int main()
//{
//    printf("%d\n", rand());
//    printf("%d\n", rand());
//    printf("%d\n", rand());
//    printf("%d\n", rand());
//    printf("%d\n", rand());
//    return 0;
//}
//
//我们发现到虽然⼀次运⾏中产⽣的5个数字是相对随机的，但是下⼀次运⾏程序⽣成的结果和上⼀次
//⼀模⼀样，原因是rand函数是根据种子数来产生随机数的，种子数是固定的，所以每次运行程序时，rand函数产生的随机数序列都是相同的。
//为了让每次运行程序时产生不同的随机数序列，我们要让种子是变化的。
//
//1.2 srand
//C语⾔中⼜提供了⼀个函数叫srand，⽤来初始化随机数的⽣成器的，srand的原型如下：
//void srand(unsigned int seed);
//
//程序中在调⽤rand函数之前先调⽤srand函数，通过srand函数的参数seed来设置rand函数⽣成随
//机数的时候的种⼦，只要种⼦在变化，每次⽣成的随机数序列也就变化起来了。
//那也就是说给srand的种⼦是如果是随机的，rand就能⽣成随机数；在⽣成随机数的时候⼜需要⼀个随
//机数，这就⽭盾了。
//
//1.3 time
//在程序中我们⼀般是使⽤程序运⾏的时间作为种⼦的，因为时间时刻在发⽣变化的。
//在C语⾔中有⼀个函数叫time，就可以获得这个时间，time函数原型如下：
//time_t time(time_t * timer);
//
//time 函数会返回当前的⽇历时间，其实返回的是1970年1⽉1⽇0时0分0秒到现在程序运⾏时间之间的
//差值，单位是秒。返回的类型是time_t类型的，time_t类型本质上其实就是32位或者64位的整型类
//型。
//time函数的参数timer如果是⾮NULL的指针的话，函数也会将这个返回的差值放在timer指向的内存
//中带回去。
//如果timer是NULL，就只返回这个时间的差值。time函数返回的这个时间差也被叫做：时间戳。
//time函数的时候需要包含头⽂件：time.h
//
//如果只是让time函数返回时间戳，我们就可以这样写：
//time(NULL);//调⽤time函数返回时间戳，这⾥没有接收返回值
//
//1.4 设计随机数的范围
//如果我们要⽣成0~99之间的随机数，⽅法如下：
//rand() % 100;//余数的范围是0~99
//
//如果要⽣成1~100之间的随机数，⽅法如下：
//rand() % 100 + 1;//%100的余数是0~99, 0~99的数字+ 1,范围是1~100
//
//如果要⽣成100~200的随机数，⽅法如下：
//100 + rand() % (200 - 100 + 1)
//    //余数的范围是0~100，加100后就是100~200
//
//所以如果要⽣成a~b的随机数，⽅法如下：
//a + rand() % (b - a + 1)
//    //余数的范围是0~(b-a),加a后就是a~b

//有了这些前置知识，可以试着写一个猜数字游戏


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game()
{
    int r = rand() % 100 + 1;
    int guess = 0;
    int count = 6;
    while (count)
    {
        printf("\n你还有%d次机会\n", count);
        printf("请猜数字>：");
        scanf("%d", &guess);
        if (guess < r)
        {
            printf("猜小了\n");
        }
        else if (guess > r)
        {
            printf("猜大了\n");
        }
        else
        {
            printf("恭喜你，猜对了\n");
            break;
        }
        count--;
    }
    if (count == 0)
    {
        printf("你失败了，正确的是:%d\n", r);
    }
}

void menu()
{   
	printf(" 欢迎来到猜数字游戏\n");
    printf("********************\n");
    printf("****** 1. play ******\n");
    printf("****** 0. exit ******\n");
    printf("********************\n");
}

int main()
{
    int input = 0;
    srand((unsigned int)time(NULL));
    do
    {
        menu();
        printf("请选择:>");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            game();
            break;
        case 0:
            printf("游戏结束\n");
            break;
        default:
            printf("选择错误，重新选择\n");
            break;
        }
    } while (input);

    return 0;
}
