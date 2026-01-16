//
// Created by Claude Code on 2025/12/4.
//

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "../pixels_buffer.h"
#include <memory>

namespace pri
{
/**
 * @brief 图元基类
 */
class IPrimitive
{
public:
    virtual ~IPrimitive() = default;

    /**
     * @brief 绘制图元到指定的像素缓冲区
     * @param buffer 像素缓冲区
     */
    virtual void Draw(PixelsBuffer &buffer) const = 0;

    /**
     * @brief 克隆图元（用于复制）
     * @return 克隆的图元
     */
    virtual std::unique_ptr<IPrimitive> Clone() const = 0;
};

}

#endif // PRIMITIVE_H