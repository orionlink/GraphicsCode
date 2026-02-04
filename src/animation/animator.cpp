//
// Created by Claude Code
//
// 动画管理器实现

#include "animation/animator.h"
#include <algorithm>

namespace anim
{

void Animator::Update(int64_t delta_time_us)
{
    // 倒序遍历，安全删除
    for (int i = static_cast<int>(_animations.size()) - 1; i >= 0; --i)
    {
        auto& anim = _animations[i];

        const bool running = anim->Update(delta_time_us);

        // 如果动画已结束且不循环，移除它
        if (!running && !anim->IsLoop())
        {
            _animations.erase(_animations.begin() + i);
        }
    }
}

void Animator::Add(std::shared_ptr<Animation> animation)
{
    if (animation)
    {
        _animations.push_back(std::move(animation));
    }
}

bool Animator::Remove(const Animation* animation)
{
    auto it = std::remove_if(_animations.begin(), _animations.end(),
                             [animation](const auto& anim) { return anim.get() == animation; });

    if (it != _animations.end())
    {
        _animations.erase(it, _animations.end());
        return true;
    }
    return false;
}

void Animator::Clear()
{
    _animations.clear();
}

} // namespace anim