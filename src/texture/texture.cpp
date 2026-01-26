//
// Created by admin on 2026/1/25.
//

#include "texture.h"
#include <algorithm>
#include <cmath>

namespace texture
{

Texture::Texture(std::shared_ptr<image::Image> image) : _image(image) {}

Texture::Texture(const std::string &file_path, int desired_channels)
    : _image(std::make_shared<image::Image>(file_path, desired_channels))
{
}

float Texture::ApplyWrap(float coord) const
{
    switch (_wrap_mode)
    {
    case WrapMode::Clamp:
        return std::clamp(coord, 0.0f, 1.0f);
    case WrapMode::Repeat:
        return coord - std::floor(coord);
    case WrapMode::Mirror:
    {
        float t = coord - std::floor(coord);
        int period = static_cast<int>(std::floor(coord));
        if (period % 2 != 0)
        {
            t = 1.0f - t;
        }
        return t;
    }
    }
    return std::clamp(coord, 0.0f, 1.0f);
}

Color Texture::Sample(float u, float v) const
{
    if (!_image || !_image->IsValid())
    {
        return Color::Transparent();
    }

    u = ApplyWrap(u);
    v = ApplyWrap(v);

    if (_sample_mode == SampleMode::Bilinear)
    {
        return SampleBilinear(u, v);
    }

    // 最近邻采样
    int x = static_cast<int>(u * (_image->Width() - 1) + 0.5f);
    int y = static_cast<int>(v * (_image->Height() - 1) + 0.5f);

    return _image->GetPixel(x, y);
}

Color Texture::SampleBilinear(float u, float v) const
{
    if (!_image || !_image->IsValid())
    {
        return Color::Transparent();
    }

    // 转换为像素坐标（浮点数）
    float px = u * (_image->Width() - 1);
    float py = v * (_image->Height() - 1);

    // 获取四个相邻像素的坐标
    int x0 = static_cast<int>(std::floor(px));
    int y0 = static_cast<int>(std::floor(py));
    // 这里不使用ceil的原因是使用ceil(px), ceil(py)，px, py是整数时导致x0,
    // x0与x1, y0与y1相同，导致插值权重为0(这种的解决方案是需要特殊处理).
    // 直接使用min(x0 + 1, _image->Width() - 1) 和min(y0 + 1, _image->Height() -
    // 1)，可以确保x1, y1不会与x0, y0相同。
    int x1 = std::min(x0 + 1, _image->Width() - 1);
    int y1 = std::min(y0 + 1, _image->Height() - 1);

    // 计算插值权重
    float fx = px - x0;
    float fy = py - y0;

    // 获取四个像素的颜色
    Color c00 = _image->GetPixel(x0, y0);
    Color c10 = _image->GetPixel(x1, y0);
    Color c01 = _image->GetPixel(x0, y1);
    Color c11 = _image->GetPixel(x1, y1);

    // 水平方向插值
    Color c0 = Color::Lerp(c00, c10, fx);
    Color c1 = Color::Lerp(c01, c11, fx);

    // 垂直方向插值
    return Color::Lerp(c0, c1, fy);
}

} // namespace texture
