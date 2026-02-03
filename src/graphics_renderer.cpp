//
// Created by Claude Code on 2025/12/4.
//

#include "graphics_renderer.h"
#include "color.h"
#include "primitive/line_primitive.h"
#include <cmath>

GraphicsRenderer::GraphicsRenderer(PixelsBuffer& buffer) : _buffer(buffer) {}

void GraphicsRenderer::Clear(const Color& color)
{
    _buffer.Clear(color);
}

void GraphicsRenderer::Draw(const pri::IPrimitive& primitive)
{
    primitive.Draw(_buffer);
}

void GraphicsRenderer::DrawPoint(int x, int y, const Color& color)
{
    pri::PointPrimitive point(x, y, color);
    point.Draw(_buffer);
}

void GraphicsRenderer::DrawPoint(const pri::PointPrimitive& point)
{
    point.Draw(_buffer);
}

void GraphicsRenderer::DrawLine(int x1, int y1, int x2, int y2, const Color& color)
{
    // 使用 LinePrimitive 来绘制直线
    pri::LinePrimitive line(x1, y1, x2, y2, color);
    line.Draw(_buffer);
}

void GraphicsRenderer::DrawLine(const pri::PointPrimitive& start, const pri::PointPrimitive& end)
{
    pri::LinePrimitive line(start, end);
    line.Draw(_buffer);
}

void GraphicsRenderer::DrawAntialiasedLine(int x1, int y1, int x2, int y2, const Color& color)
{
    // 使用 LinePrimitive 并启用抗锯齿来绘制直线
    pri::LinePrimitive line(x1, y1, x2, y2, color, true);
    line.Draw(_buffer);
}

void GraphicsRenderer::DrawAntialiasedLine(const pri::PointPrimitive& start, const pri::PointPrimitive& end)
{
    pri::LinePrimitive line(start, end, true);
    line.Draw(_buffer);
}

void GraphicsRenderer::DrawPoint(const math::Point2i& point, const Color& color)
{
    DrawPoint(point.X(), point.Y(), color);
}

void GraphicsRenderer::DrawPoint(const math::Point2f& point, const Color& color)
{
    DrawPoint(static_cast<int>(std::round(point.X())), static_cast<int>(std::round(point.Y())), color);
}

void GraphicsRenderer::DrawLine(const math::Point2i& start, const math::Point2i& end, const Color& color)
{
    DrawLine(start.X(), start.Y(), end.X(), end.Y(), color);
}

void GraphicsRenderer::DrawLine(const math::Point2f& start, const math::Point2f& end, const Color& color)
{
    DrawLine(static_cast<int>(std::round(start.X())), static_cast<int>(std::round(start.Y())),
             static_cast<int>(std::round(end.X())), static_cast<int>(std::round(end.Y())), color);
}

void GraphicsRenderer::DrawLine(const math::Line2i& line, const Color& color)
{
    DrawLine(line.Start(), line.End(), color);
}

void GraphicsRenderer::DrawLine(const math::Line2f& line, const Color& color)
{
    DrawLine(line.Start(), line.End(), color);
}

void GraphicsRenderer::DrawAntialiasedLine(const math::Point2i& start, const math::Point2i& end, const Color& color)
{
    DrawAntialiasedLine(start.X(), start.Y(), end.X(), end.Y(), color);
}

void GraphicsRenderer::DrawAntialiasedLine(const math::Point2f& start, const math::Point2f& end, const Color& color)
{
    DrawAntialiasedLine(static_cast<int>(std::round(start.X())), static_cast<int>(std::round(start.Y())),
                        static_cast<int>(std::round(end.X())), static_cast<int>(std::round(end.Y())), color);
}

void GraphicsRenderer::DrawAntialiasedLine(const math::Line2i& line, const Color& color)
{
    DrawAntialiasedLine(line.Start(), line.End(), color);
}

void GraphicsRenderer::DrawAntialiasedLine(const math::Line2f& line, const Color& color)
{
    DrawAntialiasedLine(line.Start(), line.End(), color);
}

void GraphicsRenderer::DrawImage(std::shared_ptr<image::Image> image)
{
    if (!image)
        return;
    int offset_y = image->Position().Y();
    int offset_x = image->Position().X();
    int limit_y = image->Height() + offset_y;
    int limit_x = image->Width() + offset_x;

    for (int j = offset_y; j < limit_y; j++)
    {
        for (int i = offset_x; i < limit_x; i++)
        {
            const Color color = image->GetPixel(i - offset_x, j - offset_y);
            _buffer.SetPixel(i, j, color);
        }
    }
}

void GraphicsRenderer::AddPrimitive(std::unique_ptr<pri::IPrimitive> primitive)
{
    _primitives.push_back(std::move(primitive));
}

void GraphicsRenderer::ClearPrimitives()
{
    _primitives.clear();
}

void GraphicsRenderer::DrawAllPrimitives()
{
    for (const auto& primitive : _primitives)
    {
        primitive->Draw(_buffer);
    }
}