//
// Created by admin on 2026/1/15.
//

#include "triangle_primitive.h"
#include "bounding_box.h"
#include "math/vector.h"

namespace pri
{

void TrianglePrimitive::Draw(PixelsBuffer &buffer) const
{
    // 计算包围盒子
    math::BoundingBox2i bbox;
    bbox.AddPoint(math::Point2i(_p0.X(), _p0.Y()));
    bbox.AddPoint(math::Point2i(_p1.X(), _p1.Y()));
    bbox.AddPoint(math::Point2i(_p2.X(), _p2.Y()));

    math::Vector2<int> pv0;
    math::Vector2<int> pv1;
    math::Vector2<int> pv2;
    for (int i = bbox.MinX(); i <= bbox.MaxX(); ++i)
    {
        for (int j = bbox.MinY(); j <= bbox.MaxY(); ++j)
        {
            pv0 = math::Vector2(_p0.X() - i, _p0.Y() - j);
            pv1 = math::Vector2(_p1.X() - i, _p1.Y() - j);
            pv2 = math::Vector2(_p2.X() - i, _p2.Y() - j);

            auto cross0 = pv0.Cross(pv1);
            auto cross1 = pv1.Cross(pv2);
            auto cross2 = pv2.Cross(pv0);

            bool inside = (cross0 >= 0 && cross1 >= 0 && cross2 >= 0) ||
                          (cross0 <= 0 && cross1 <= 0 && cross2 <= 0);
            if (inside)
            {
                Color color;
                if ((_p0.GetColor() == _p1.GetColor()) && (_p0.GetColor() == _p2.GetColor()))
                {
                    color = _p0.GetColor();
                }
                else
                {
                    color = InterpolateColor(i, j);
                }
                buffer.SetPixel(i, j, color);
            }
        }
    }
}

std::unique_ptr<IPrimitive> TrianglePrimitive::Clone() const
{
    return std::make_unique<TrianglePrimitive>(*this);
}

Color TrianglePrimitive::InterpolateColor(const int x, const int y) const
{
    math::Vector2f triangle_edge1 =
        math::Vector2(static_cast<float>(_p0.X() - _p1.X()),
                      static_cast<float>(_p0.Y() - _p1.Y()));
    math::Vector2f triangle_edge2 =
        math::Vector2(static_cast<float>(_p0.X() - _p2.X()),
                      static_cast<float>(_p0.Y() - _p2.Y()));
    float sum_area = std::abs(triangle_edge1.Cross(triangle_edge2));
    if (sum_area <= 0.0f)
    {
        return Color(0, 0, 0, 0);
    }

    math::Vector2f pv0 = math::Vector2(static_cast<float>(x - _p0.X()),
                                       static_cast<float>(y - _p0.Y()));
    math::Vector2f pv1 = math::Vector2(static_cast<float>(x - _p1.X()),
                                       static_cast<float>(y - _p1.Y()));
    math::Vector2f pv2 = math::Vector2(static_cast<float>(x - _p2.X()),
                                       static_cast<float>(y - _p2.Y()));
    float area1 = std::abs(pv1.Cross(pv2));
    float area2 = std::abs(pv0.Cross(pv2));
    float area3 = std::abs(pv0.Cross(pv1));

    float alpha{0}, beta{0}, gamma{0};
    alpha = area1 / sum_area;
    beta = area2 / sum_area;
    gamma = area3 / sum_area;

    uint8_t r = alpha * _p0.GetColor().R() + beta * _p1.GetColor().R() +
                gamma * _p2.GetColor().R();
    uint8_t g = alpha * _p0.GetColor().G() + beta * _p1.GetColor().G() +
                gamma * _p2.GetColor().G();
    uint8_t b = alpha * _p0.GetColor().B() + beta * _p1.GetColor().B() +
                gamma * _p2.GetColor().B();
    return Color(r, g, b);
}
} // namespace pri