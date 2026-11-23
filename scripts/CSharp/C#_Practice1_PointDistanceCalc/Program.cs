using System;

class Program
{
    static void Main()
    {
        // 1. 定义两个数组存放点的X、Y坐标（初始定义5个点）
        double[] x = new double[5] { 0, 30, 60, 100, 45 };
        double[] y = new double[5] { 0, 40, 10, -30, 45 };
        double x0, y0;

        // 2. 读入查询点，使用TryParse防止输入非法导致程序崩溃
        while (true)
        {
            Console.Write("请输入查询点 x0 = ");
            string s1 = Console.ReadLine();
            // TryParse成功返回true，并将值赋给x0
            if (double.TryParse(s1, out x0))
            {
                break; // 输入合法，跳出循环
            }
            Console.WriteLine("输入非法，请输入数字！"); // 提示错误并继续循环
        }

        // 同样的方式读取y0
        while (true)
        {
            Console.Write("请输入查询点 y0 = ");
            string s2 = Console.ReadLine();
            if (double.TryParse(s2, out y0))
            {
                break;
            }
            Console.WriteLine("输入非法，请输入数字！");
        }

        // 3. 计算查询点到每个点的欧氏距离
        double[] d = new double[5]; // 用于存放5个距离值
        Console.WriteLine();
        Console.WriteLine("各点距离如下：");

        for (int i = 0; i < 5; i++)
        {
            // 计算坐标差
            double dx = x[i] - x0;
            double dy = y[i] - y0;
            // 计算欧氏距离：根号下(dx的平方 + dy的平方)
            d[i] = Math.Sqrt(dx * dx + dy * dy);

            // 输出格式化，F2代表保留两位小数
            Console.WriteLine("点" + (i + 1) +
                " 坐标(" + x[i] + "," + y[i] + ")" +
                " 距离 = " + d[i].ToString("F2"));
        }

        // 4. 找最近点
        int nearest = 0; // 假设第1个点（索引0）距离最近
        for (int i = 1; i < 5; i++)
        {
            // 如果发现更小的距离，更新最近点索引
            if (d[i] < d[nearest])
            {
                nearest = i;
            }
        }
        Console.WriteLine();
        Console.WriteLine("距离最近的点是：点" + (nearest + 1)); // 序号从1开始，所以索引+1
        Console.WriteLine("最近距离为：" + d[nearest].ToString("F2"));

        // 5. 输出距离小于阈值50的所有点序号
        double threshold = 50.0; // 设定阈值
        Console.WriteLine();
        Console.WriteLine("距离小于50的点有：");

        bool flag = false; // 用于标记是否找到了满足条件的点
        for (int i = 0; i < 5; i++)
        {
            if (d[i] < threshold)
            {
                Console.WriteLine("点" + (i + 1) + ", 距离 = " + d[i].ToString("F2"));
                flag = true; // 找到至少一个点，改变标志位
            }
        }

        // 如果遍历结束后标志位仍为false，说明没有点符合要求
        if (flag == false)
        {
            Console.WriteLine("没有满足条件的点。");
        }

        Console.WriteLine();
        Console.WriteLine("程序结束。");
        Console.ReadKey(); // 阻塞程序，防止控制台闪退
    }
}