//
// Created by Claude Code
//
// UV 滚动动画 - 用于实现跑马灯效果

#ifndef UV_SCROLL_ANIMATION_H
#define UV_SCROLL_ANIMATION_H

#include "animation/animation.h"
#include "math/point.h"
#include <functional>

namespace anim
{

/**
 * @brief UV 滚动动画
 *
 * 通过持续偏移 UV 坐标实现纹理滚动效果（跑马灯）
 *
 * 使用场景：
 *   - 跑马灯文字/图片滚动
 *   - 背景纹理滚动
 *   - 流动效果（河流、云层等）
 */
class UVScrollAnimation : public Animation
{
  public:
    /**
     * @brief UV 更新回调
     * 当动画更新时，通过此回调通知外部更新 UV 坐标
     * 参数：当前 UV 偏移量 (u_offset, v_offset)
     */
    using UVCallback = std::function<void(float u_offset, float v_offset)>;

    /**
     * @brief 构造函数
     * @param uv_callback UV 更新回调
     * @param speed_u U 方向滚动速度（每秒滚动的 UV 单位）
     * @param speed_v V 方向滚动速度（每秒滚动的 UV 单位）
     *
     * 示例：
     *   - speed_u = 1.0, speed_v = 0  → 每秒向右滚动整个纹理宽度
     *   - speed_u = -0.5, speed_v = 0 → 每秒向左滚动半个纹理宽度
     *   - speed_u = 0, speed_v = 0.5  → 每秒向下滚动半个纹理高度
     */
    UVScrollAnimation(UVCallback uv_callback, float speed_u = 0.5f, float speed_v = 0.0f);
    ~UVScrollAnimation() override = default;

    /**
     * @brief 设置滚动速度
     * @param speed_u U 方向速度
     * @param speed_v V 方向速度
     */
    void SetScrollSpeed(float speed_u, float speed_v)
    {
        _speed_u = speed_u;
        _speed_v = speed_v;
    }

    /**
     * @brief 获取当前 UV 偏移量
     */
    [[nodiscard]] math::Point2f GetOffset() const
    {
        return {_u_offset, _v_offset};
    }

    /**
     * @brief 更新动画
     * @param delta_time_us 距离上一帧的时间（微秒）
     * @return true 动画仍在运行, false 动画已结束
     */
    bool Update(int64_t delta_time_us) override;

    /**
     * @brief 重置动画到初始状态
     */
    void Reset() override;

  private:
    UVCallback _uv_callback; // UV 更新回调
    float _speed_u;          // U 方向滚动速度
    float _speed_v;          // V 方向滚动速度
    float _u_offset = 0.0f;  // 当前 U 偏移量
    float _v_offset = 0.0f;  // 当前 V 偏移量
};

} // namespace anim

#endif // UV_SCROLL_ANIMATION_H