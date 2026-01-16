//
// Created by admin on 2026/1/15.
//

#include "triangle_primitive.h"
#include "bounding_box.h"

namespace pri
{

void TrianglePrimitive::Draw(PixelsBuffer &buffer) const
{
    // 计算包围盒子
    math::BoundingBox2i bbox;
    bbox.AddPoint(math::Point2i(_x1, _y1));
    bbox.AddPoint(math::Point2i(_x2, _y2));
    bbox.AddPoint(math::Point2i(_x3, _y3));

    math::Vector2<int> pv0;
    math::Vector2<int> pv1;
    math::Vector2<int> pv2;
    for (int i = bbox.MinX(); i <= bbox.MaxX(); ++i)
    {
        for (int j = bbox.MinY(); j <= bbox.MaxY(); ++j)
        {
            pv0 = math::Vector2(_x1 - i, _y1 - j);
            pv1 = math::Vector2(_x2 - i, _y2 - j);
            pv2 = math::Vector2(_x3 - i, _y3 - j);

            auto cross0 = pv0.Cross(pv1);
            auto cross1 = pv1.Cross(pv2);
            auto cross2 = pv2.Cross(pv0);

            bool inside = (cross0 >= 0 && cross1 >= 0 && cross2 >= 0) ||
                          (cross0 <= 0 && cross1 <= 0 && cross2 <= 0);
            if (inside)
            {
                buffer.SetPixel(i, j, _color);
            }
        }
    }

}

std::unique_ptr<IPrimitive> TrianglePrimitive::Clone() const
{
    return std::make_unique<TrianglePrimitive>(*this);
}

} // pri