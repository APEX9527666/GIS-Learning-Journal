// C语言基础综合练习
// 完成时间：2026-9-2~2026-9-3
// 练习内容：根据所学模拟了一个简单的购物小票计算器
// 
// =====================================================
// 程序名称：购物小票计算器（C语言基础综合练习）
// 功能说明：
//   1. 输入商品单价（浮点数）和数量（整数）
//   2. 计算总价（单价 × 数量）
//   3. 打印格式化的购物小票
//   4. 额外演示自增/自减、强制类型转换、sizeof、布尔类型等
// 涉及知识点：
//   - 基本数据类型（int, float, double, char, _Bool）
//   - 变量定义与初始化
//   - 算术操作符（+, -, *, /, %）
//   - 赋值与复合赋值（=, +=, -=）
//   - 单目操作符（++、--、+、-）
//   - 强制类型转换
//   - printf 和 scanf 的使用（占位符、宽度、小数位数）
//   - 转义字符（\n, \t, \a 等）
// =====================================================
//
#define _CRT_SECURE_NO_WARNINGS // 禁用 Visual Studio 的安全警告
#include <stdio.h>   // 包含 printf 和 scanf 的头文件
#include <stdbool.h> // 包含布尔类型（C99）的头文件，使用 bool, true, false

int main()           // 主函数，程序入口
{
    // ========== 1. 声明并初始化变量 ==========
    // 商品信息（使用浮点型表示金额）
    float price = 0.0f;      // 单价（单位：元），使用 float 类型
    // 在C语言中，只要写了一个带小数点的数字，编译器默认都会把它当作 double 类型（通常占8个字节）
    // 定义变量时写的是 float（通常占4个字节），如果直接用 double 类型的 0.0 去初始化它，
    // 相当于要把一个8字节的"大容器"倒进一个4字节的"小容器"里，会丢失精度
    // 所以在定义 float 类型变量时，最好在数字后面加上 f ，告诉编译器这是一个 float 类型的字面量

    int quantity = 0;        // 数量（整数），使用 int 类型
    float total = 0.0f;      // 总价（浮点数）

    // 注意：char 类型只能存1个字节的英文字符，存不了中文"￥"，故直接删掉该变量，
    // 将后面的 printf 中直接写入 "￥" 文本（方案一），完美解决编译错误。

    // 布尔类型（C99 引入，需要 #include <stdbool.h>）
    bool isValid = true;     // 标记输入是否有效（待后续 if 语句学习后使用）

    // 整型变量（演示 signed / unsigned 以及不同长度）
    int score = 85;           // 有符号整型
    unsigned int count = 10;  // 无符号整型（只能表示非负）
    short smallNum = 100;     // 短整型
    long bigNum = 100000L;    // 长整型

    // ========== 2. 打印欢迎信息（使用转义字符） ==========
    printf("==========欢迎使用购物小票计算器==========\n");
    printf("提示：输入单价和数量，程序将自动计算总价。\n\n");

    // ========== 3. 获取用户输入（使用 scanf） ==========
    printf("请输入商品单价（元）：");
    scanf("%f", &price);

    printf("请输入商品数量：");
    scanf("%d", &quantity);


    // ========== 4. 计算总价 ==========
    total = price * quantity;  // 使用乘法操作符 *

    // ========== 5. 输出购物小票（格式化输出） ==========
    // 使用 \t 制表符对齐，\n 换行；直接将 ￥ 写在双引号字符串中，避免 char 存不下的问题
    printf("\n------------------ 购物小票 ------------------\n");
    printf("商品单价：\t￥ %.2f 元\n", price);   // 直接写 ￥，不用变量
    printf("商品数量：\t%d\n", quantity);
    printf("应付总额：\t￥ %.2f 元\n", total);   // 直接写 ￥，不用变量
    printf("----------------------------------------------\n\n");

    // ========== 6. 额外演示：自增/自减操作符 ==========
    printf("========== 自增/自减演示 ==========\n");
    int a = 10;
    int b = 0;

    // 前置 ++：先自增，再使用
    b = ++a;   // a 先变为 11，然后赋值给 b
    printf("前置++：a = %d, b = %d\n", a, b);  // 输出 a=11, b=11

    // 后置 ++：先使用，再自增
    a = 10;
    b = a++;   // 先将 a 的值（10）赋给 b，然后 a 自增为 11
    printf("后置++：a = %d, b = %d\n", a, b);  // 输出 a=11, b=10

    // 前置 -- 与后置 -- 同理
    a = 10;
    b = --a;   // a 先变为 9，再赋值给 b
    printf("前置--：a = %d, b = %d\n", a, b);  // 输出 a=9, b=9

    a = 10;
    b = a--;   // 先将 a 的值（10）赋给 b，然后 a 自减为 9
    printf("后置--：a = %d, b = %d\n", a, b);  // 输出 a=9, b=10

    // ========== 7. 演示强制类型转换 ==========
    printf("\n========== 强制类型转换演示 ==========\n");
    double pi = 3.1415926;
    int intPi = (int)pi;   // 强制将 double 转为 int，只取整数部分
    printf("pi = %f，强制转换为 int 后：%d\n", pi, intPi);

    // ========== 8. 演示 sizeof 操作符 ==========
    printf("\n========== 数据类型长度（sizeof） ==========\n");
    printf("char 占 %zu 字节\n", sizeof(char));
    printf("short 占 %zu 字节\n", sizeof(short));
    printf("int 占 %zu 字节\n", sizeof(int));
    printf("long 占 %zu 字节\n", sizeof(long));
    printf("long long 占 %zu 字节\n", sizeof(long long));
    printf("float 占 %zu 字节\n", sizeof(float));
    printf("double 占 %zu 字节\n", sizeof(double));
    printf("long double 占 %zu 字节\n", sizeof(long double));
    printf("bool 占 %zu 字节\n", sizeof(bool));
    printf("变量 price 占 %zu 字节\n", sizeof(price));   // 可以计算变量

    // ========== 9. 演示字符与 ASCII ==========
    printf("\n========== 字符与 ASCII 演示 ==========\n");
    char ch = 'A';
    printf("字符 '%c' 的 ASCII 码值为 %d\n", ch, ch);     // %c 输出字符，%d 输出整数值
    ch = 65;   // 直接给 ASCII 值
    printf("ASCII 码 65 对应的字符是 '%c'\n", ch);

    // 输出所有可打印字符（从 32 到 126）
    printf("\n可打印 ASCII 字符（32~126）：\n");
    for (int i = 32; i <= 126; i++) {
        printf("%c ", i);
        if (i % 16 == 15)   // 每 16 个换行
            printf("\n");
    }
    printf("\n");

    // ========== 10. 字符串与 \0 结束标志 ==========
    printf("\n========== 字符串与 \\0 结束标志 ==========\n");
    char arr1[] = { 'H', 'e', 'l', 'l', 'o' };        // 没有 \0 结束符
    char arr2[] = "Hello";                          // 字符串常量，自动包含 \0
    printf("arr1（无 \\0）：%s\n", arr1);           // 可能打印乱码，因为找不到结束符
    printf("arr2（有 \\0）：%s\n", arr2);           // 正常打印 Hello

    // 正确做法：手动加 \0
    char arr3[] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    printf("arr3（手动加 \\0）：%s\n", arr3);

    // ========== 11. 复合赋值操作符 ==========
    printf("\n========== 复合赋值演示 ==========\n");
    int num = 20;
    printf("num 初始值：%d\n", num);
    num += 5;   // 等价于 num = num + 5
    printf("num += 5 后：%d\n", num);
    num -= 3;   // 等价于 num = num - 3
    printf("num -= 3 后：%d\n", num);
    num *= 2;   // 等价于 num = num * 2
    printf("num *= 2 后：%d\n", num);
    num /= 4;   // 等价于 num = num / 4（整数除法）
    printf("num /= 4 后：%d\n", num);
    num %= 3;   // 等价于 num = num % 3（取余）
    printf("num %%= 3 后：%d\n", num);

    // ========== 12. 退出程序 ==========
    printf("\n程序运行结束，按任意键退出...\n");
    return 0;   // 返回 0 表示程序正常结束
}