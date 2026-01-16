//
// Created by admin on 2026/1/14.
//

#include "point_primitive.h"
#include <cmath>

namespace pri
{

// PointPrimitive 实现
void PointPrimitive::Draw(PixelsBuffer &buffer) const
{
    buffer.SetPixel(_x, _y, _color);
}

std::unique_ptr<IPrimitive> PointPrimitive::Clone() const
{
    return std::make_unique<PointPrimitive>(*this);
}

}
