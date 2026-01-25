//
// Created by Claude Code on 2025/12/4.
//

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../pixels_buffer.h"
#include "texture/texture.h"
#include <memory>
#include <vector>

namespace pri
{

/**
 * @brief 重心坐标（Barycentric Coordinate）
 * 用于表示点在凸多边形内部的权重系数
 * 支持三角形、四边形等任意凸多边形
 */
struct BarycentricCoord
{
    std::vector<float> weights;  // 各顶点的权重

    BarycentricCoord() = default;
    
    explicit BarycentricCoord(size_t vertex_count) 
        : weights(vertex_count, 0.0f) {}
    
    BarycentricCoord(std::initializer_list<float> init) 
        : weights(init) {}

    /**
     * @brief 检查重心坐标是否有效（权重之和应该约等于1）
     */
    [[nodiscard]] bool IsValid() const 
    {
        float sum = 0.0f;
        for (float w : weights) {
            sum += w;
        }
        return sum > 0.99f && sum < 1.01f;
    }

    /**
     * @brief 获取顶点数量
     */
    [[nodiscard]] size_t Size() const { return weights.size(); }

    /**
     * @brief 访问指定索引的权重
     */
    float& operator[](size_t index) { return weights[index]; }
    const float& operator[](size_t index) const { return weights[index]; }
};

/**
 * @brief 图元基类
 */
class IPrimitive
{
  public:
    virtual ~IPrimitive() = default;

    /**
     * @brief 绘制图元到指定的像素缓冲区
     * @param buffer 像素缓冲区
     */
    virtual void Draw(PixelsBuffer &buffer) const = 0;

    /**
     * @brief 克隆图元（用于复制）
     * @return 克隆的图元
     */
    virtual std::unique_ptr<IPrimitive> Clone() const = 0;

    /**
     * @brief 设置纹理（基类提供默认实现）
     * @param texture 纹理对象
     */
    virtual void SetTexture(std::shared_ptr<texture::Texture> texture)
    {
        _texture = texture;
    }

    /**
     * @brief 获取纹理
     */
    [[nodiscard]] std::shared_ptr<texture::Texture> GetTexture() const 
    {
        return _texture;
    }

  protected:
    std::shared_ptr<texture::Texture> _texture;  // 纹理（所有图元共享）
};

} // namespace pri

#endif // PRIMITIVE_H