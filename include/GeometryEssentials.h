//
// Created by weekendUM on 2/2/2023.
//

#ifndef LIBTEST_GEOMETRYESSENTIALS_H
#define LIBTEST_GEOMETRYESSENTIALS_H

#include "defines.h"

namespace enpitsu
{
    struct Vector2
    {
        double x;
        double y;
        Vector2() = default;
        Vector2(const double &x, const double &y) : x(x), y(y)
        {}

        Vector2 &operator=(const glm::vec2 &rhs) noexcept
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }

        Vector2 &operator=(const Vector2 &rhs) = default;

        friend std::ostream &operator<<(std::ostream &os, const Vector2 &obj) noexcept
        {
            return os << "Vector2(" << obj.x << ", " << obj.y << ")";
        }

        bool operator==(const Vector2 &rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y;
        }

        bool operator!=(const Vector2 &rhs) const
        {
            return !(rhs == *this);
        }

        friend bool operator==(const Vector2 &lhs, const glm::vec2 &rhs) noexcept
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        explicit operator glm::vec2 () const
        {
            return {x, y};
        }
    };

    struct Vector3
    {
        double x;
        double y;
        double z;

        Vector3() = default;

        Vector3(double x, double y, double z) : x(x), y(y), z(z)
        {}

        Vector3 &operator=(const glm::vec3 &rhs) noexcept
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }

        Vector3 &operator=(const Vector3 &rhs) = default;

        friend std::ostream &operator<<(std::ostream &os, const Vector3 &obj) noexcept
        {
            return os << "Vector3(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
        }

        bool operator==(const Vector3 &rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y &&
                   z == rhs.z;
        }

        bool operator!=(const Vector3 &rhs) const
        {
            return !(rhs == *this);
        }

        explicit operator glm::vec3 () const
        {
            return {x, y, z};
        }

        Vector3& operator+(const glm::vec3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3& operator+(const Vector3& other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3& operator+=(const glm::vec3& other)
        {
            *this = *this + other;
            return *this;
        }
    };

    struct Vector4
    {
        double x;
        double y;
        double z;
        double a;

        Vector4() = default;

        Vector4(double x, double y, double z, double a) : x(x), y(y), z(z), a(a)
        {}

        Vector4 &operator=(const glm::vec3 &rhs) noexcept
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }

        Vector4 &operator=(const Vector4 &rhs) = default;

        friend std::ostream &operator<<(std::ostream &os, const Vector4 &obj) noexcept
        {
            return os << "Vector4(" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.a << ")";
        }

        bool operator==(const Vector4 &rhs) const
        {
            return x == rhs.x &&
                   y == rhs.y &&
                   z == rhs.z &&
                   a == rhs.a;
        }

        bool operator!=(const Vector4 &rhs) const
        {
            return !(rhs == *this);
        }

        explicit operator glm::vec4 () const
        {
            return {x, y, z, a};
        }
    };

    float toGLCoord(const float &screenCoord, const float &maxDimension);

    float fromGLCoord(const float& GLCoord, const float &maxDimension);

    glm::vec3 toGLMVec3(const Vector3 &obj);
}

#endif //LIBTEST_GEOMETRYESSENTIALS_H
