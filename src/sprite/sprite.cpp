//
// Created by Claude Code
//
// Sprite 精灵类实现

#include "sprite/sprite.h"

namespace sprite
{

Sprite::Sprite(GraphicsRenderer& renderer, std::shared_ptr<texture::Texture> texture)
    : _renderer(renderer), _texture(std::move(texture))
{
}

void Sprite::SetRect(int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}

std::shared_ptr<anim::Animation> Sprite::CreateUVScrollAnimation(float speed_u, float speed_v)
{
    auto animation = std::make_shared<anim::UVScrollAnimation>([this](float u, float v) { this->SetUVOffset(u, v); },
                                                               speed_u, speed_v);
    return animation;
}

void Sprite::Draw() const
{
    // 矩形的四个顶点
    // p0 --- p1
    // |      |
    // p2 --- p3

    int x0 = _x;
    int y0 = _y;
    int x1 = _x + _width;
    int y1 = _y;
    int x2 = _x;
    int y2 = _y + _height;
    int x3 = _x + _width;
    int y3 = _y + _height;

    // UV 坐标（加上偏移量实现滚动）
    float u0 = _uv_offset.X();
    float v0 = _uv_offset.Y();
    float u1 = _uv_offset.X() + 1.0f;
    float v1 = _uv_offset.Y() + 1.0f;

    // 三角形 1: p0 -> p1 -> p2 (左上三角形)
    pri::TrianglePrimitive triangle1({x0, y0}, {x1, y1}, {x2, y2}, _texture, math::Point2f(u0, v0),
                                     math::Point2f(u1, v0), math::Point2f(u0, v1));

    // 三角形 2: p1 -> p3 -> p2 (右下三角形)
    pri::TrianglePrimitive triangle2({x1, y1}, {x3, y3}, {x2, y2}, _texture, math::Point2f(u1, v0),
                                     math::Point2f(u1, v1), math::Point2f(u0, v1));

    _renderer.Draw(triangle1);
    _renderer.Draw(triangle2);
}

} // namespace sprite