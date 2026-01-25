#include "bounding_box.h"
#include "color.h"
#include "image.h"
#include "math/vector.h"
#include "primitive/line_primitive.h"
#include "sdl2_window.h"
#include "triangle_primitive.h"

#include <cstdlib>
#include <iostream>
#include <memory>

using namespace math;
using namespace std;

// 360° = 2π 弧度
// 两边除以 360：
//
// 1° = 2π/360 弧度
//    = π/180 弧度
#define DEG2RAD(deg) ((deg) * M_PI / 180.0)

void TestRenderer(GraphicsRenderer &renderer);
void TestVector();

const int g_width = 800;
const int g_height = 600;

int main(int argc, char *argv[])
{
    (void)argc; // 避免未使用参数警告
    (void)argv;

    Sdl2Window window("OpenGL 学习", g_width, g_height);
    auto &renderer = window.graphicsRenderer();

#if 1 // 1. 红色方块 (左上角) - 应该显示红色
    TestRenderer(renderer);
#endif

#if 0
    TestVector();
#endif
    // 启动事件循环
    window.EventLoop();

    return 0;
}

void TestVector()
{
    std::cout << "向量加法测试" << std::endl;
    Vector2<int> v1(1, 2);
    Vector2<int> v2(3, 4);
    Vector2<int> v3 = v1 + v2;
    std::cout << "v3 = " << v3.PrintToString() << std::endl;

    Vector3<int> v4(1, 2, 3);
    Vector3<int> v5(4, 5, 6);
    Vector3<int> v6 = v4 + v5;
    std::cout << "v6 = " << v6.PrintToString() << std::endl;

    Vector4<int> v7(1, 2, 3, 4);
    Vector4<int> v8(5, 6, 7, 8);
    Vector4<int> v9 = v7 + v8;
    std::cout << "v9 = " << v9.PrintToString() << std::endl;

    std::cout << "向量减法测试" << std::endl;
    Vector2<int> v13 = v1 - v2;
    std::cout << "v13 = " << v13.PrintToString() << std::endl;

    Vector3<int> v14 = v4 - v5;
    std::cout << "v14 = " << v14.PrintToString() << std::endl;

    Vector4<int> v15 = v7 - v8;
    std::cout << "v15 = " << v15.PrintToString() << std::endl;

    std::cout << "向量逐元素乘法测试" << std::endl;
    Vector2<int> v16 = v1 * v2;
    std::cout << "v16 = " << v16.PrintToString() << std::endl;

    Vector3<int> v17 = v4 * v5;
    std::cout << "v17 = " << v17.PrintToString() << std::endl;

    Vector4<int> v18 = v7 * v8;
    std::cout << "v18 = " << v18.PrintToString() << std::endl;

    std::cout << "向量除与标量测试" << std::endl;
    Vector2<int> v19 = v1 / 2;
    std::cout << "v19 = " << v19.PrintToString() << std::endl;

    Vector3<int> v20 = v4 / 2;
    std::cout << "v20 = " << v20.PrintToString() << std::endl;

    Vector4<int> v21 = v7 / 2;
    std::cout << "v21 = " << v21.PrintToString() << std::endl;

    std::cout << "向量点积测试" << std::endl;
    auto v22 = v1.Dot(v2);
    std::cout << "v22 = " << v22 << std::endl;

    auto v23 = v4.Dot(v5);
    std::cout << "v23 = " << v23 << std::endl;

    auto v24 = v7.Dot(v8);
    std::cout << "v24 = " << v24 << std::endl;

    std::cout << "向量叉积测试" << std::endl;
    auto v25 = v4.Cross(v5);
    std::cout << "v25 = " << v25.PrintToString() << std::endl;

    std::cout << "向量长度测试" << std::endl;

    std::cout << "向量归一化测试" << std::endl;
    Vector2<int> v31 = v1.Normalized();
    std::cout << "v31 = " << v31.PrintToString() << std::endl;

    Vector3<int> v32 = v4.Normalized();
    std::cout << "v32 = " << v32.PrintToString() << std::endl;

    Vector4<int> v33 = v7.Normalized();
    std::cout << "v33 = " << v33.PrintToString() << std::endl;
}

void BresenhamLine(const pri::PointPrimitive point1,
                   const pri::PointPrimitive point2, GraphicsRenderer &renderer)
{
    pri::PointPrimitive start_point = point1;
    pri::PointPrimitive end_point = point2;
    // 1、保证x是从小到大的顺序
    if (start_point.X() > end_point.X())
    {
        start_point.Swap(end_point);
    }

    // 2、保证y是从小到大的顺序
    bool flip_y = false;
    if (start_point.Y() > end_point.Y())
    {
        start_point.SetY(start_point.Y() * -1);
        end_point.SetY(end_point.Y() * -1);
        flip_y = true;
    }

    int dx = end_point.X() - start_point.X();
    int dy = end_point.Y() - start_point.Y();
    // 斜率大于1，交换xy
    bool swapxy = false;
    if (dx < dy)
    {
        start_point.SwapXY();
        end_point.SwapXY();
        std::swap(dx, dy);
        swapxy = true;
    }

    pri::PointPrimitive current_point = start_point;
    pri::PointPrimitive result_point{0, 0};
    int p = 2 * dy - dx;
    for (int i = 0; i < dx; ++i)
    {
        if (p >= 0)
        {
            p = p - 2 * dx;
            current_point.SetY(current_point.Y() + 1);
        }
        p = p + 2 * dy;
        current_point.SetX(current_point.X() + 1);

        result_point = current_point;
        if (swapxy)
        {
            result_point.SwapXY();
        }

        if (flip_y)
        {
            result_point.SetY(result_point.Y() * -1);
        }

        float t = 0.0f;
        if (point1.X() != point2.X())
        {
            t = static_cast<float>((result_point.X() - point1.X())) /
                (static_cast<float>(point2.X() - point1.X()));
        }
        else if (point1.Y() != point2.Y())
        {
            t = static_cast<float>((result_point.Y() - point1.Y())) /
                (static_cast<float>(point2.Y() - point1.Y()));
        }

        Color color = Color::Lerp(point1.GetColor(), point2.GetColor(), t);
        result_point.SetColor(color);

        renderer.DrawPoint(result_point);
    }
}

void TestRenderer(GraphicsRenderer &renderer)
{
#if 0
    // 简单直线算法
    double x1 = 150, y1 = 150;
    double x2 = 640, y2 = 320;
 double k = (y2 - y1) / (x2 - x1);
    double b = y1 - k * x1;

    double x{x1};
    while (x < x2)
    {
        double y = (k * x) + b;
        renderer.DrawPoint(x, y);
        x++;
    }
#endif

#if 0
    // 迭代模型直线算法
    double x1 = 150, y1 = 150;
    double x2 = 640, y2 = 320;

    // 斜率大于1的时候，不管如何增大斜率，实际画出来的直线斜率一直都是1
    double x1 = 0, y1 = 50;
    double x2 = 100, y2 = 400;

    int new_x = x1;
    int new_y = y1;
    int p = 2 * (y2 - y1) - (x2 - x1);
    while (new_x < x2)
    {
        renderer.DrawPoint(new_x, new_y);
        new_x++;
        if (p >= 0)
        {
            p = p - (2 * (x2 - x1));
            new_y++;
        }
        p = p + (2 * (y2 - y1));
    }

    // 斜率大于1互换xy
    std::swap(x1, y1);
    std::swap(x2, y2);
    new_x = x1;
    new_y = y1;
    p = 2 * (y2 - y1) - (x2 - x1);
    while (new_x < x2)
    {
        renderer.DrawPoint(new_y, new_x, Color::Green());
        new_x++;
        if (p >= 0)
        {
            p = p - (2 * (x2 - x1));
            new_y++;
        }
        p = p + (2 * (y2 - y1));
    }
#endif

    // Bresenham 直线算法

    // x1 < x2 y1 < y2, k > 1 (红色到黄色)
    pri::PointPrimitive start_point{10, 100, Color::Red()};
    pri::PointPrimitive end_point{100, 500, Color::Yellow()};
    BresenhamLine(start_point, end_point, renderer);
    // x1 < x2 y1 > y2, k > 1 (青色到洋红)
    start_point = {10, 500, Color::Cyan()};
    end_point = {100, 100, Color::Magenta()};
    BresenhamLine(start_point, end_point, renderer);

    // x1 > x2, y1 > y2, k > 1 (粉色到紫色)
    start_point = {100, 400, Color::Pink()};
    end_point = {50, 100, Color::Purple()};
    BresenhamLine(start_point, end_point, renderer);

    start_point = {400, 100, Color::Green()};
    end_point = {90, 420};
    pri::LinePrimitive line{start_point, end_point};
    renderer.Draw(line);

    pri::PointPrimitive c{g_width / 2, g_height / 2, Color::Red()};
    int r = 150;
    // sin 和 cos 就是一张“角度→比例”的对照表。
    // 你给一个角度，它告诉你竖边和横边各占斜边的多少比例。
    // 只要角度 θ 相同，不管三角形多大，这个比例永远不变！
    for (float i = 0; i < 360; i += 10) // 从 0° 到 360°，每隔 10°
    {
        float radian = DEG2RAD(i);       // 转成弧度
        int x = r * cos(radian) + c.X(); // 圆上的 x 坐标
        int y = r * sin(radian) + c.Y(); // 圆上的 y 坐标
        pri::PointPrimitive pt{x, y,
                               Color{static_cast<unsigned char>(rand() % 255),
                                     static_cast<unsigned char>(rand() % 255),
                                     static_cast<unsigned char>(rand() % 255),
                                     255}};
        // renderer.DrawLine(c, pt); // 从圆心画线到圆周
        BresenhamLine(c, pt, renderer);
        // renderer.DrawAntialiasedLine(c, pt);
    }

    // Wu氏抗锯齿直线演示 - 在右侧绘制对比
    // 左侧: Bresenham (锯齿)
    renderer.DrawLine(150, 50, 250, 150, Color::Red());
    renderer.DrawLine(150, 170, 250, 270, Color::Green());
    renderer.DrawLine(150, 290, 250, 390, Color::Blue());

    // 右侧: Wu氏抗锯齿 (平滑)
    renderer.DrawAntialiasedLine(550, 50, 650, 150, Color::Red());
    renderer.DrawAntialiasedLine(550, 170, 650, 270, Color::Green());
    renderer.DrawAntialiasedLine(550, 290, 650, 390, Color::Blue());

    math::Point2i p1{150, 200};
    math::Point2i p2{350, 200};
    math::Point2i p3{250, 350};
    pri::PointPrimitive pp1{p1, Color::Red()};
    pri::PointPrimitive pp2{p2, Color::Green()};
    pri::PointPrimitive pp3{p3, Color::Blue()};
    // pri::TrianglePrimitive triangle{p1, p2, p3}; // 纯颜色
    pri::TrianglePrimitive triangle{pp1, pp2, pp3}; // 颜色插值
    auto image = std::make_shared<image::Image>("/Users/admin/Downloads/beautiful-landscape-around-lake-kawaguchiko小.jpeg");
    image->Move(math::Point2i(450, 350));
    renderer.Draw(triangle);

    renderer.DrawImage(image);
}