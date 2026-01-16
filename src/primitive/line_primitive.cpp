//
// Created by admin on 2026/1/14.
//

#include "line_primitive.h"
#include <cmath>

namespace pri
{

// LinePrimitive 实现
void LinePrimitive::Draw(PixelsBuffer &buffer) const
{
    // Bresenham 直线算法
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
        if (e2 > -dy) // err > -dy/2
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

std::unique_ptr<IPrimitive> LinePrimitive::Clone() const
{
    return std::make_unique<LinePrimitive>(*this);
}

} // pri