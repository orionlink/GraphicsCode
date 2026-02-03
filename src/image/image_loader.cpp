//
// Created by Claude Code on 2026/1/24.
//

#define STB_IMAGE_IMPLEMENTATION
#include <stdexcept>

#include "image_loader.h"
#include "stb_image.h"

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define IMAGE_LITTLE_ENDIAN 1
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define IMAGE_LITTLE_ENDIAN 0
#elif defined(__LITTLE_ENDIAN__) || defined(_WIN32)
#define IMAGE_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__)
#define IMAGE_LITTLE_ENDIAN 0
#else
#error "Cannot determine endianness"
#endif

namespace image
{
ImageLoader::ImageData ImageLoader::Load(const std::string& file_path, int desired_channels)
{
    int width, height, channels;
    unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &channels, desired_channels);

    if (!data)
    {
        throw std::runtime_error("Failed to load image: " + file_path + " - " + stbi_failure_reason());
    }

    int actual_channels = desired_channels != 0 ? desired_channels : channels;
    size_t pixel_count = static_cast<size_t>(width) * height;
    std::vector<uint32_t> pixels(pixel_count);

    for (size_t i = 0; i < pixel_count; ++i)
    {
        uint8_t r = 0, g = 0, b = 0, a = 255;
        size_t byte_offset = i * actual_channels;

        if (actual_channels >= 1)
            r = data[byte_offset];
        if (actual_channels >= 2)
            g = data[byte_offset + 1];
        if (actual_channels >= 3)
            b = data[byte_offset + 2];
        if (actual_channels >= 4)
            a = data[byte_offset + 3];

        // 打包为 SDL_PIXELFORMAT_RGBA8888 格式（与 Color 类一致）
#if IMAGE_LITTLE_ENDIAN
        // 小端：R在最高字节，A在最低字节
        pixels[i] = (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) |
                    (static_cast<uint32_t>(b) << 8) | static_cast<uint32_t>(a);
#else
        // 大端：A在最高字节，R在最低字节
        pixels[i] = (static_cast<uint32_t>(a) << 24) | (static_cast<uint32_t>(b) << 16) |
                    (static_cast<uint32_t>(g) << 8) | static_cast<uint32_t>(r);
#endif
    }
    stbi_image_free(data);

    return ImageData(std::move(pixels), width, height, actual_channels);
}

ImageLoader::ImageData ImageLoader::LoadFromMemory(const uint8_t* buffer, size_t length, int desired_channels)
{
    int width, height, channels;
    unsigned char* data =
        stbi_load_from_memory(buffer, static_cast<int>(length), &width, &height, &channels, desired_channels);

    if (!data)
    {
        throw std::runtime_error(std::string("Failed to load image from memory: ") + stbi_failure_reason());
    }

    int actual_channels = desired_channels != 0 ? desired_channels : channels;
    size_t pixel_count = static_cast<size_t>(width) * height;
    std::vector<uint32_t> pixels(pixel_count);

    for (size_t i = 0; i < pixel_count; ++i)
    {
        uint8_t r = 0, g = 0, b = 0, a = 255;
        size_t byte_offset = i * actual_channels;

        if (actual_channels >= 1)
            r = data[byte_offset];
        if (actual_channels >= 2)
            g = data[byte_offset + 1];
        if (actual_channels >= 3)
            b = data[byte_offset + 2];
        if (actual_channels >= 4)
            a = data[byte_offset + 3];

        pixels[i] = (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) |
                    (static_cast<uint32_t>(b) << 8) | static_cast<uint32_t>(a);
    }
    stbi_image_free(data);

    return ImageData(std::move(pixels), width, height, actual_channels);
}

void ImageLoader::SetFlipVerticallyOnLoad(bool flip) { stbi_set_flip_vertically_on_load(flip ? 1 : 0); }

bool ImageLoader::GetInfo(const std::string& file_path, int& width, int& height, int& channels)
{
    return stbi_info(file_path.c_str(), &width, &height, &channels) != 0;
}
} // namespace image