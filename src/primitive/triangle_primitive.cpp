//
// Created by admin on 2026/1/15.
//

#include "triangle_primitive.h"
#include "bounding_box.h"
#include "math/vector.h"

namespace pri
{

void TrianglePrimitive::Draw(PixelsBuffer& buffer) const
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

            bool inside = (cross0 >= 0 && cross1 >= 0 && cross2 >= 0) || (cross0 <= 0 && cross1 <= 0 && cross2 <= 0);
            if (inside)
            {
                // 计算重心坐标
                BarycentricCoord barycentric = ComputeBarycentricCoord(i, j);

                Color color;
                if (_texture)
                {
                    // 使用纹理：插值 UV 坐标，然后采样纹理
                    math::Point2f uv = InterpolateUV(barycentric);
                    color = _texture->Sample(uv.X(), uv.Y());
                }
                else
                {
                    // 不使用纹理：插值顶点颜色
                    if ((_p0.GetColor() == _p1.GetColor()) && (_p0.GetColor() == _p2.GetColor()))
                    {
                        // 优化：纯色三角形
                        color = _p0.GetColor();
                    }
                    else
                    {
                        // 插值颜色
                        color = InterpolateColor(barycentric);
                    }
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

BarycentricCoord TrianglePrimitive::ComputeBarycentricCoord(int x, int y) const
{
    // 计算三角形的面积（使用两条边的叉积）
    math::Vector2f edge1(static_cast<float>(_p0.X() - _p1.X()), static_cast<float>(_p0.Y() - _p1.Y()));
    math::Vector2f edge2(static_cast<float>(_p0.X() - _p2.X()), static_cast<float>(_p0.Y() - _p2.Y()));
    float sum_area = std::abs(edge1.Cross(edge2));

    if (sum_area <= 0.0f)
    {
        // 退化三角形
        return BarycentricCoord(3);
    }

    // 计算点 P 到各顶点形成的三角形面积
    math::Vector2f pv0(static_cast<float>(x - _p0.X()), static_cast<float>(y - _p0.Y()));
    math::Vector2f pv1(static_cast<float>(x - _p1.X()), static_cast<float>(y - _p1.Y()));
    math::Vector2f pv2(static_cast<float>(x - _p2.X()), static_cast<float>(y - _p2.Y()));

    // 子三角形面积
    float area0 = std::abs(pv1.Cross(pv2)); // P-P1-P2 的面积，对应顶点0的权重
    float area1 = std::abs(pv0.Cross(pv2)); // P-P0-P2 的面积，对应顶点1的权重
    float area2 = std::abs(pv0.Cross(pv1)); // P-P0-P1 的面积，对应顶点2的权重

    // 归一化得到重心坐标
    BarycentricCoord result(3);
    result[0] = area0 / sum_area; // alpha (顶点0的权重)
    result[1] = area1 / sum_area; // beta (顶点1的权重)
    result[2] = area2 / sum_area; // gamma (顶点2的权重)

    return result;
}

Color TrianglePrimitive::InterpolateColor(const BarycentricCoord& barycentric) const
{
    if (barycentric.Size() != 3)
    {
        return Color::Transparent();
    }

    // 使用重心坐标插值 RGB 分量
    uint8_t r = static_cast<uint8_t>(barycentric[0] * _p0.GetColor().R() + barycentric[1] * _p1.GetColor().R() +
                                     barycentric[2] * _p2.GetColor().R());
    uint8_t g = static_cast<uint8_t>(barycentric[0] * _p0.GetColor().G() + barycentric[1] * _p1.GetColor().G() +
                                     barycentric[2] * _p2.GetColor().G());
    uint8_t b = static_cast<uint8_t>(barycentric[0] * _p0.GetColor().B() + barycentric[1] * _p1.GetColor().B() +
                                     barycentric[2] * _p2.GetColor().B());

    return Color(r, g, b);
}

math::Point2f TrianglePrimitive::InterpolateUV(const BarycentricCoord& barycentric) const
{
    if (barycentric.Size() != 3)
    {
        return math::Point2f(0, 0);
    }

    // 使用重心坐标插值 UV 坐标
    float u = barycentric[0] * _uv0.X() + barycentric[1] * _uv1.X() + barycentric[2] * _uv2.X();

    float v = barycentric[0] * _uv0.Y() + barycentric[1] * _uv1.Y() + barycentric[2] * _uv2.Y();

    return math::Point2f(u, v);
}

} // namespace pri
