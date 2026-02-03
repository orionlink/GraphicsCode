//
// Created by admin on 2026/1/25.
//

#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include "point.h"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace image
{

/**
 * @brief 图像类 - 纯粹的图像数据容器
 * 职责：
 *   1. 存储像素数据
 *   2. 提供像素访问接口
 *   3. 从文件/内存加载图像
 */
class Image
{
  public:
    /**
     * @brief 从文件加载图像
     * @param file_path 图片文件路径
     * @param desired_channels 期望的通道数 (0=自动, 1=灰度, 3=RGB, 4=RGBA)
     */
    explicit Image(const std::string& file_path, int desired_channels = 4);

    /**
     * @brief 从像素数据创建图像
     * @param pixels 像素数据
     * @param width 宽度
     * @param height 高度
     * @param channels 通道数
     */
    Image(std::vector<uint32_t>&& pixels, int width, int height, int channels = 4);

    /**
     * @brief 创建空白图像
     * @param width 宽度
     * @param height 高度
     * @param channels 通道数
     * @param fill_color 填充颜色
     */
    Image(int width, int height, int channels = 4, Color fill_color = Color::Transparent());

    /**
     * @brief 将图片移动到屏幕的某个位置
     *
     * @param position 位置
     */
    void Move(const math::Point2i& position) { _start_position = position; }

    /**
     * @brief 将图片移动到屏幕的某个位置
     *
     * @param x 横坐标
     * @param y 纵坐标
     */
    void Move(const int x, const int y) { _start_position = math::Point2i(x, y); }

    math::Point2i Position() const { return _start_position; }

    /**
     * @brief 获取指定位置的像素颜色
     * @param x X 坐标
     * @param y Y 坐标
     * @return 像素颜色
     */
    [[nodiscard]] Color GetPixel(int x, int y) const;

    /**
     * @brief 设置指定位置的像素颜色
     * @param x X 坐标
     * @param y Y 坐标
     * @param color 颜色
     */
    void SetPixel(int x, int y, const Color& color);

    /**
     * @brief 获取图像宽度
     */
    [[nodiscard]] int Width() const { return _width; }

    /**
     * @brief 获取图像高度
     */
    [[nodiscard]] int Height() const { return _height; }

    /**
     * @brief 获取通道数
     */
    [[nodiscard]] int Channels() const { return _channels; }

    /**
     * @brief 检查图像是否有效
     */
    [[nodiscard]] bool IsValid() const { return !_pixels.empty(); }

    /**
     * @brief 获取原始像素数据（只读）
     */
    [[nodiscard]] const std::vector<uint32_t>& Pixels() const { return _pixels; }

    /**
     * @brief 获取原始像素数据（可修改）
     */
    [[nodiscard]] std::vector<uint32_t>& Pixels() { return _pixels; }

  private:
    std::vector<uint32_t> _pixels;
    int _width;
    int _height;
    int _channels;
    /** 对应图片左上角在屏幕坐标的开始位置 */
    math::Point2i _start_position{0, 0};
};

} // namespace image

#endif // IMAGE_H
