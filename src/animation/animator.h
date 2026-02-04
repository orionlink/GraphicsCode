//
// Created by Claude Code
//
// 动画管理器 - 统一管理所有动画的更新

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "animation/animation.h"
#include <memory>
#include <vector>

namespace anim
{

/**
 * @brief 动画管理器
 * 职责：
 *   - 统一管理所有动画对象
 *   - 每帧更新所有正在运行的动画
 *   - 自动清理已完成的非循环动画
 *
 * 设计思路：
 *   - 使用单一 Animator 管理场景中所有动画
 *   - 支持动态添加/移除动画
 *   - 自动处理动画生命周期
 */
class Animator
{
  public:
    Animator() = default;
    ~Animator() = default;

    /**
     * @brief 更新所有动画
     * @param delta_time_us 距离上一帧的时间（微秒）
     *
     * 应在每一帧调用此方法来更新所有动画
     */
    void Update(int64_t delta_time_us);

    /**
     * @brief 添加动画
     * @param animation 动画对象（智能指针）
     */
    void Add(std::shared_ptr<Animation> animation);

    /**
     * @brief 移除动画
     * @param animation 要移除的动画对象
     * @return true 成功移除, false 未找到
     */
    bool Remove(const Animation* animation);

    /**
     * @brief 清空所有动画
     */
    void Clear();

    /**
     * @brief 获取动画数量
     */
    [[nodiscard]] size_t GetCount() const
    {
        return _animations.size();
    }

    /**
     * @brief 检查是否有任何动画在运行
     */
    [[nodiscard]] bool HasAnimations() const
    {
        return !_animations.empty();
    }

  private:
    std::vector<std::shared_ptr<Animation>> _animations;
};

} // namespace anim

#endif // ANIMATOR_H