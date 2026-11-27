using System;

namespace GIS_ShapeArea
{
    // 1. 抽象基类 Shape
    public abstract class Shape
    {
        // 属性：图形名称
        public string Name { get; set; }

        // 抽象方法：计算面积（没有方法体，强制子类实现）
        public abstract double Area();

        // 虚方法：显示信息（子类可以根据需要重写）
        public virtual void Show()
        {
            Console.WriteLine($"图形：{Name}，面积：{Area():F2}");
        }
    }

    // 2. 子类 Circle（圆）
    public class Circle : Shape
    {
        public double R { get; set; } // 半径

        // 构造函数
        public Circle(double r)
        {
            R = r;
            Name = "圆形";
        }

        // 重写面积方法
        public override double Area()
        {
            return Math.PI * R * R;
        }

        // 重写显示方法
        public override void Show()
        {
            Console.WriteLine($"圆：半径{R}，面积{Area():F2}");
        }
    }

    // 3. 子类 Rectangle（矩形）
    public class Rectangle : Shape
    {
        public double W { get; set; } // 宽
        public double H { get; set; } // 高

        public Rectangle(double w, double h)
        {
            W = w;
            H = h;
            Name = "矩形";
        }

        public override double Area()
        {
            return W * H;
        }

        public override void Show()
        {
            Console.WriteLine($"矩形：宽{W}，高{H}，面积{Area():F2}");
        }
    }

    // 4. 子类 Triangle（三角形）
    public class Triangle : Shape
    {
        public double A { get; set; } // 底
        public double H { get; set; } // 高

        public Triangle(double a, double h)
        {
            A = a;
            H = h;
            Name = "三角形";
        }

        public override double Area()
        {
            return 0.5 * A * H;
        }

        public override void Show()
        {
            Console.WriteLine($"三角形：底{A}，高{H}，面积{Area():F2}");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            // 5. 创建一个Shape数组，放入2个圆、2个矩形、1个三角形
            Shape[] shapes = new Shape[5];
            shapes[0] = new Circle(5.0);       // 圆1
            shapes[1] = new Circle(3.0);       // 圆2
            shapes[2] = new Rectangle(4.0, 6.0); // 矩形1
            shapes[3] = new Rectangle(10.0, 2.0);// 矩形2
            shapes[4] = new Triangle(6.0, 8.0);  // 三角形1

            double totalArea = 0;     // 总面积
            Shape maxShape = shapes[0]; // 假设第一个图形面积最大

            Console.WriteLine("=== 图形要素信息列表 ===");

            // 6. 遍历数组，调用Show()，计算总面积
            // 7. 找出面积最大的图形
            foreach (Shape s in shapes)
            {
                // 这里体现了多态：调用的是具体子类重写后的Show()
                s.Show();

                // 累加面积
                totalArea += s.Area();

                // 比较面积，寻找最大图形
                if (s.Area() > maxShape.Area())
                {
                    maxShape = s;
                }
            }

            // 输出统计结果
            Console.WriteLine("\n=== 统计结果 ===");
            Console.WriteLine($"所有图形总面积：{totalArea:F2}");
            Console.WriteLine($"面积最大的图形：{maxShape.Name}，具体面积：{maxShape.Area():F2}");

            Console.WriteLine("\n程序结束。按任意键退出...");
            Console.ReadKey();
        }
    }
}