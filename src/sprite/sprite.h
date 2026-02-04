//
// Created by Claude Code
//
// Sprite 精灵类 - 渲染纹理矩形

#ifndef SPRITE_H
#define SPRITE_H

#include "animation/animation.h"
#include "animation/uv_scroll_animation.h"
#include "graphics_renderer.h"
#include "image/image.h"
#include "math/point.h"
#include "primitive/triangle_primitive.h"
#include "texture/texture.h"
#include <memory>

namespace sprite
{

/**
 * @brief 精灵类
 *
 * 职责：
 *   - 管理一个纹理矩形（由两个三角形组成）
 *   - 支持 UV 坐标动态更新（用于纹理滚动）
 *   - 支持位置、尺寸设置
 *   - 可绑定动画实现动态效果
 *
 * 使用示例：
 *   auto sprite = std::make_shared<Sprite>(renderer, texture);
 *   sprite->SetPosition(100, 100);
 *   sprite->SetSize(200, 200);
 *   sprite->Draw(); // 每帧调用
 */
class Sprite
{
  public:
    /**
     * @brief 构造函数
     * @param renderer 图形渲染器引用
     * @param texture 纹理对象
     */
    Sprite(GraphicsRenderer& renderer, std::shared_ptr<texture::Texture> texture);
    ~Sprite() = default;

    /**
     * @brief 设置位置（左上角坐标）
     */
    void SetPosition(int x, int y)
    {
        _x = x;
        _y = y;
    }

    /**
     * @brief 设置尺寸
     */
    void SetSize(int width, int height)
    {
        _width = width;
        _height = height;
    }

    /**
     * @brief 设置 UV 偏移量（用于纹理滚动）
     * @param u_offset U 方向偏移 [0, 1]
     * @param v_offset V 方向偏移 [0, 1]
     */
    void SetUVOffset(float u_offset, float v_offset)
    {
        _uv_offset = math::Point2f(u_offset, v_offset);
    }

    /**
     * @brief 设置纹理
     */
    void SetTexture(std::shared_ptr<texture::Texture> texture)
    {
        _texture = std::move(texture);
    }

    /**
     * @brief 获取位置
     */
    [[nodiscard]] math::Point2i GetPosition() const
    {
        return math::Point2i(_x, _y);
    }

    /**
     * @brief 获取尺寸
     */
    [[nodiscard]] math::Point2i GetSize() const
    {
        return math::Point2i(_width, _height);
    }

    /**
     * @brief 获取当前 UV 偏移量
     */
    [[nodiscard]] math::Point2f GetUVOffset() const
    {
        return _uv_offset;
    }

    /**
     * @brief 获取纹理
     */
    [[nodiscard]] std::shared_ptr<texture::Texture> GetTexture() const
    {
        return _texture;
    }

    /**
     * @brief 设置矩形区域（位置 + 尺寸）
     */
    void SetRect(int x, int y, int width, int height);

    /**
     * @brief 创建 UV 滚动动画（跑马灯效果）
     * @param speed_u U 方向滚动速度（每秒滚动的 UV 单位）
     * @param speed_v V 方向滚动速度
     * @return 动画对象，可添加到 Animator 中
     *
     * 示例：
     *   auto anim = sprite->CreateUVScrollAnimation(0.5f, 0.0f); // 向右滚动
     *   animator.Add(anim);
     */
    [[nodiscard]] std::shared_ptr<anim::Animation> CreateUVScrollAnimation(float speed_u = 0.5f, float speed_v = 0.0f);

    /**
     * @brief 绘制精灵
     * 每帧调用此方法将精灵绘制到渲染器
     */
    void Draw() const;

  private:
    GraphicsRenderer& _renderer;
    std::shared_ptr<texture::Texture> _texture;

    int _x = 0;                           // X 位置
    int _y = 0;                           // Y 位置
    int _width = 100;                     // 宽度
    int _height = 100;                    // 高度
    math::Point2f _uv_offset{0.0f, 0.0f}; // UV 偏移量
};

} // namespace sprite

#endif // SPRITE_H