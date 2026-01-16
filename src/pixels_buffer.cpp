//
// Created by admin on 2025/12/4.
//

#include "pixels_buffer.h"
#include "color.h"
#include <cassert>
#include <algorithm>

PixelsBuffer::PixelsBuffer(int width, int height)
    : _width(width), _height(height), _pitch(width * 4)
{
    assert(width > 0 && height > 0);
    _pixel_data.
        resize(static_cast<size_t>(width) * static_cast<size_t>(height));
    Clear(); // 默认清除为透明黑色
}

Color PixelsBuffer::GetPixel(int x, int y) const
{
    if (!IsValidCoordinate(x, y))
    {
        return Color(0);
    }
    return Color(_pixel_data[static_cast<size_t>(y) * _width + x]);
}

void PixelsBuffer::SetPixel(int x, int y, const Color &color)
{
    if (!IsValidCoordinate(x, y))
    {
        return;
    }
    _pixel_data[static_cast<size_t>(y) * _width + x] = color.ToUint32();
}

void PixelsBuffer::Clear(const Color &color)
{
    std::fill(_pixel_data.begin(), _pixel_data.end(), color.ToUint32());
}

bool PixelsBuffer::IsValidCoordinate(int x, int y) const
{
    return x >= 0 && x < _width && y >= 0 && y < _height;
}
