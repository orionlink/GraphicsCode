//
// Created by admin on 2026/1/14.
//

#ifndef LINE_PRIMITIVE_H
#define LINE_PRIMITIVE_H

#include "primitive.h"
#include "point_primitive.h"
#include "../math/line.h"

namespace pri
{

// 线图元
class LinePrimitive : public IPrimitive
{
public:
    LinePrimitive(int x1, int y1, int x2, int y2, const Color &color)
        : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _color(color)
    {
    }

    LinePrimitive(PointPrimitive start, PointPrimitive end)
        : _x1(start.X()), _y1(start.Y()), _x2(end.X()), _y2(end.Y()),
          _color(start.GetColor())
    {

    }

    /**
     * @brief 从 math::Line2i 构造
     * @param line 二维整数线段
     * @param color 颜色
     */
    LinePrimitive(const math::Line2i &line, const Color &color)
        : _x1(line.Start().X()), _y1(line.Start().Y()), 
          _x2(line.End().X()), _y2(line.End().Y()), _color(color)
    {
    }

    /**
     * @brief 从 math::Line2f 构造（四舍五入）
     * @param line 二维浮点线段
     * @param color 颜色
     */
    LinePrimitive(const math::Line2f &line, const Color &color)
        : _x1(static_cast<int>(std::round(line.Start().X()))), 
          _y1(static_cast<int>(std::round(line.Start().Y()))),
          _x2(static_cast<int>(std::round(line.End().X()))), 
          _y2(static_cast<int>(std::round(line.End().Y()))), 
          _color(color)
    {
    }

    void Draw(PixelsBuffer &buffer) const override;
    std::unique_ptr<IPrimitive> Clone() const override;

    // 获取属性
    int X1() const { return _x1; }
    int Y1() const { return _y1; }
    int X2() const { return _x2; }
    int Y2() const { return _y2; }
    Color GetColor() const { return _color; }

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

    void SetColor(const Color &color) { _color = color; }

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
};

} // pri

#endif //LINE_PRIMITIVE_H
