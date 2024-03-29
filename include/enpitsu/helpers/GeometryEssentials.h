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

    Vector3 generateFlatNormal(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3);

    std::pair<std::vector<GLfloat>, std::vector<GLfloat>>
    generateFlatNormals(const std::vector<GLfloat> &points, const std::vector<GLuint> &indices);
} // namespace enpitsu

template<>
struct fmt::formatter<enpitsu::Vector2>
{
    template<class ParseContext>
    constexpr auto parse(ParseContext &context)
    {
        return context.begin();
    }

    template<class FormatContext>
    auto format(const enpitsu::Vector2 &v, FormatContext &context)
    {
        return fmt::format_to(context.out(), "({}, {})", v.x, v.y);
    }
};

template<>
struct fmt::formatter<enpitsu::Vector3>
{
    template<class ParseContext>
    constexpr auto parse(ParseContext &context)
    {
        return context.begin();
    }

    template<class FormatContext>
    auto format(const enpitsu::Vector3 &v, FormatContext &context)
    {
        return fmt::format_to(context.out(), "({}, {}, {})", v.x, v.y, v.z);
    }
};

template<>
struct fmt::formatter<enpitsu::Vector4>
{
    template<class ParseContext>
    constexpr auto parse(ParseContext &context)
    {
        return context.begin();
    }

    template<class FormatContext>
    auto format(const enpitsu::Vector4 &v, FormatContext &context)
    {
        return fmt::format_to(context.out(), "({}, {}, {}, {})", v.x, v.y, v.z, v.w);
    }
};

#endif //ENPITSU_GEOMETRYESSENTIALS_H
