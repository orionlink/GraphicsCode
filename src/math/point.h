//
// Created by admin on 2026/1/14.
//

#ifndef POINT_H
#define POINT_H

#include "vector.h"
#include <algorithm>
#include <iostream>

namespace math
{

/**
 * @brief 二维点类模板
 * @tparam T 坐标数据类型（如int, float, double等）
 */
template <class T> class Point2
{
  public:
    /**
     * @brief 默认构造函数，初始化为原点
     */
    Point2() : _x(0), _y(0) {}

    /**
     * @brief 参数化构造函数
     * @param x x坐标
     * @param y y坐标
     */
    Point2(T x, T y) : _x(x), _y(y) {}

    /**
     * @brief 从Vector2构造
     * @param v 二维向量
     */
    Point2(const Vector2<T>& v) : _x(v[0]), _y(v[1]) {}

    /**
     * @brief 拷贝构造函数
     * @param p 要拷贝的点
     */
    Point2(const Point2& p) : _x(p._x), _y(p._y) {}

    /**
     * @brief 赋值运算符
     * @param p 要赋值的点
     * @return 当前点的引用
     */
    Point2& operator=(const Point2& p)
    {
        if (this == &p)
            return *this;

        _x = p._x;
        _y = p._y;
        return *this;
    }

    /**
     * @brief 从Vector2赋值
     * @param v 二维向量
     * @return 当前点的引用
     */
    Point2& operator=(const Vector2<T>& v)
    {
        _x = v[0];
        _y = v[1];
        return *this;
    }

    /**
     * @brief 转换为Vector2
     * @return 对应的二维向量
     */
    Vector2<T> ToVector() const
    {
        return Vector2<T>(_x, _y);
    }

    /**
     * @brief 获取x坐标
     * @return x坐标值
     */
    T X() const
    {
        return _x;
    }

    /**
     * @brief 获取y坐标
     * @return y坐标值
     */
    T Y() const
    {
        return _y;
    }

    /**
     * @brief 设置x坐标
     * @param x x坐标值
     */
    void SetX(T x)
    {
        _x = x;
    }

    /**
     * @brief 设置y坐标
     * @param y y坐标值
     */
    void SetY(T y)
    {
        _y = y;
    }

    /**
     * @brief 设置坐标
     * @param x x坐标值
     * @param y y坐标值
     */
    void Set(T x, T y)
    {
        _x = x;
        _y = y;
    }

    /**
     * @brief 下标运算符（常量版本）
     * @param index 索引（0=x, 1=y）
     * @return 对应坐标的值
     */
    T operator[](const int index) const
    {
        switch (index)
        {
        case 0:
            return _x;
        case 1:
            return _y;
        default:
            return _x;
        }
    }

    /**
     * @brief 下标运算符（可修改版本）
     * @param index 索引（0=x, 1=y）
     * @return 对应坐标的引用
     */
    T& operator[](const int index)
    {
        switch (index)
        {
        case 0:
            return _x;
        case 1:
            return _y;
        default:
            return _x;
        }
    }

    /**
     * @brief 点加法（平移）
     * @param v 平移向量
     * @return 平移后的新点
     */
    Point2 operator+(const Vector2<T>& v) const
    {
        return Point2(_x + v[0], _y + v[1]);
    }

    /**
     * @brief 点加法赋值（平移）
     * @param v 平移向量
     * @return 当前点的引用
     */
    Point2& operator+=(const Vector2<T>& v)
    {
        _x += v[0];
        _y += v[1];
        return *this;
    }

    /**
     * @brief 点减法（平移）
     * @param v 平移向量
     * @return 平移后的新点
     */
    Point2 operator-(const Vector2<T>& v) const
    {
        return Point2(_x - v[0], _y - v[1]);
    }

    /**
     * @brief 点减法赋值（平移）
     * @param v 平移向量
     * @return 当前点的引用
     */
    Point2& operator-=(const Vector2<T>& v)
    {
        _x -= v[0];
        _y -= v[1];
        return *this;
    }

    /**
     * @brief 两点相减得到向量
     * @param p 另一个点
     * @return 从当前点到p的向量
     */
    Vector2<T> operator-(const Point2& p) const
    {
        return Vector2<T>(_x - p._x, _y - p._y);
    }

    /**
     * @brief 判断两点是否相等
     * @param p 另一个点
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const Point2& p) const
    {
        return _x == p._x && _y == p._y;
    }

    /**
     * @brief 判断两点是否不相等
     * @param p 另一个点
     * @return 如果不相等返回true，否则返回false
     */
    bool operator!=(const Point2& p) const
    {
        return !(*this == p);
    }

    /**
     * @brief 交换x和y坐标
     */
    void SwapXY()
    {
        std::swap(_x, _y);
    }

    /**
     * @brief 计算到另一个点的距离
     * @param p 另一个点
     * @return 两点之间的距离
     */
    T DistanceTo(const Point2& p) const
    {
        Vector2<T> diff = *this - p;
        return diff.Length();
    }

    /**
     * @brief 计算到另一个点的距离的平方（避免开方运算）
     * @param p 另一个点
     * @return 两点之间距离的平方
     */
    T DistanceSquaredTo(const Point2& p) const
    {
        Vector2<T> diff = *this - p;
        return diff.LengthSquared();
    }

    /**
     * @brief 输出流运算符
     * @param os 输出流
     * @param p 点
     * @return 输出流引用
     */
    friend std::ostream& operator<<(std::ostream& os, const Point2& p)
    {
        os << "Point2(" << p._x << ", " << p._y << ")";
        return os;
    }

  private:
    T _x;
    T _y;
};

/**
 * @brief 三维点类模板
 * @tparam T 坐标数据类型（如int, float, double等）
 */
template <class T> class Point3
{
  public:
    /**
     * @brief 默认构造函数，初始化为原点
     */
    Point3() : _x(0), _y(0), _z(0) {}

    /**
     * @brief 参数化构造函数
     * @param x x坐标
     * @param y y坐标
     * @param z z坐标
     */
    Point3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    /**
     * @brief 从Vector3构造
     * @param v 三维向量
     */
    Point3(const Vector3<T>& v) : _x(v[0]), _y(v[1]), _z(v[2]) {}

    /**
     * @brief 从Point2构造，z坐标设为0
     * @param p 二维点
     */
    Point3(const Point2<T>& p) : _x(p[0]), _y(p[1]), _z(0) {}

    /**
     * @brief 拷贝构造函数
     * @param p 要拷贝的点
     */
    Point3(const Point3& p) : _x(p._x), _y(p._y), _z(p._z) {}

    /**
     * @brief 赋值运算符
     * @param p 要赋值的点
     * @return 当前点的引用
     */
    Point3& operator=(const Point3& p)
    {
        if (this == &p)
            return *this;

        _x = p._x;
        _y = p._y;
        _z = p._z;
        return *this;
    }

    /**
     * @brief 从Vector3赋值
     * @param v 三维向量
     * @return 当前点的引用
     */
    Point3& operator=(const Vector3<T>& v)
    {
        _x = v[0];
        _y = v[1];
        _z = v[2];
        return *this;
    }

    /**
     * @brief 从Point2赋值，z坐标设为0
     * @param p 二维点
     * @return 当前点的引用
     */
    Point3& operator=(const Point2<T>& p)
    {
        _x = p[0];
        _y = p[1];
        _z = 0;
        return *this;
    }

    /**
     * @brief 转换为Vector3
     * @return 对应的三维向量
     */
    Vector3<T> ToVector() const
    {
        return Vector3<T>(_x, _y, _z);
    }

    /**
     * @brief 转换为Point2（丢弃z坐标）
     * @return 对应的二维点
     */
    Point2<T> ToPoint2() const
    {
        return Point2<T>(_x, _y);
    }

    /**
     * @brief 获取x坐标
     * @return x坐标值
     */
    T X() const
    {
        return _x;
    }

    /**
     * @brief 获取y坐标
     * @return y坐标值
     */
    T Y() const
    {
        return _y;
    }

    /**
     * @brief 获取z坐标
     * @return z坐标值
     */
    T Z() const
    {
        return _z;
    }

    /**
     * @brief 设置x坐标
     * @param x x坐标值
     */
    void SetX(T x)
    {
        _x = x;
    }

    /**
     * @brief 设置y坐标
     * @param y y坐标值
     */
    void SetY(T y)
    {
        _y = y;
    }

    /**
     * @brief 设置z坐标
     * @param z z坐标值
     */
    void SetZ(T z)
    {
        _z = z;
    }

    /**
     * @brief 设置坐标
     * @param x x坐标值
     * @param y y坐标值
     * @param z z坐标值
     */
    void Set(T x, T y, T z)
    {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * @brief 下标运算符（常量版本）
     * @param index 索引（0=x, 1=y, 2=z）
     * @return 对应坐标的值
     */
    T operator[](const int index) const
    {
        switch (index)
        {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            return _x;
        }
    }

    /**
     * @brief 下标运算符（可修改版本）
     * @param index 索引（0=x, 1=y, 2=z）
     * @return 对应坐标的引用
     */
    T& operator[](const int index)
    {
        switch (index)
        {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            return _x;
        }
    }

    /**
     * @brief 点加法（平移）
     * @param v 平移向量
     * @return 平移后的新点
     */
    Point3 operator+(const Vector3<T>& v) const
    {
        return Point3(_x + v[0], _y + v[1], _z + v[2]);
    }

    /**
     * @brief 点加法赋值（平移）
     * @param v 平移向量
     * @return 当前点的引用
     */
    Point3& operator+=(const Vector3<T>& v)
    {
        _x += v[0];
        _y += v[1];
        _z += v[2];
        return *this;
    }

    /**
     * @brief 点减法（平移）
     * @param v 平移向量
     * @return 平移后的新点
     */
    Point3 operator-(const Vector3<T>& v) const
    {
        return Point3(_x - v[0], _y - v[1], _z - v[2]);
    }

    /**
     * @brief 点减法赋值（平移）
     * @param v 平移向量
     * @return 当前点的引用
     */
    Point3& operator-=(const Vector3<T>& v)
    {
        _x -= v[0];
        _y -= v[1];
        _z -= v[2];
        return *this;
    }

    /**
     * @brief 两点相减得到向量
     * @param p 另一个点
     * @return 从当前点到p的向量
     */
    Vector3<T> operator-(const Point3& p) const
    {
        return Vector3<T>(_x - p._x, _y - p._y, _z - p._z);
    }

    /**
     * @brief 判断两点是否相等
     * @param p 另一个点
     * @return 如果相等返回true，否则返回false
     */
    bool operator==(const Point3& p) const
    {
        return _x == p._x && _y == p._y && _z == p._z;
    }

    /**
     * @brief 判断两点是否不相等
     * @param p 另一个点
     * @return 如果不相等返回true，否则返回false
     */
    bool operator!=(const Point3& p) const
    {
        return !(*this == p);
    }

    /**
     * @brief 计算到另一个点的距离
     * @param p 另一个点
     * @return 两点之间的距离
     */
    T DistanceTo(const Point3& p) const
    {
        Vector3<T> diff = *this - p;
        return diff.Length();
    }

    /**
     * @brief 计算到另一个点的距离的平方（避免开方运算）
     * @param p 另一个点
     * @return 两点之间距离的平方
     */
    T DistanceSquaredTo(const Point3& p) const
    {
        Vector3<T> diff = *this - p;
        return diff.LengthSquared();
    }

    /**
     * @brief 输出流运算符
     * @param os 输出流
     * @param p 点
     * @return 输出流引用
     */
    friend std::ostream& operator<<(std::ostream& os, const Point3& p)
    {
        os << "Point3(" << p._x << ", " << p._y << ", " << p._z << ")";
        return os;
    }

  private:
    T _x;
    T _y;
    T _z;
};

// 常用类型别名
using Point2i = Point2<int>;
using Point2f = Point2<float>;
using Point2d = Point2<double>;

using Point3i = Point3<int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;

} // namespace math

#endif // POINT_H
