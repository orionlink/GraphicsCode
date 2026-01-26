//
// Created by admin on 2026/1/25.
//

#include "image.h"
#include "image_loader.h"
#include <algorithm>

namespace image {

Image::Image(const std::string& file_path, int desired_channels)
    : _width(0), _height(0), _channels(0)
{
    try {
        ImageLoader::ImageData image_data = ImageLoader::Load(file_path, desired_channels);
        _width = image_data.width;
        _height = image_data.height;
        _channels = image_data.channels;
        _pixels = std::move(image_data.pixels);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

Image::Image(std::vector<uint32_t>&& pixels, int width, int height, int channels)
    : _pixels(std::move(pixels)), _width(width), _height(height), _channels(channels)
{
}

Image::Image(int width, int height, int channels, Color fill_color)
    : _width(width), _height(height), _channels(channels)
{
    _pixels.resize(width * height, fill_color.ToUint32());
}

Color Image::GetPixel(int x, int y) const
{
    if (_pixels.empty()) {
        return Color::Transparent();
    }

    x = std::clamp(x, 0, _width - 1);
    y = std::clamp(y, 0, _height - 1);
    
    int index = y * _width + x;
    if (index < 0 || index >= static_cast<int>(_pixels.size())) {
        return Color::Transparent();
    }
    
    return Color(_pixels[index]);
}

void Image::SetPixel(int x, int y, const Color& color)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }
    
    int index = y * _width + x;
    if (index >= 0 && index < static_cast<int>(_pixels.size())) {
        _pixels[index] = color.ToUint32();
    }
}

} // namespace image
