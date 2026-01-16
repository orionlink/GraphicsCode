//
// Created by admin on 2026/1/14.
//

#include "antialiased_line_primitive.h"

namespace pri
{

// AntialiasedLinePrimitive 实现 - Wu氏抗锯齿算法
void AntialiasedLinePrimitive::Draw(PixelsBuffer &buffer) const
{
    float x0 = _x1, y0 = _y1;
    float x1 = _x2, y1 = _y2;

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
        buffer.SetPixel(ypxl1 + 1, xpxl1,
                        BlendColor(_color, fpart(yend) * xgap));
    }
    else
    {
        buffer.SetPixel(xpxl1, ypxl1, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(xpxl1, ypxl1 + 1,
                        BlendColor(_color, fpart(yend) * xgap));
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
        buffer.SetPixel(ypxl2 + 1, xpxl2,
                        BlendColor(_color, fpart(yend) * xgap));
    }
    else
    {
        buffer.SetPixel(xpxl2, ypxl2, BlendColor(_color, rfpart(yend) * xgap));
        buffer.SetPixel(xpxl2, ypxl2 + 1,
                        BlendColor(_color, fpart(yend) * xgap));
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

std::unique_ptr<IPrimitive> AntialiasedLinePrimitive::Clone() const
{
    return std::make_unique<AntialiasedLinePrimitive>(*this);
}

} // pri