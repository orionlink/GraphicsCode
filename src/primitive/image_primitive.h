//
// Created by admin on 2026/1/24.
//

#ifndef IMAGEPRIMITIVE_H
#define IMAGEPRIMITIVE_H

#include "primitive.h"
#include <string>
#include <vector>

namespace pri {

class ImagePrimitive : public IPrimitive
{
public:
    /**
     * @brief 从文件加载图片
     * @param file_path 图片文件路径
     * @param desired_channels 期望的通道数 (0=自动, 1=灰度, 3=RGB, 4=RGBA)
     */
    ImagePrimitive(const std::string& file_path, int desired_channels = 4);

    void Move(int x, int y);

    /**
     * @brief 绘制图元到指定的像素缓冲区
     * @param buffer 像素缓冲区
     */
    virtual void Draw(PixelsBuffer &buffer) const;

    /**
     * @brief 克隆图元（用于复制）
     * @return 克隆的图元
     */
    virtual std::unique_ptr<IPrimitive> Clone() const;
private:
    std::vector<uint32_t> _pixels;
    int _width;
    int _height;
    int _channels;
    int _x, _y;
};

} // pri

#endif //IMAGEPRIMITIVE_H
