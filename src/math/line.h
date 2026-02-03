//
// Created by admin on 2026/1/14.
//

#ifndef LINE_H
#define LINE_H

#include "point.h"
#include "vector.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace math
{

/**
 * @brief 二维线段类模板
 * @tparam T 坐标数据类型（如int, float, double等）
 */
template <class T> class Line2
{
  public:
    /**
     * @brief 默认构造函数，初始化为从原点到原点的线段
     */
    Line2() : _start(), _end() {}

    /**
     * @brief 参数化构造函数（使用两个点）
     * @param start 起点
     * @param end 终点
     */
    Line2(const Point2<T>& start, const Point2<T>& end) : _start(start), _end(end) {}

    /**
     * @brief 参数化构造函数（使用坐标）
     * @param x1 起点x坐标
     * @param y1 起点y坐标
     * @param x2 终点x坐标
     * @param y2 终点y坐标
     */
    Line2(T x1, T y1, T x2, T y2) : _start(x1, y1), _end(x2, y2) {}

    /**
     * @brief 拷贝构造函数
     * @param line 要拷贝的线段
     */
    Line2(const Line2& line) : _start(line._start), _end(line._end) {}

    /**
     * @brief 赋值运算符
     * @param line 要赋值的线段
     * @return 当前线段的引用
     */
    Line2& operator=(const Line2& line)
    {
        if (this == &line)
            return *this;

        _start = line._start;
        _end = line._end;
        return *this;
    }

    /**
     * @brief 获取起点
     * @return 起点的引用
     */
    const Point2<T>& Start() const { return _start; }

    /**
     * @brief 获取终点
     * @return 终点的引用
     */
    const Point2<T>& End() const { return _end; }

    /**
     * @brief 获取起点（可修改）
     * @return 起点的引用
     */
    Point2<T>& Start() { return _start; }

    /**
     * @brief 获取终点（可修改）
     * @return 终点的引用
     */
    Point2<T>& End() { return _end; }

    /**
     * @brief 设置起点
     * @param start 起点
     */
    void SetStart(const Point2<T>& start) { _start = start; }

    /**
     * @brief 设置终点
     * @param end 终点
     */
    void SetEnd(const Point2<T>& end) { _end = end; }

    /**
     * @brief 设置起点坐标
     * @param x x坐标
     * @param y y坐标
     */
    void SetStart(T x, T y) { _start.Set(x, y); }

    /**
     * @brief 设置终点坐标
     * @param x x坐标
     * @param y y坐标
     */
    void SetEnd(T x, T y) { _end.Set(x, y); }

    /**
     * @brief 设置线段
     * @param start 起点
     * @param end 终点
     */
    void Set(const Point2<T>& start, const Point2<T>& end)
    {
        _start = start;
        _end = end;
    }

    /**
     * @brief 设置线段坐标
     * @param x1 起点x坐标
     * @param y1 起点y坐标
     * @param x2 终点x坐标
     * @param y2 终点y坐标
     */
    void Set(T x1, T y1, T x2, T y2)
    {
        _start.Set(x1, y1);
        _end.Set(x2, y2);
    }

    /**
     * @brief 获取方向向量（从起点指向终点）
     * @return 方向向量
     */
    Vector2<T> Direction() const { return _end - _start; }

    /**
     * @brief 获取归一化的方向向量
     * @return 归一化的方向向量
     */
    Vector2<T> NormalizedDirection() const
    {
        Vector2<T> dir = Direction();
        return dir.Normalized();
    }

    /**
     * @brief 计算线段长度
     * @return 线段长度
     */
    T Length() const { return _start.DistanceTo(_end); }

    /**
     * @brief 计算线段长度的平方（避免开方运算）
     * @return 线段长度的平方
     */
    T LengthSquared() const { return _start.DistanceSquaredTo(_end); }

    /**
     * @brief 获取中点
     * @return 线段中点
     */
    Point2<T> Midpoint() const { return Point2<T>((_start.X() + _end.X()) / T(2), (_start.Y() + _end.Y()) / T(2)); }

    /**
     * @brief 反转线段（交换起点和终点）
     */
    void Reverse() { std::swap(_start, _end); }

    /**
     * @brief 获取反转后的线段
     * @return 反转后的新线段
     */
    Line2 Reversed() const { return Line2(_end, _start); }

    /**
     * @brief 判断两条线段是否相等
     * @param line 另一条线段
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const Line2& line) const { return _start == line._start && _end == line._end; }

    /**
     * @brief 判断两条线段是否不相等
     * @param line 另一条线段
     * @return 如果不相等返回true，否则返回false
     */
    bool operator!=(const Line2& line) const { return !(*this == line); }

    /**
     * @brief 输出流运算符
     * @param os 输出流
     * @param line 线段
     * @return 输出流引用
     */
    friend std::ostream& operator<<(std::ostream& os, const Line2& line)
    {
        os << "Line2(" << line._start << " -> " << line._end << ")";
        return os;
    }

  private:
    Point2<T> _start;
    Point2<T> _end;
};

/**
 * @brief 三维线段类模板
 * @tparam T 坐标数据类型（如int, float, double等）
 */
template <class T> class Line3
{
  public:
    /**
     * @brief 默认构造函数，初始化为从原点到原点的线段
     */
    Line3() : _start(), _end() {}

    /**
     * @brief 参数化构造函数（使用两个点）
     * @param start 起点
     * @param end 终点
     */
    Line3(const Point3<T>& start, const Point3<T>& end) : _start(start), _end(end) {}

    /**
     * @brief 参数化构造函数（使用坐标）
     * @param x1 起点x坐标
     * @param y1 起点y坐标
     * @param z1 起点z坐标
     * @param x2 终点x坐标
     * @param y2 终点y坐标
     * @param z2 终点z坐标
     */
    Line3(T x1, T y1, T z1, T x2, T y2, T z2) : _start(x1, y1, z1), _end(x2, y2, z2) {}

    /**
     * @brief 拷贝构造函数
     * @param line 要拷贝的线段
     */
    Line3(const Line3& line) : _start(line._start), _end(line._end) {}

    /**
     * @brief 赋值运算符
     * @param line 要赋值的线段
     * @return 当前线段的引用
     */
    Line3& operator=(const Line3& line)
    {
        if (this == &line)
            return *this;

        _start = line._start;
        _end = line._end;
        return *this;
    }

    /**
     * @brief 获取起点
     * @return 起点的引用
     */
    const Point3<T>& Start() const { return _start; }

    /**
     * @brief 获取终点
     * @return 终点的引用
     */
    const Point3<T>& End() const { return _end; }

    /**
     * @brief 获取起点（可修改）
     * @return 起点的引用
     */
    Point3<T>& Start() { return _start; }

    /**
     * @brief 获取终点（可修改）
     * @return 终点的引用
     */
    Point3<T>& End() { return _end; }

    /**
     * @brief 设置起点
     * @param start 起点
     */
    void SetStart(const Point3<T>& start) { _start = start; }

    /**
     * @brief 设置终点
     * @param end 终点
     */
    void SetEnd(const Point3<T>& end) { _end = end; }

    /**
     * @brief 设置起点坐标
     * @param x x坐标
     * @param y y坐标
     * @param z z坐标
     */
    void SetStart(T x, T y, T z) { _start.Set(x, y, z); }

    /**
     * @brief 设置终点坐标
     * @param x x坐标
     * @param y y坐标
     * @param z z坐标
     */
    void SetEnd(T x, T y, T z) { _end.Set(x, y, z); }

    /**
     * @brief 设置线段
     * @param start 起点
     * @param end 终点
     */
    void Set(const Point3<T>& start, const Point3<T>& end)
    {
        _start = start;
        _end = end;
    }

    /**
     * @brief 设置线段坐标
     * @param x1 起点x坐标
     * @param y1 起点y坐标
     * @param z1 起点z坐标
     * @param x2 终点x坐标
     * @param y2 终点y坐标
     * @param z2 终点z坐标
     */
    void Set(T x1, T y1, T z1, T x2, T y2, T z2)
    {
        _start.Set(x1, y1, z1);
        _end.Set(x2, y2, z2);
    }

    /**
     * @brief 获取方向向量（从起点指向终点）
     * @return 方向向量
     */
    Vector3<T> Direction() const { return _end - _start; }

    /**
     * @brief 获取归一化的方向向量
     * @return 归一化的方向向量
     */
    Vector3<T> NormalizedDirection() const
    {
        Vector3<T> dir = Direction();
        return dir.Normalized();
    }

    /**
     * @brief 计算线段长度
     * @return 线段长度
     */
    T Length() const { return _start.DistanceTo(_end); }

    /**
     * @brief 计算线段长度的平方（避免开方运算）
     * @return 线段长度的平方
     */
    T LengthSquared() const { return _start.DistanceSquaredTo(_end); }

    /**
     * @brief 获取中点
     * @return 线段中点
     */
    Point3<T> Midpoint() const
    {
        return Point3<T>((_start.X() + _end.X()) / T(2), (_start.Y() + _end.Y()) / T(2),
                         (_start.Z() + _end.Z()) / T(2));
    }

    /**
     * @brief 反转线段（交换起点和终点）
     */
    void Reverse() { std::swap(_start, _end); }

    /**
     * @brief 获取反转后的线段
     * @return 反转后的新线段
     */
    Line3 Reversed() const { return Line3(_end, _start); }

    /**
     * @brief 判断两条线段是否相等
     * @param line 另一条线段
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const Line3& line) const { return _start == line._start && _end == line._end; }

    /**
     * @brief 判断两条线段是否不相等
     * @param line 另一条线段
     * @return 如果不相等返回true，否则返回false
     */
    bool operator!=(const Line3& line) const { return !(*this == line); }

    /**
     * @brief 输出流运算符
     * @param os 输出流
     * @param line 线段
     * @return 输出流引用
     */
    friend std::ostream& operator<<(std::ostream& os, const Line3& line)
    {
        os << "Line3(" << line._start << " -> " << line._end << ")";
        return os;
    }

  private:
    Point3<T> _start;
    Point3<T> _end;
};

// 常用类型别名
using Line2i = Line2<int>;
using Line2f = Line2<float>;
using Line2d = Line2<double>;

using Line3i = Line3<int>;
using Line3f = Line3<float>;
using Line3d = Line3<double>;

} // namespace math

#endif // LINE_H
