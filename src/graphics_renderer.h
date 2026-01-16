//
// Created by Claude Code on 2025/12/4.
//

#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "pixels_buffer.h"
#include "primitive/primitive.h"
#include "primitive/point_primitive.h"
#include "math/point.h"
#include "math/line.h"
#include "color.h"
#include <vector>
#include <memory>

class GraphicsRenderer
{
public:
    // 构造函数，接受像素缓冲区引用
    explicit GraphicsRenderer(PixelsBuffer &buffer);

    // 清空缓冲区（填充指定颜色）
    void Clear(const Color &color = Color::Black());

    void Draw(const pri::IPrimitive &primitive);

    // 直接绘制函数（立即绘制到缓冲区）
    void DrawPoint(int x, int y, const Color &color = Color::Red());
    void DrawPoint(const pri::PointPrimitive &point);
    void DrawPoint(const math::Point2i &point, const Color &color = Color::Red());
    void DrawPoint(const math::Point2f &point, const Color &color = Color::Red());
    
    void DrawLine(int x1, int y1, int x2, int y2, const Color &color);
    void DrawLine(const pri::PointPrimitive &start,
                  const pri::PointPrimitive &end);
    void DrawLine(const math::Point2i &start, const math::Point2i &end, const Color &color);
    void DrawLine(const math::Point2f &start, const math::Point2f &end, const Color &color);
    void DrawLine(const math::Line2i &line, const Color &color);
    void DrawLine(const math::Line2f &line, const Color &color);

    // Wu氏抗锯齿直线绘制
    void DrawAntialiasedLine(int x1, int y1, int x2, int y2,
                             const Color &color);
    void DrawAntialiasedLine(const pri::PointPrimitive &start,
                             const pri::PointPrimitive &end);
    void DrawAntialiasedLine(const math::Point2i &start, const math::Point2i &end, const Color &color);
    void DrawAntialiasedLine(const math::Point2f &start, const math::Point2f &end, const Color &color);
    void DrawAntialiasedLine(const math::Line2i &line, const Color &color);
    void DrawAntialiasedLine(const math::Line2f &line, const Color &color);

    // 图元管理
    void AddPrimitive(std::unique_ptr<pri::IPrimitive> primitive);
    void ClearPrimitives();
    void DrawAllPrimitives();

    // 获取关联的像素缓冲区
    PixelsBuffer &Buffer() { return _buffer; }
    const PixelsBuffer &Buffer() const { return _buffer; }

private:
    PixelsBuffer &_buffer;
    std::vector<std::unique_ptr<pri::IPrimitive>> _primitives;
};

#endif // GRAPHICS_RENDERER_H