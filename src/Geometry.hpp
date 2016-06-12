#pragma once

#include <cmath>

template <typename T>
struct Vec2
{
    Vec2() : x(0), y(0)
    {
    }

    Vec2(T _x, T _y) : x(_x), y(_y)
    {
    }

    inline Vec2<T> operator+(const Vec2<T>& _vec) const
    {
        return Vec2<T>(x + _vec.x, y + _vec.y);
    }

    inline Vec2<T> operator-(const Vec2<T>& _vec) const
    {
        return Vec2<T>(x - _vec.x, y - _vec.y);
    }

    inline Vec2<T> operator*(const float _f) const
    {
        return Vec2<T>(x * _f, y * _f);
    }

    Vec2<T>& operator=(const Vec2<T>& _vec)
    {
        if (this != &_vec)
        {
            x = _vec.x;
            y = _vec.y;
        }

        return *this;
    }

    T x, y;
};

template <typename T>
struct Vec3
{
    Vec3() : x(0), y(0), z(0)
    {
    }

    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
    {
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    Vec3& normalize()
    {
        float len = length();
        if (len * len > 0)
        {
            x /= len;
            y /= len;
            z /= len;
        }

        return *this;
    }

    T dot(const Vec3& _vec) const
    {
        return x * _vec.x + y * _vec.y + z * _vec.z;
    }

    Vec3<T> cross(const Vec3& _vec) const
    {
        return Vec3<T>(y * _vec.z - z * _vec.y, z * _vec.x - x * _vec.z, x * _vec.y - y * _vec.x);
    }

    inline Vec3<T> operator+(const Vec3<T>& _vec) const
    {
        return Vec3<T>(x + _vec.x, y + _vec.y, z + _vec.z);
    }

    inline Vec3<T> operator-(const Vec3<T>& _vec) const
    {
        return Vec3<T>(x - _vec.x, y - _vec.y, z - _vec.z);
    }

    inline Vec3<T> operator*(const float _f) const
    {
        return Vec3<T>(x * _f, y * _f, z * _f);
    }

    Vec3<T>& operator=(const Vec3<T>& _vec)
    {
        if (this != &_vec)
        {
            x = _vec.x;
            y = _vec.y;
            z = _vec.z;
        }

        return *this;
    }

    T x, y, z;
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
