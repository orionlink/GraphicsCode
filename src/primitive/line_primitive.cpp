//
// Created by admin on 2026/1/14.
//

#include "line_primitive.h"
#include <cmath>

namespace pri
{

// LinePrimitive 实现
void LinePrimitive::Draw(PixelsBuffer& buffer) const
{
    if (_antialiased)
    {
        DrawAntialiased(buffer);
    }
    else
    {
        DrawBresenham(buffer);
    }
}

// Bresenham 直线算法
void LinePrimitive::DrawBresenham(PixelsBuffer& buffer) const
{
    int dx = std::abs(_x2 - _x1);
    int dy = std::abs(_y2 - _y1);
    int sx = (_x1 < _x2) ? 1 : -1;
    int sy = (_y1 < _y2) ? 1 : -1;
    int err = dx - dy; // x方向的路程比 y 多多少

    int x = _x1;
    int y = _y1;

    //     err 小                    err 大
    //   ←                         →
    // ├───────────────────┼───────────────────┤
    // -dy                  0                  dx
    // "欠 x 方向"                      "欠 y 方向"

    //     ←─────────────────────────────→
    // -dy        -dy/2   0   dx/2        dx
    // ├───────────┼─────┼─────┼───────────┤
    // │   只走y   │  两者都走   │   只走x    │

    while (true)
    {
        buffer.SetPixel(x, y, _color);
        if (x == _x2 && y == _y2)
            break;
        int e2 = 2 * err; // 避免除2产生浮点数, 等价于 err > -dy / 2, err < dx / 2
        if (e2 > -dy)     // err > -dy/2
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) // err < dx/2
        {
            err += dx;
            y += sy;
        }
    }
}

// Wu 氏抗锯齿直线算法
void LinePrimitive::DrawAntialiased(PixelsBuffer& buffer) const
{
    float x0 = static_cast<float>(_x1);
    float y0 = static_cast<float>(_y1);
    float x1 = static_cast<float>(_x2);
    float y1 = static_cast<float>(_y2);

    // 判断是否需要交换xy (斜率是否 > 1)
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    // 保证从左到右绘制
    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = (dx == 0) ? 1.0f : dy / dx; // 斜率

    // 处理起点
    float xend = std::round(x0);
    float yend = y0 + gradient * (xend - x0);
    float xgap = rfpart(x0 + 0.5f);
    int xpxl1 = static_cast<int>(xend);
    int ypxl1 = static_cast<int>(yend);

    if (steep)
    {
        buffer.SetPixel(ypxl1, xpxl1, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(ypxl1 + 1, xpxl1, BlendColor(_color, fpart(yend) * xgap));
    }
    else
    {
        buffer.SetPixel(xpxl1, ypxl1, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(xpxl1, ypxl1 + 1, BlendColor(_color, fpart(yend) * xgap));
    }

    float intery = yend + gradient; // 第一个y交点

    // 处理终点
    xend = std::round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5f);
    int xpxl2 = static_cast<int>(xend);
    int ypxl2 = static_cast<int>(yend);

    if (steep)
    {
        buffer.SetPixel(ypxl2, xpxl2, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(ypxl2 + 1, xpxl2, BlendColor(_color, fpart(yend) * xgap));
    }
    else
    {
        buffer.SetPixel(xpxl2, ypxl2, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(xpxl2, ypxl2 + 1, BlendColor(_color, fpart(yend) * xgap));
    }

    // 主循环: 绘制中间的所有点
    if (steep)
    {
        for (int x = xpxl1 + 1; x < xpxl2; x++)
        {
            int y = static_cast<int>(intery);
            // 绘制两个相邻像素，透明度根据距离
            buffer.SetPixel(y, x, BlendColor(_color, rfpart(intery)));
            buffer.SetPixel(y + 1, x, BlendColor(_color, fpart(intery)));
            intery += gradient;
        }
    }
    else
    {
        for (int x = xpxl1 + 1; x < xpxl2; x++)
        {
            int y = static_cast<int>(intery);
            // 绘制两个相邻像素，透明度根据距离
            buffer.SetPixel(x, y, BlendColor(_color, rfpart(intery)));
            buffer.SetPixel(x, y + 1, BlendColor(_color, fpart(intery)));
            intery += gradient;
        }
    }
}

std::unique_ptr<IPrimitive> LinePrimitive::Clone() const { return std::make_unique<LinePrimitive>(*this); }

} // namespace pri