//
// Created by admin on 2026/1/25.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include "color.h"
#include "image/image.h"

namespace texture {

/**
 * @brief 纹理采样模式
 */
enum class SampleMode {
    Nearest,    // 最近邻采样
    Bilinear    // 双线性插值
};

/**
 * @brief 纹理环绕模式
 */
enum class WrapMode {
    Clamp,      // 钳制到边缘
    Repeat,     // 重复平铺
    Mirror      // 镜像重复
};

/**
 * @brief 纹理类 - 用于渲染的纹理对象
 * 职责：
 *   1. 持有图像数据（Image）
 *   2. 提供纹理采样功能（UV坐标 -> 颜色）
 *   3. 管理采样模式和环绕模式
 * 
 * 设计思路：
 *   - Image 负责存储原始像素数据（数据层）
 *   - Texture 负责采样和过滤（渲染层）
 *   - 多个 Texture 可以共享同一个 Image（内存优化）
 */
class Texture {
public:
    /**
     * @brief 从 Image 创建纹理
     * @param image 图像对象（共享指针，允许多个 Texture 共享）
     */
    explicit Texture(std::shared_ptr<image::Image> image);

    /**
     * @brief 从文件加载纹理（便捷方法）
     * @param file_path 图片文件路径
     * @param desired_channels 期望的通道数 (0=自动, 1=灰度, 3=RGB, 4=RGBA)
     */
    explicit Texture(const std::string& file_path, int desired_channels = 4);

    /**
     * @brief 根据 UV 坐标采样颜色
     * @param u U 坐标 (0.0 ~ 1.0)
     * @param v V 坐标 (0.0 ~ 1.0)
     * @return 采样得到的颜色
     */
    [[nodiscard]] Color Sample(float u, float v) const;

    /**
     * @brief 设置采样模式
     * @param mode 采样模式
     */
    void SetSampleMode(SampleMode mode) { _sample_mode = mode; }

    /**
     * @brief 获取采样模式
     */
    [[nodiscard]] SampleMode GetSampleMode() const { return _sample_mode; }

    /**
     * @brief 设置环绕模式
     * @param mode 环绕模式
     */
    void SetWrapMode(WrapMode mode) { _wrap_mode = mode; }

    /**
     * @brief 获取环绕模式
     */
    [[nodiscard]] WrapMode GetWrapMode() const { return _wrap_mode; }

    /**
     * @brief 获取底层图像对象
     */
    [[nodiscard]] std::shared_ptr<image::Image> GetImage() const { return _image; }

    /**
     * @brief 获取纹理宽度
     */
    [[nodiscard]] int Width() const { return _image ? _image->Width() : 0; }

    /**
     * @brief 获取纹理高度
     */
    [[nodiscard]] int Height() const { return _image ? _image->Height() : 0; }

    /**
     * @brief 检查纹理是否有效
     */
    [[nodiscard]] bool IsValid() const { return _image && _image->IsValid(); }

private:
    std::shared_ptr<image::Image> _image;  // 持有图像数据（可共享）
    SampleMode _sample_mode = SampleMode::Nearest;
    WrapMode _wrap_mode = WrapMode::Clamp;

    /**
     * @brief 应用环绕模式处理坐标
     */
    [[nodiscard]] float ApplyWrap(float coord) const;

    /**
     * @brief 双线性插值采样
     */
    [[nodiscard]] Color SampleBilinear(float u, float v) const;
};

} // namespace texture

#endif // TEXTURE_H
