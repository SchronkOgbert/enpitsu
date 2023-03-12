//
// Created by weekendUM on 2/2/2023.
//

#ifndef LIBTEST_GEOMETRYESSENTIALS_H
#define LIBTEST_GEOMETRYESSENTIALS_H

#include "defines.h"
#include "Exception.h"

namespace enpitsu
{
    class BadDimensionException : public Exception
    {
    public:
        BadDimensionException() : Exception("The dimension you asked for does not exist") {}
    };

    struct Vector2
    {
        double x;
        double y;

        Vector2() = default;

        Vector2(const double &x, const double &y) : x(x), y(y)
        {}

        [[nodiscard]] std::tuple<double, double> linearize() const
        {
            return {x, y};
        }

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

        explicit operator glm::vec2() const
        {
            return {x, y};
        }

        double operator[](const char& dimension) const
        {
            switch (dimension)
            {
                case 'x':
                    return x;
                case 'y':
                    return y;
                default:
                    throw BadDimensionException();
            }
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

        [[nodiscard]] std::tuple<double, double, double> linearize() const
        {
            return {x, y, z};
        }

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

        explicit operator glm::vec3() const
        {
            return {x, y, z};
        }

        Vector3 &operator+(const glm::vec3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3 &operator+(const Vector3 &other)
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

        double operator[](const char& dimension) const
        {
            switch (dimension)
            {
                case 'x':
                    return x;
                case 'y':
                    return y;
                case 'z':
                    return z;
                default:
                    throw BadDimensionException();
            }
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

        [[nodiscard]] std::tuple<double, double, double, double> linearize() const
        {
            return {x, y, z, a};
        }

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

        explicit operator glm::vec4() const
        {
            return {x, y, z, a};
        }

        double operator[](const char& dimension) const
        {
            switch (dimension)
            {
                case 'x':
                    return x;
                case 'y':
                    return y;
                case 'z':
                    return z;
                case 'a':
                    return a;
                default:
                    throw BadDimensionException();
            }
        }
    };

    float toGLCoord(const float &screenCoord, const float &maxDimension);

    float fromGLCoord(const float &GLCoord, const float &maxDimension);

    glm::vec3 toGLMVec3(const Vector3 &obj);

    template<class Vector>
    concept vectorType =
    requires(Vector t)
    {
        requires
        std::same_as<Vector, Vector2> ||
        std::same_as<Vector, Vector3> ||
        std::same_as<Vector, Vector4>;
    };

    template<vectorType T>
    std::vector<GLfloat> linearizePointsVector(const std::vector<T> &points)
    {
        size_t dimensions;
        if(typeid(T) == typeid(Vector2))
        {
            dimensions = 2;
        }
        else if(typeid(T) == typeid(Vector3))
        {
            dimensions = 3;
        }
        else
        {
            dimensions = 4;
        }
        std::vector<GLfloat> res(points.size() * dimensions);
        size_t counter = 0;
        for (auto &el: points)
        {
            res[counter++] = el['x'];
            res[counter++] = el['y'];
            switch (dimensions)
            {
                case 3:
                {
                    res[counter++] = el['z'];
                    break;
                }
                case 4:
                {
                    res[counter++] = el['z'];
                    res[counter++] = el['a'];
                    break;
                }
                default:
                    break;
            }
        }
        return res;
    }
}

#endif //LIBTEST_GEOMETRYESSENTIALS_H
