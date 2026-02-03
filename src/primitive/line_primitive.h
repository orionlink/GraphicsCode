//
// Created by admin on 2026/1/14.
//

#ifndef LINE_PRIMITIVE_H
#define LINE_PRIMITIVE_H

#include "../math/line.h"
#include "point_primitive.h"
#include "primitive.h"
#include <cmath>

namespace pri
{

// 线图元（支持抗锯齿）
class LinePrimitive : public IPrimitive
{
  public:
    LinePrimitive(int x1, int y1, int x2, int y2, const Color& color, bool antialiased = false)
        : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _color(color), _antialiased(antialiased)
    {
    }

    LinePrimitive(PointPrimitive start, PointPrimitive end, bool antialiased = false)
        : _x1(start.X()), _y1(start.Y()), _x2(end.X()), _y2(end.Y()), _color(start.GetColor()),
          _antialiased(antialiased)
    {
    }

    /**
     * @brief 从 math::Line2i 构造
     * @param line 二维整数线段
     * @param color 颜色
     * @param antialiased 是否开启抗锯齿
     */
    LinePrimitive(const math::Line2i& line, const Color& color, bool antialiased = false)
        : _x1(line.Start().X()), _y1(line.Start().Y()), _x2(line.End().X()), _y2(line.End().Y()), _color(color),
          _antialiased(antialiased)
    {
    }

    /**
     * @brief 从 math::Line2f 构造（四舍五入）
     * @param line 二维浮点线段
     * @param color 颜色
     * @param antialiased 是否开启抗锯齿
     */
    LinePrimitive(const math::Line2f& line, const Color& color, bool antialiased = false)
        : _x1(static_cast<int>(std::round(line.Start().X()))), _y1(static_cast<int>(std::round(line.Start().Y()))),
          _x2(static_cast<int>(std::round(line.End().X()))), _y2(static_cast<int>(std::round(line.End().Y()))),
          _color(color), _antialiased(antialiased)
    {
    }

    void Draw(PixelsBuffer& buffer) const override;
    std::unique_ptr<IPrimitive> Clone() const override;

    // 获取属性
    int X1() const
    {
        return _x1;
    }
    int Y1() const
    {
        return _y1;
    }
    int X2() const
    {
        return _x2;
    }
    int Y2() const
    {
        return _y2;
    }
    Color GetColor() const
    {
        return _color;
    }
    bool IsAntialiased() const
    {
        return _antialiased;
    }

    // 设置属性
    void SetStart(int x, int y)
    {
        _x1 = x;
        _y1 = y;
    }

    void SetEnd(int x, int y)
    {
        _x2 = x;
        _y2 = y;
    }

    void SetColor(const Color& color)
    {
        _color = color;
    }

    /**
     * @brief 设置抗锯齿选项
     * @param antialiased true 启用 Wu 氏抗锯齿，false 使用 Bresenham 算法
     */
    void SetAntialiased(bool antialiased)
    {
        _antialiased = antialiased;
    }

    /**
     * @brief 转换为 math::Line2i
     * @return 对应的二维整数线段
     */
    math::Line2i ToLine2i() const
    {
        return math::Line2i(math::Point2i(_x1, _y1), math::Point2i(_x2, _y2));
    }

    /**
     * @brief 转换为 math::Line2f
     * @return 对应的二维浮点线段
     */
    math::Line2f ToLine2f() const
    {
        return math::Line2f(math::Point2f(static_cast<float>(_x1), static_cast<float>(_y1)),
                            math::Point2f(static_cast<float>(_x2), static_cast<float>(_y2)));
    }

  private:
    int _x1;
    int _y1;
    int _x2;
    int _y2;
    Color _color;
    bool _antialiased = false; // 是否启用抗锯齿

    // Bresenham 直线绘制
    void DrawBresenham(PixelsBuffer& buffer) const;

    // Wu 氏抗锯齿直线绘制
    void DrawAntialiased(PixelsBuffer& buffer) const;

    // 辅助函数: 返回小数部分
    static float fpart(float x)
    {
        return x - std::floor(x);
    }

    // 辅助函数: 返回 1 - 小数部分
    static float rfpart(float x)
    {
        return 1.0f - fpart(x);
    }

    // 辅助函数: 混合颜色与背景
    static Color BlendColor(const Color& fg, float alpha, const Color& bg = Color::Black())
    {
        // Alpha混合
        uint8_t r = static_cast<uint8_t>(fg.R() * alpha + bg.R() * (1.0f - alpha));
        uint8_t g = static_cast<uint8_t>(fg.G() * alpha + bg.G() * (1.0f - alpha));
        uint8_t b = static_cast<uint8_t>(fg.B() * alpha + bg.B() * (1.0f - alpha));
        return Color(r, g, b);
    }
};

} // namespace pri

#endif // LINE_PRIMITIVE_H
