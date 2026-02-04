//
// Created by Claude Code
//
// UV 滚动动画实现

#include "animation/uv_scroll_animation.h"
#include <cmath>

namespace anim
{

UVScrollAnimation::UVScrollAnimation(UVCallback uv_callback, float speed_u, float speed_v)
    : _uv_callback(std::move(uv_callback)), _speed_u(speed_u), _speed_v(speed_v), _u_offset(0.0f), _v_offset(0.0f)
{
}

bool UVScrollAnimation::Update(int64_t delta_time_us)
{
    // 计算时间增量（秒）
    float delta_seconds = (delta_time_us / 1000000.0f) * _speed;

    // 更新 UV 偏移量
    _u_offset += _speed_u * delta_seconds;
    _v_offset += _speed_v * delta_seconds;

    // 触发回调，通知外部更新 UV
    if (_uv_callback)
    {
        _uv_callback(_u_offset, _v_offset);
    }

    // 循环动画永不结束（除非手动停止）
    return _loop || !_finished;
}

void UVScrollAnimation::Reset()
{
    _u_offset = 0.0f;
    _v_offset = 0.0f;
    _finished = false;
}

} // namespace anim