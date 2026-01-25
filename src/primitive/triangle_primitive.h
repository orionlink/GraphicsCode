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
     * @brief 带纹理的三角形构造函数
     */
    TrianglePrimitive(const PointPrimitive &p1, const PointPrimitive &p2, const PointPrimitive &p3,
                      std::shared_ptr<texture::Texture> texture,
                      const math::Point2f &uv0, const math::Point2f &uv1, const math::Point2f &uv2)
        : _p0(p1), _p1(p2), _p2(p3)
        , _uv0(uv0), _uv1(uv1), _uv2(uv2)
    {
        _texture = texture;
    }

    /**
     * @brief 绘制图元到指定的像素缓冲区
     * @param buffer 像素缓冲区
     */
    virtual void Draw(PixelsBuffer &buffer) const override;

    /**
     * @brief 克隆图元（用于复制）
     * @return 克隆的图元
     */
    virtual std::unique_ptr<IPrimitive> Clone() const override;

    /**
     * @brief 设置纹理和 UV 坐标（重写基类方法，支持 UV）
     */
    void SetTexture(std::shared_ptr<texture::Texture> texture,
                    const math::Point2f &uv0, const math::Point2f &uv1, const math::Point2f &uv2)
    {
        IPrimitive::SetTexture(texture);
        _uv0 = uv0;
        _uv1 = uv1;
        _uv2 = uv2;
    }

    /**
     * @brief 设置 UV 坐标
     */
    void SetUV(const math::Point2f &uv0, const math::Point2f &uv1, const math::Point2f &uv2)
    {
        _uv0 = uv0;
        _uv1 = uv1;
        _uv2 = uv2;
    }

private:
    /**
     * @brief 计算点 (x, y) 相对于三角形的重心坐标
     * @param x X 坐标
     * @param y Y 坐标
     * @return 重心坐标（3个权重）
     */
    [[nodiscard]] BarycentricCoord ComputeBarycentricCoord(int x, int y) const;

    /**
     * @brief 使用重心坐标插值颜色
     * @param barycentric 重心坐标
     * @return 插值后的颜色
     */
    [[nodiscard]] Color InterpolateColor(const BarycentricCoord &barycentric) const;

    /**
     * @brief 使用重心坐标插值 UV 坐标
     * @param barycentric 重心坐标
     * @return 插值后的 UV 坐标
     */
    [[nodiscard]] math::Point2f InterpolateUV(const BarycentricCoord &barycentric) const;

private:
    PointPrimitive _p0, _p1, _p2;
    
    math::Point2f _uv0{0, 0};  // 顶点 0 的 UV 坐标
    math::Point2f _uv1{0, 0};  // 顶点 1 的 UV 坐标
    math::Point2f _uv2{0, 0};  // 顶点 2 的 UV 坐标
};

} // pri

#endif //TRIANGLE_PRIMITIVE_H
