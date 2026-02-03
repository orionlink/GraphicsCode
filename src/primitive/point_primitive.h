//
// Created by admin on 2026/1/14.
//

#ifndef POINT_PRIMITIVE_H
#define POINT_PRIMITIVE_H

#include "../math/point.h"
#include "primitive.h"

namespace pri
{

/**
 * @brief 点图元
 */
class PointPrimitive : public IPrimitive
{
  public:
    PointPrimitive(int x, int y, const Color& color = Color::Green()) : _x(x), _y(y), _color(color) {}

    /**
     * @brief 从 math::Point2i 构造
     * @param point 二维整数点
     * @param color 颜色
     */
    PointPrimitive(const math::Point2i& point, const Color& color = Color::Green())
        : _x(point.X()), _y(point.Y()), _color(color)
    {
    }

    /**
     * @brief 从 math::Point2f 构造（四舍五入）
     * @param point 二维浮点 point
     * @param color 颜色
     */
    PointPrimitive(const math::Point2f& point, const Color& color = Color::Green())
        : _x(static_cast<int>(std::round(point.X()))), _y(static_cast<int>(std::round(point.Y()))), _color(color)
    {
    }

    void Draw(PixelsBuffer& buffer) const override;
    std::unique_ptr<IPrimitive> Clone() const override;

    void Swap(PointPrimitive& other)
    {
        std::swap(_x, other._x);
        std::swap(_y, other._y);
    }

    void SwapXY() { std::swap(_x, _y); }

    // 获取属性
    int X() const { return _x; }
    int Y() const { return _y; }
    void SetX(int x) { _x = x; }
    void SetY(int y) { _y = y; }
    Color GetColor() const { return _color; }

    // 设置属性
    void SetPosition(int x, int y)
    {
        _x = x;
        _y = y;
    }

    void SetColor(const Color& color) { _color = color; }

    /**
     * @brief 转换为 math::Point2i
     * @return 对应的二维整数点
     */
    math::Point2i ToPoint2i() const { return math::Point2i(_x, _y); }

    /**
     * @brief 转换为 math::Point2f
     * @return 对应的二维浮点 point
     */
    math::Point2f ToPoint2f() const { return math::Point2f(static_cast<float>(_x), static_cast<float>(_y)); }

  private:
    int _x;
    int _y;
    Color _color;
};

} // namespace pri

#endif // POINT_PRIMITIVE_H
