//
// Created by admin on 2026/1/24.
//

#include "image_primitive.h"
#include "image/image_loader.h"

namespace pri
{
ImagePrimitive::ImagePrimitive(const std::string &file_path, int desired_channels)
    :_x(0), _y(0)
{
    image::ImageLoader::ImageData image_data = image::ImageLoader::Load(file_path, desired_channels);
    _width = image_data.width;
    _height = image_data.height;
    _channels = image_data.channels;
    _pixels = image_data.PixelsData();
}

void ImagePrimitive::Move(int x, int y)
{
    _x = x;
    _y = y;
}

void ImagePrimitive::Draw(PixelsBuffer &buffer) const
{
    for (int j = _y; j < _y + _height; ++j)
    {
        for (int i = _x; i < _x + _width; ++i)
        {
            int index = ((j - _y) * _width) + (i - _x);
            if (index < 0 || index >= _pixels.size()) {
                break;
            }
            buffer.SetPixel(i, j, Color(_pixels[index]));
        }
    }
}

std::unique_ptr<IPrimitive> ImagePrimitive::Clone() const
{
    return std::make_unique<ImagePrimitive>(*this);
}
} // pri