//
// Created by admin on 2025/12/24.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
#include <sstream>

namespace math
{

template <class T> class Vector3;
template <class T> class Vector4;
template <class T> class Vector2;

using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;
using Vector2f = Vector2<float>;

using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;
using Vector3f = Vector3<float>;

using Vector4i = Vector4<int>;
using Vector4d = Vector4<double>;
using Vector4f = Vector4<float>;

/**
 * @brief 二维向量类模板
 * @tparam T 向量分量的数据类型（如int, float, double等）
 */
template <class T> class Vector2
{
  public:
    /**
     * @brief 默认构造函数，初始化为零向量
     */
    Vector2() : _x(0), _y(0) {}

    /**
     * @brief 参数化构造函数
     * @param x x分量
     * @param y y分量
     */
    Vector2(T x, T y) : _x(x), _y(y) {}

    /**
     * @brief 拷贝构造函数
     * @param v 要拷贝的向量
     */
    Vector2(const Vector2& v) : _x(v._x), _y(v._y) {}

    /**
     * @brief 从Vector3构造，丢弃z分量
     * @param v 三维向量
     */
    Vector2(const Vector3<T>& v) : _x(v[0]), _y(v[1]) {}

    /**
     * @brief 从Vector4构造，丢弃z和w分量
     * @param v 四维向量
     */
    Vector2(const Vector4<T>& v) : _x(v[0]), _y(v[1]) {}

    /**
     * @brief 赋值运算符
     * @param v 要赋值的向量
     * @return 当前向量的引用
     */
    Vector2& operator=(const Vector2& v)
    {
        if (this == &v)
            return *this;

        _x = v._x;
        _y = v._y;
        return *this;
    }

    /**
     * @brief 从Vector3赋值，丢弃z分量
     * @param v 三维向量
     * @return 当前向量的引用
     */
    Vector2& operator=(const Vector3<T>& v)
    {
        _x = v[0];
        _y = v[1];
        return *this;
    }

    /**
     * @brief 从Vector4赋值，丢弃z和w分量
     * @param v 四维向量
     * @return 当前向量的引用
     */
    Vector2& operator=(const Vector4<T>& v)
    {
        _x = v[0];
        _y = v[1];
        return *this;
    }

    /**
     * @brief 下标运算符（常量版本）
     * @param index 索引（0=x, 1=y）
     * @return 对应分量的值
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
     * @return 对应分量的引用
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
     * @brief 向量加法
     * @param v 要相加的向量
     * @return 相加后的新向量
     */
    Vector2 operator+(const Vector2& v) const
    {
        return Vector2(_x + v._x, _y + v._y);
    }

    /**
     * @brief 向量加法赋值
     * @param v 要相加的向量
     * @return 当前向量的引用
     */
    Vector2& operator+=(const Vector2& v)
    {
        _x += v._x;
        _y += v._y;
        return *this;
    }

    /**
     * @brief 标量乘法
     * @param s 标量值
     * @return 相乘后的新向量
     */
    Vector2 operator*(const T s) const
    {
        return Vector2(_x * s, _y * s);
    }

    /**
     * @brief 标量乘法赋值
     * @param s 标量值
     * @return 当前向量的引用
     */
    Vector2& operator*=(const T s)
    {
        _x *= s;
        _y *= s;
        return *this;
    }

    /**
     * @brief 标量除法
     * @param s 标量值
     * @return 相除后的新向量，如果s接近0则返回原向量
     */
    Vector2 operator/(const T s) const
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        return Vector2(_x / s, _y / s);
    }

    /**
     * @brief 标量除法赋值
     * @param s 标量值
     * @return 当前向量的引用，如果s接近0则不做修改
     */
    Vector2& operator/=(const T s)
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= s;
        _y /= s;
        return *this;
    }

    /**
     * @brief 向量取反（负号运算符）
     * @return 取反后的新向量
     */
    Vector2 operator-()
    {
        return Vector2(-_x, -_y);
    }

    /**
     * @brief 向量减法
     * @param v 要相减的向量
     * @return 相减后的新向量
     */
    Vector2 operator-(const Vector2& v) const
    {
        return Vector2(_x - v._x, _y - v._y);
    }

    /**
     * @brief 向量减法赋值
     * @param v 要相减的向量
     * @return 当前向量的引用
     */
    Vector2& operator-=(const Vector2& v)
    {
        _x -= v._x;
        _y -= v._y;
        return *this;
    }

    /**
     * @brief 向量逐元素乘法
     * @param v 要相乘的向量
     * @return 逐元素相乘后的新向量
     */
    Vector2 operator*(const Vector2& v) const
    {
        return Vector2(_x * v._x, _y * v._y);
    }

    /**
     * @brief 向量逐元素乘法赋值
     * @param v 要相乘的向量
     * @return 当前向量的引用
     */
    Vector2& operator*=(const Vector2& v)
    {
        _x *= v._x;
        _y *= v._y;
        return *this;
    }

    /**
     * @brief 计算向量的点积（内积）
     * @param v 另一个向量
     * @return 点积结果
     */
    T Dot(const Vector2& v) const
    {
        return _x * v._x + _y * v._y;
    }

    /**
     * @brief 计算向量的叉积（外积）
     * @param v 另一个向量
     * @return 叉积结果标量
     */
    T Cross(const Vector2& v) const
    {
        return _x * v._y - _y * v._x;
    }

    /**
     * @brief 计算向量长度的平方
     * @return 向量长度的平方
     */
    T LengthSquared() const
    {
        return _x * _x + _y * _y;
    }

    /**
     * @brief 计算向量的长度（模）
     * @return 向量的长度
     */
    T Length() const
    {
        return std::sqrt(LengthSquared());
    }

    /**
     * @brief 返回归一化后的新向量（单位向量）
     * @return 归一化后的新向量，如果长度为0则返回零向量
     */
    Vector2 Normalized() const
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return Vector2(0, 0);
        }
        return Vector2(_x / len, _y / len);
    }

    /**
     * @brief 将当前向量归一化（转换为单位向量）
     * @return 当前向量的引用，如果长度为0则不做修改
     */
    Vector2& Normalize()
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= len;
        _y /= len;
        return *this;
    }

    /**
     * @brief 计算向量的绝对值（各分量取绝对值）
     * @return 各分量取绝对值后的新向量
     */
    Vector2 Abs() const
    {
        return Vector2(std::abs(_x), std::abs(_y));
    }

    T X() const
    {
        return _x;
    }
    T Y() const
    {
        return _y;
    }

    /**
     * @brief 输出向量信息
     */
    void Print()
    {
        std::cout << "x: " << _x << ", y: " << _y << std::endl;
    }

    /**
     * @brief 输出向量信息到字符串
     * @return 向量信息的字符串
     */
    std::string PrintToString()
    {
        std::stringstream ss;
        ss << "x: " << _x << ", y: " << _y;
        return ss.str();
    }

  private:
    T _x, _y;
};

/**
 * @brief 三维向量类模板
 * @tparam T 向量分量的数据类型（如int, float, double等）
 */
template <class T> class Vector3
{
  public:
    /**
     * @brief 默认构造函数，初始化为零向量
     */
    Vector3() : _x(0), _y(0), _z(0) {}

    /**
     * @brief 参数化构造函数
     * @param x x分量
     * @param y y分量
     * @param z z分量
     */
    Vector3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    /**
     * @brief 拷贝构造函数
     * @param v 要拷贝的向量
     */
    Vector3(const Vector3& v) : _x(v._x), _y(v._y), _z(v._z) {}

    /**
     * @brief 从Vector2构造，z分量设为0
     * @param v 二维向量
     */
    Vector3(const Vector2<T>& v) : _x(v[0]), _y(v[1]), _z(0) {}

    /**
     * @brief 从Vector4构造，丢弃w分量
     * @param v 四维向量
     */
    Vector3(const Vector4<T>& v) : _x(v[0]), _y(v[1]), _z(v[2]) {}

    /**
     * @brief 赋值运算符
     * @param v 要赋值的向量
     * @return 当前向量的引用
     */
    Vector3& operator=(const Vector3& v)
    {
        if (this == &v)
            return *this;

        _x = v._x;
        _y = v._y;
        _z = v._z;
        return *this;
    }

    /**
     * @brief 从Vector2赋值，z分量设为0
     * @param v 二维向量
     * @return 当前向量的引用
     */
    Vector3& operator=(const Vector2<T>& v)
    {
        _x = v[0];
        _y = v[1];
        _z = 0;
        return *this;
    }

    /**
     * @brief 从Vector4赋值，丢弃w分量
     * @param v 四维向量
     * @return 当前向量的引用
     */
    Vector3& operator=(const Vector4<T>& v)
    {
        _x = v[0];
        _y = v[1];
        _z = v[2];
        return *this;
    }

    /**
     * @brief 下标运算符（常量版本）
     * @param index 索引（0=x, 1=y, 2=z）
     * @return 对应分量的值
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
     * @return 对应分量的引用
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
     * @brief 向量加法
     * @param v 要相加的向量
     * @return 相加后的新向量
     */
    Vector3 operator+(const Vector3& v) const
    {
        return Vector3(_x + v._x, _y + v._y, _z + v._z);
    }

    /**
     * @brief 向量加法赋值
     * @param v 要相加的向量
     * @return 当前向量的引用
     */
    Vector3& operator+=(const Vector3& v)
    {
        _x += v._x;
        _y += v._y;
        _z += v._z;
        return *this;
    }

    /**
     * @brief 标量乘法
     * @param s 标量值
     * @return 相乘后的新向量
     */
    Vector3 operator*(const T s) const
    {
        return Vector3(_x * s, _y * s, _z * s);
    }

    /**
     * @brief 标量乘法赋值
     * @param s 标量值
     * @return 当前向量的引用
     */
    Vector3& operator*=(const T s)
    {
        _x *= s;
        _y *= s;
        _z *= s;
        return *this;
    }

    /**
     * @brief 标量除法
     * @param s 标量值
     * @return 相除后的新向量，如果s接近0则返回原向量
     */
    Vector3 operator/(const T s) const
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        return Vector3(_x / s, _y / s, _z / s);
    }

    /**
     * @brief 标量除法赋值
     * @param s 标量值
     * @return 当前向量的引用，如果s接近0则不做修改
     */
    Vector3& operator/=(const T s)
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= s;
        _y /= s;
        _z /= s;
        return *this;
    }

    /**
     * @brief 向量取反（负号运算符）
     * @return 取反后的新向量
     */
    Vector3 operator-()
    {
        return Vector3(-_x, -_y, -_z);
    }

    /**
     * @brief 向量减法
     * @param v 要相减的向量
     * @return 相减后的新向量
     */
    Vector3 operator-(const Vector3& v) const
    {
        return Vector3(_x - v._x, _y - v._y, _z - v._z);
    }

    /**
     * @brief 向量减法赋值
     * @param v 要相减的向量
     * @return 当前向量的引用
     */
    Vector3& operator-=(const Vector3& v)
    {
        _x -= v._x;
        _y -= v._y;
        _z -= v._z;
        return *this;
    }

    /**
     * @brief 向量逐元素乘法
     * @param v 要相乘的向量
     * @return 逐元素相乘后的新向量
     */
    Vector3 operator*(const Vector3& v) const
    {
        return Vector3(_x * v._x, _y * v._y, _z * v._z);
    }

    /**
     * @brief 向量逐元素乘法赋值
     * @param v 要相乘的向量
     * @return 当前向量的引用
     */
    Vector3& operator*=(const Vector3& v)
    {
        _x *= v._x;
        _y *= v._y;
        _z *= v._z;
        return *this;
    }

    /**
     * @brief 计算向量的点积（内积）
     * @param v 另一个向量
     * @return 点积结果
     */
    T Dot(const Vector3& v) const
    {
        return _x * v._x + _y * v._y + _z * v._z;
    }

    /**
     * @brief 计算向量的叉积（外积）
     * @param v 另一个向量
     * @return 叉积结果向量
     */
    Vector3 Cross(const Vector3& v) const
    {
        return Vector3(_y * v._z - _z * v._y, _z * v._x - _x * v._z, _x * v._y - _y * v._x);
    }

    /**
     * @brief 计算向量长度的平方
     * @return 向量长度的平方
     */
    T LengthSquared() const
    {
        return _x * _x + _y * _y + _z * _z;
    }

    /**
     * @brief 计算向量的长度（模）
     * @return 向量的长度
     */
    T Length() const
    {
        return std::sqrt(LengthSquared());
    }

    /**
     * @brief 返回归一化后的新向量（单位向量）
     * @return 归一化后的新向量，如果长度为0则返回零向量
     */
    Vector3 Normalized() const
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return Vector3(0, 0, 0);
        }
        return Vector3(_x / len, _y / len, _z / len);
    }

    /**
     * @brief 将当前向量归一化（转换为单位向量）
     * @return 当前向量的引用，如果长度为0则不做修改
     */
    Vector3& Normalize()
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= len;
        _y /= len;
        _z /= len;
        return *this;
    }

    /**
     * @brief 计算向量的绝对值（各分量取绝对值）
     * @return 各分量取绝对值后的新向量
     */
    Vector3 Abs() const
    {
        return Vector3(std::abs(_x), std::abs(_y), std::abs(_z));
    }

    T X() const
    {
        return _x;
    }
    T Y() const
    {
        return _y;
    }
    T Z() const
    {
        return _z;
    }

    /**
     * @brief 输出向量信息
     */
    void Print()
    {
        std::cout << "x: " << _x << ", y: " << _y << ", z: " << _z << std::endl;
    }

    /**
     * @brief 输出向量信息到字符串
     * @return 向量信息的字符串
     */
    std::string PrintToString()
    {
        std::stringstream ss;
        ss << "x: " << _x << ", y: " << _y << ", z: " << _z;
        return ss.str();
    }

  private:
    T _x, _y, _z;
};

/**
 * @brief 四维向量类模板
 * @tparam T 向量分量的数据类型（如int, float, double等）
 */
template <class T> class Vector4
{
  public:
    /**
     * @brief 默认构造函数，初始化为零向量
     */
    Vector4() : _x(0), _y(0), _z(0), _w(0) {}

    /**
     * @brief 参数化构造函数
     * @param x x分量
     * @param y y分量
     * @param z z分量
     * @param w w分量
     */
    Vector4(T x, T y, T z, T w) : _x(x), _y(y), _z(z), _w(w) {}

    /**
     * @brief 拷贝构造函数
     * @param v 要拷贝的向量
     */
    Vector4(const Vector4& v) : _x(v._x), _y(v._y), _z(v._z), _w(v._w) {}

    /**
     * @brief 从Vector2构造，z和w分量设为0
     * @param v 二维向量
     */
    Vector4(const Vector2<T>& v) : _x(v[0]), _y(v[1]), _z(0), _w(0) {}

    /**
     * @brief 从Vector3构造，w分量设为0
     * @param v 三维向量
     */
    Vector4(const Vector3<T>& v) : _x(v[0]), _y(v[1]), _z(v[2]), _w(0) {}

    /**
     * @brief 赋值运算符
     * @param v 要赋值的向量
     * @return 当前向量的引用
     */
    Vector4& operator=(const Vector4& v)
    {
        if (this == &v)
            return *this;

        _x = v._x;
        _y = v._y;
        _z = v._z;
        _w = v._w;
        return *this;
    }

    /**
     * @brief 从Vector2赋值，z和w分量设为0
     * @param v 二维向量
     * @return 当前向量的引用
     */
    Vector4& operator=(const Vector2<T>& v)
    {
        _x = v[0];
        _y = v[1];
        _z = 0;
        _w = 0;
        return *this;
    }

    /**
     * @brief 从Vector3赋值，w分量设为0
     * @param v 三维向量
     * @return 当前向量的引用
     */
    Vector4& operator=(const Vector3<T>& v)
    {
        _x = v[0];
        _y = v[1];
        _z = v[2];
        _w = 0;
        return *this;
    }

    /**
     * @brief 下标运算符（常量版本）
     * @param index 索引（0=x, 1=y, 2=z, 3=w）
     * @return 对应分量的值
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
        case 3:
            return _w;
        default:
            return _x;
        }
    }

    /**
     * @brief 下标运算符（可修改版本）
     * @param index 索引（0=x, 1=y, 2=z, 3=w）
     * @return 对应分量的引用
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
        case 3:
            return _w;
        default:
            return _x;
        }
    }

    /**
     * @brief 向量加法
     * @param v 要相加的向量
     * @return 相加后的新向量
     */
    Vector4 operator+(const Vector4& v) const
    {
        return Vector4(_x + v._x, _y + v._y, _z + v._z, _w + v._w);
    }

    /**
     * @brief 向量加法赋值
     * @param v 要相加的向量
     * @return 当前向量的引用
     */
    Vector4& operator+=(const Vector4& v)
    {
        _x += v._x;
        _y += v._y;
        _z += v._z;
        _w += v._w;
        return *this;
    }

    /**
     * @brief 标量乘法
     * @param s 标量值
     * @return 相乘后的新向量
     */
    Vector4 operator*(const T s) const
    {
        return Vector4(_x * s, _y * s, _z * s, _w * s);
    }

    /**
     * @brief 标量乘法赋值
     * @param s 标量值
     * @return 当前向量的引用
     */
    Vector4& operator*=(const T s)
    {
        _x *= s;
        _y *= s;
        _z *= s;
        _w *= s;
        return *this;
    }

    /**
     * @brief 标量除法
     * @param s 标量值
     * @return 相除后的新向量，如果s接近0则返回原向量
     */
    Vector4 operator/(const T s) const
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        return Vector4(_x / s, _y / s, _z / s, _w / s);
    }

    /**
     * @brief 标量除法赋值
     * @param s 标量值
     * @return 当前向量的引用，如果s接近0则不做修改
     */
    Vector4& operator/=(const T s)
    {
        if (std::abs(s) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= s;
        _y /= s;
        _z /= s;
        _w /= s;
        return *this;
    }

    /**
     * @brief 向量取反（负号运算符）
     * @return 取反后的新向量
     */
    Vector4 operator-()
    {
        return Vector4(-_x, -_y, -_z, -_w);
    }

    /**
     * @brief 向量减法
     * @param v 要相减的向量
     * @return 相减后的新向量
     */
    Vector4 operator-(const Vector4& v) const
    {
        return Vector4(_x - v._x, _y - v._y, _z - v._z, _w - v._w);
    }

    /**
     * @brief 向量减法赋值
     * @param v 要相减的向量
     * @return 当前向量的引用
     */
    Vector4& operator-=(const Vector4& v)
    {
        _x -= v._x;
        _y -= v._y;
        _z -= v._z;
        _w -= v._w;
        return *this;
    }

    /**
     * @brief 向量逐元素乘法
     * @param v 要相乘的向量
     * @return 逐元素相乘后的新向量
     */
    Vector4 operator*(const Vector4& v) const
    {
        return Vector4(_x * v._x, _y * v._y, _z * v._z, _w * v._w);
    }

    /**
     * @brief 向量逐元素乘法赋值
     * @param v 要相乘的向量
     * @return 当前向量的引用
     */
    Vector4& operator*=(const Vector4& v)
    {
        _x *= v._x;
        _y *= v._y;
        _z *= v._z;
        _w *= v._w;
        return *this;
    }

    /**
     * @brief 计算向量的点积（内积）
     * @param v 另一个向量
     * @return 点积结果
     */
    T Dot(const Vector4& v) const
    {
        return _x * v._x + _y * v._y + _z * v._z + _w * v._w;
    }

    /**
     * @brief 计算向量长度的平方
     * @return 向量长度的平方
     */
    T LengthSquared() const
    {
        return _x * _x + _y * _y + _z * _z + _w * _w;
    }

    /**
     * @brief 计算向量的长度（模）
     * @return 向量的长度
     */
    T Length() const
    {
        return std::sqrt(LengthSquared());
    }

    /**
     * @brief 返回归一化后的新向量（单位向量）
     * @return 归一化后的新向量，如果长度为0则返回零向量
     */
    Vector4 Normalized() const
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return Vector4(0, 0, 0, 0);
        }
        return Vector4(_x / len, _y / len, _z / len, _w / len);
    }

    /**
     * @brief 将当前向量归一化（转换为单位向量）
     * @return 当前向量的引用，如果长度为0则不做修改
     */
    Vector4& Normalize()
    {
        T len = Length();
        if (std::abs(len) < std::numeric_limits<T>::epsilon())
        {
            return *this;
        }
        _x /= len;
        _y /= len;
        _z /= len;
        _w /= len;
        return *this;
    }

    /**
     * @brief 计算向量的绝对值（各分量取绝对值）
     * @return 各分量取绝对值后的新向量
     */
    Vector4 Abs() const
    {
        return Vector4(std::abs(_x), std::abs(_y), std::abs(_z), std::abs(_w));
    }

    T X() const
    {
        return _x;
    }
    T Y() const
    {
        return _y;
    }
    T Z() const
    {
        return _z;
    }
    T W() const
    {
        return _w;
    }

    /**
     * @brief 输出向量信息
     */
    void Print()
    {
        std::cout << "x: " << _x << ", y: " << _y << ", z: " << _z << ", w: " << _w << std::endl;
    }

    /**
     * @brief 输出向量信息到字符串
     * @return 向量信息的字符串
     */
    std::string PrintToString()
    {
        std::stringstream ss;
        ss << "x: " << _x << ", y: " << _y << ", z: " << _z << ", w: " << _w;
        return ss.str();
    }

  private:
    T _x, _y, _z, _w;
};

// ==================== 全局运算符重载 ====================

/**
 * @brief 标量与二维向量相乘（标量在左）
 * @tparam T 向量分量的数据类型
 * @param s 标量值
 * @param v 向量
 * @return 相乘后的新向量
 */
template <class T> Vector2<T> operator*(const T s, const Vector2<T>& v)
{
    return v * s;
}

/**
 * @brief 标量与三维向量相乘（标量在左）
 * @tparam T 向量分量的数据类型
 * @param s 标量值
 * @param v 向量
 * @return 相乘后的新向量
 */
template <class T> Vector3<T> operator*(const T s, const Vector3<T>& v)
{
    return v * s;
}

/**
 * @brief 标量与四维向量相乘（标量在左）
 * @tparam T 向量分量的数据类型
 * @param s 标量值
 * @param v 向量
 * @return 相乘后的新向量
 */
template <class T> Vector4<T> operator*(const T s, const Vector4<T>& v)
{
    return v * s;
}

} // namespace math

#endif // VECTOR_H
