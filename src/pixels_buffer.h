//
// Created by admin on 2025/12/4.
//

#ifndef PIXELS_BUFFER_H
#define PIXELS_BUFFER_H

#include <cstdint>
#include <vector>
#include "color.h"

class PixelsBuffer
{
public:
    PixelsBuffer(int width, int height);
    ~PixelsBuffer() = default;

    // 获取尺寸信息
    int Width() const { return _width; }
    int Height() const { return _height; }
    int Pitch() const { return _pitch; }

    // 像素数据访问
    uint32_t *Pixels() { return _pixel_data.data(); }
    const uint32_t *Pixels() const { return _pixel_data.data(); }

    // 获取/设置指定位置的像素
    Color GetPixel(int x, int y) const;
    void SetPixel(int x, int y, const Color &color);

    void SetPixelData(const std::vector<uint32_t> &data)
    {
        _pixel_data = data;
    }

    // 清除缓冲区（填充指定颜色）
    void Clear(const Color &color = Color::Transparent());

    // 检查坐标是否在有效范围内
    bool IsValidCoordinate(int x, int y) const;

private:
    int _width;
    int _height;
    int _pitch; // 每行字节数 = _width * 4
    std::vector<uint32_t> _pixel_data; // RGBA8888 格式，每个像素 32 位
};

#endif //PIXELS_BUFFER_H
