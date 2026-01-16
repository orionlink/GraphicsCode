//
// Created by admin on 2026/1/15.
//

#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

#include "primitive.h"
#include "point.h"

namespace pri
{

/**
 * @brief
 */
class TrianglePrimitive : public IPrimitive
{
public:
    TrianglePrimitive() = default;

    TrianglePrimitive(int x1, int y1, int x2, int y2, int x3, int y3,
                      const Color &color)
        : _x1(x1), _y1(y1), _x2(x2), _y2(y2), _x3(x3), _y3(y3), _color(color)
    {
    }

    TrianglePrimitive(const math::Point2i &p1, const math::Point2i &p2,
                      const math::Point2i &p3,
                      const Color &color)
        : _x1(p1.X()), _y1(p1.Y()), _x2(p2.X()), _y2(p2.Y()), _x3(p3.X()),
          _y3(p3.Y()), _color(color)
    {
    }

    /**
     * @brief 绘制图元到指定的像素缓冲区
     * @param buffer 像素缓冲区
     */
    virtual void Draw(PixelsBuffer &buffer) const;

    /**
     * @brief 克隆图元（用于复制）
     * @return 克隆的图元
     */
    virtual std::unique_ptr<IPrimitive> Clone() const;

private:
    int _x1, _y1, _x2, _y2, _x3, _y3;
    Color _color;
};

} // pri

#endif //TRIANGLE_PRIMITIVE_H
