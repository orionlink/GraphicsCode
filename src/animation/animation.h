//
// Created by Claude Code
//
// 动画基类 - 定义动画接口

#ifndef ANIMATION_H
#define ANIMATION_H

#include <cstdint>

namespace anim
{

/**
 * @brief 动画基类
 * 职责：
 *   - 定义动画生命周期接口
 *   - 提供动画状态查询
 *   - 支持动画循环、速度控制
 */
class Animation
{
  public:
    Animation() = default;
    virtual ~Animation() = default;

    /**
     * @brief 更新动画状态
     * @param delta_time_us 距离上一帧的时间（微秒）
     * @return true 动画仍在运行, false 动画已结束
     */
    virtual bool Update(int64_t delta_time_us) = 0;

    /**
     * @brief 重置动画到初始状态
     */
    virtual void Reset() = 0;

    /**
     * @brief 设置动画是否循环
     */
    void SetLoop(bool loop)
    {
        _loop = loop;
    }

    /**
     * @brief 获取动画是否循环
     */
    [[nodiscard]] bool IsLoop() const
    {
        return _loop;
    }

    /**
     * @brief 检查动画是否已完成
     */
    [[nodiscard]] bool IsFinished() const
    {
        return _finished;
    }

    /**
     * @brief 设置动画速度倍率 (1.0 = 正常速度)
     */
    void SetSpeed(float speed)
    {
        _speed = speed;
    }

    /**
     * @brief 获取动画速度倍率
     */
    [[nodiscard]] float GetSpeed() const
    {
        return _speed;
    }

  protected:
    bool _loop = true;      // 是否循环播放
    bool _finished = false; // 是否已完成
    float _speed = 1.0f;    // 播放速度倍率
};

} // namespace anim

#endif // ANIMATION_H