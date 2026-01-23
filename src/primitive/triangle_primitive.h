//
// Created by admin on 2026/1/15.
//

#ifndef TRIANGLE_PRIMITIVE_H
#define TRIANGLE_PRIMITIVE_H

#include "color.h"
#include "primitive.h"
#include "point.h"
#include "point_primitive.h"

namespace pri
{

/**
 * @brief 三角形图元(填充)
 */
class TrianglePrimitive : public IPrimitive
{
public:
    TrianglePrimitive() = default;

    TrianglePrimitive(int x1, int y1, int x2, int y2, int x3, int y3,
                      const Color &color)   
        : _p0(x1, y1, color), _p1(x2, y2, color), _p2(x3, y3, color)
    {
    }

    TrianglePrimitive(const math::Point2i &p1, const math::Point2i &p2,
                      const math::Point2i &p3,
                      const Color &color)
        : _p0(p1, color), _p1(p2, color), _p2(p3, color)
    {
    }

    TrianglePrimitive(const PointPrimitive &p1, const PointPrimitive &p2, const PointPrimitive &p3)
        : _p0(p1), _p1(p2), _p2(p3)
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
    /**
     *
     * @param x
     * @param y
     * @return
     */
    Color InterpolateColor(const int x, const int y) const;

private:
    PointPrimitive _p0, _p1, _p2;
};

} // pri

#endif //TRIANGLE_PRIMITIVE_H
