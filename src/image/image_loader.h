//
// Created by Claude Code on 2026/1/24.
//

#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <string>
#include <vector>
#include <cstdint>

namespace image
{
    class ImageLoader
    {
    public:
        struct ImageData
        {
            std::vector<uint32_t> pixels;
            int width;
            int height;
            int channels;

            ImageData() : width(0), height(0), channels(0) {}

            ImageData(std::vector<uint32_t>&& data, int w, int h, int c)
                : pixels(std::move(data)), width(w), height(h), channels(c) {}

            [[nodiscard]] bool IsValid() const { return !pixels.empty(); }

            uint32_t* Data() { return pixels.data(); }
            [[nodiscard]] std::vector<uint32_t> PixelsData() const { return pixels; }
            [[nodiscard]] size_t Size() const { return pixels.size(); }
        };

        ImageLoader() = delete;

        /**
         * @brief 从文件加载图片
         * @param file_path 图片文件路径
         * @param desired_channels 期望的通道数 (0=自动, 1=灰度, 3=RGB, 4=RGBA)
         * @return ImageData 包含像素数据和图片信息
         * @throws std::runtime_error 如果加载失败
         */
        static ImageData Load(const std::string& file_path, int desired_channels = 4);

        /**
         * @brief 从内存加载图片
         * @param buffer 图片数据缓冲区
         * @param length 缓冲区长度
         * @param desired_channels 期望的通道数 (0=自动, 1=灰度, 3=RGB, 4=RGBA)
         * @return ImageData 包含像素数据和图片信息
         * @throws std::runtime_error 如果加载失败
         */
        static ImageData LoadFromMemory(const uint8_t* buffer, size_t length, int desired_channels = 4);

        /**
         * @brief 设置是否在加载时垂直翻转图片
         * @param flip true 表示翻转，false 表示不翻转
         */
        static void SetFlipVerticallyOnLoad(bool flip);

        /**
         * @brief 获取图片文件信息（不加载像素数据）
         * @param file_path 图片文件路径
         * @param width 输出宽度
         * @param height 输出高度
         * @param channels 输出通道数
         * @return true 如果成功获取信息，false 如果失败
         */
        static bool GetInfo(const std::string& file_path, int& width, int& height, int& channels);
    };
}

#endif // IMAGE_LOADER_H