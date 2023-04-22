#ifndef ENPITSU_GEOMETRYESSENTIALS_H
#define ENPITSU_GEOMETRYESSENTIALS_H

#include "defines.h"
#include "Exception.h"

namespace enpitsu
{
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;

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
    std::vector<GLfloat>
    linearizePointsVector(const std::vector<T> &points)
    {
        size_t dimensions;
        if (typeid(T) == typeid(Vector2))
        {
            dimensions = 2;
        } else if (typeid(T) == typeid(Vector3))
        {
            dimensions = 3;
        } else
        {
            dimensions = 4;
        }
        std::vector<GLfloat> res(points.size() * dimensions);
        size_t counter = 0;
        for (auto &el: points)
        {
            auto values = glm::value_ptr(el);
            switch (dimensions)
            {
                case 2:
                {
                    res[counter++] = el[0];
                    res[counter++] = el[1];
                }
                break;
                case 3:
                {
                    res[counter++] = el[0];
                    res[counter++] = el[1];
                    res[counter++] = el[2];
                    break;
                }
                case 4:
                {
                    res[counter++] = el[0];
                    res[counter++] = el[1];
                    res[counter++] = el[2];
                    res[counter++] = el[3];
                    break;
                }
                default:
                    break;
            }
        }
        return res;
    }

    enpitsu::Vector2 mousePosToGLCoords(const enpitsu::Vector2 &mousePos, const enpitsu::Vector2 &screenSize,
                                        const enpitsu::Vector2 &cameraPosition = {0, 0}, const float &unitScale = 1);
} // namespace enpitsu

// TODO remove this cause it doesn't work on gcc
namespace std
{
    template<>
    struct std::formatter<enpitsu::Vector2> : std::formatter<std::string>
    {
        auto format(const enpitsu::Vector2 &v, format_context &context)
        {
            return formatter<string>::format(std::format("({}, {})", v.x, v.y), context);
        }
    };

    template<>
    struct std::formatter<enpitsu::Vector3> : std::formatter<std::string>
    {
        auto format(const enpitsu::Vector3 &v, format_context &context)
        {
            return formatter<string>::format(std::format("({}, {}, {})", v.x, v.y, v.z), context);
        }
    };

    template<>
    struct std::formatter<enpitsu::Vector4> : std::formatter<std::string>
    {
        auto format(const enpitsu::Vector4 &v, format_context &context)
        {
            return formatter<string>::format(std::format("({}, {}, {}, {})", v.x, v.y, v.z, v.a), context);
        }
    };
} // namespace std

#endif //ENPITSU_GEOMETRYESSENTIALS_H
