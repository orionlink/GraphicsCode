//
// Created by admin on 2026/1/14.
//

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "point.h"
#include <vector>
#include <limits>
#include <algorithm>

namespace math
{

/**
 * @brief 二维边界框类模板
 * @tparam T 坐标数据类型（如int, float, double等）
 */
template <class T>
class BoundingBox2
{
public:
    /**
     * @brief 默认构造函数，初始化为无效边界框
     */
    BoundingBox2()
        : _min_x(std::numeric_limits<T>::max()),
          _min_y(std::numeric_limits<T>::max()),
          _max_x(std::numeric_limits<T>::lowest()),
          _max_y(std::numeric_limits<T>::lowest())
    {
    }

    /**
     * @brief 参数化构造函数
     * @param min_x 最小x坐标
     * @param min_y 最小y坐标
     * @param max_x 最大x坐标
     * @param max_y 最大y坐标
     */
    BoundingBox2(T min_x, T min_y, T max_x, T max_y)
        : _min_x(min_x), _min_y(min_y), _max_x(max_x), _max_y(max_y)
    {
    }

    /**
     * @brief 根据点集合计算边界框
     * @param points 点集合
     * @return 边界框
     */
    static BoundingBox2 FromPoints(
        const std::vector<Point2<T>> &points)
    {
        if (points.empty())
        {
            return BoundingBox2();
        }

        BoundingBox2 bbox;
        for (const auto &point : points)
        {
            bbox.AddPoint(point);
        }
        return bbox;
    }

    /**
     * @brief 添加一个点到当前边界框
     * @param point 点
     */
    void AddPoint(const Point2<T> &point)
    {
        _min_x = std::min(_min_x, point.X());
        _min_y = std::min(_min_y, point.Y());
        _max_x = std::max(_max_x, point.X());
        _max_y = std::max(_max_y, point.Y());
    }

    /**
     * @brief 添加另一个边界框到当前边界框
     * @param box 另一个边界框
     */
    void AddBox(const BoundingBox2 &box)
    {
        AddPoint(Point2<T>(box._min_x, box._min_y));
        AddPoint(Point2<T>(box._max_x, box._max_y));
    }

    /**
     * @brief 检查点是否在边界框内
     * @param point 点
     * @return 点是否在边界框内
     */
    bool Contains(const Point2<T> &point) const
    {
        return point.X() >= _min_x &&
               point.X() <= _max_x &&
               point.Y() >= _min_y &&
               point.Y() <= _max_y;
    }

    /**
     * @brief 检查两个边界框是否相交
     * @param other 另一个边界框
     * @return 两个边界框是否相交
     */
    bool Intersects(const BoundingBox2 &other) const
    {
        return _max_x > other._min_x &&
               _max_y > other._min_y &&
               _min_x < other._max_x &&
               _min_y < other._max_y;
    }

    /**
     * @brief 获取边界框的宽度
     * @return 边界框的宽度
     */
    T Width() const { return _max_x - _min_x; }

    /**
     * @brief 获取边界框的高度
     * @return 边界框的高度
     */
    T Height() const { return _max_y - _min_y; }

    /**
     * @brief 获取边界框的面积
     * @return 边界框的面积
     */
    T Area() const { return Width() * Height(); }

    /**
     * @brief 获取最小x坐标
     * @return 最小x坐标
     */
    T MinX() const { return _min_x; }

    /**
     * @brief 获取最小y坐标
     * @return 最小y坐标
     */
    T MinY() const { return _min_y; }

    /**
     * @brief 获取最大x坐标
     * @return 最大x坐标
     */
    T MaxX() const { return _max_x; }

    /**
     * @brief 获取最大y坐标
     * @return 最大y坐标
     */
    T MaxY() const { return _max_y; }

    /**
     * @brief 获取最小点（左下角）
     * @return 最小点
     */
    Point2<T> MinPoint() const { return Point2<T>(_min_x, _min_y); }

    /**
     * @brief 获取最大点（右上角）
     * @return 最大点
     */
    Point2<T> MaxPoint() const { return Point2<T>(_max_x, _max_y); }

    /**
     * @brief 获取中心点
     * @return 中心点
     */
    Point2<T> Center() const
    {
        return Point2<T>(
            (_min_x + _max_x) / T(2),
            (_min_y + _max_y) / T(2));
    }

    /**
     * @brief 判断边界框是否有效（已添加过点）
     * @return 如果有效返回true，否则返回false
     */
    bool IsValid() const
    {
        return _min_x <= _max_x && _min_y <= _max_y;
    }

    /**
     * @brief 判断两个边界框是否相等
     * @param other 另一个边界框
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const BoundingBox2 &other) const
    {
        return _min_x == other._min_x &&
               _min_y == other._min_y &&
               _max_x == other._max_x &&
               _max_y == other._max_y;
    }

    /**
     * @brief 判断两个边界框是否不相等
     * @param other 另一个边界框
     * @return 如果不相等返回true，否则返回false
     */
    bool operator!=(const BoundingBox2 &other) const
    {
        return !(*this == other);
    }

private:
    T _min_x, _min_y, _max_x, _max_y;
};

// 常用类型别名（保持向后兼容）
using BoundingBox = BoundingBox2<float>;
using BoundingBox2i = BoundingBox2<int>;
using BoundingBox2f = BoundingBox2<float>;
using BoundingBox2d = BoundingBox2<double>;

} // math

#endif //BOUNDING_BOX_H
