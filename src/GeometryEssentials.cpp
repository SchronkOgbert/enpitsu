#include "enpitsu/helpers/GeometryEssentials.h"

using namespace enpitsu;

float enpitsu::toGLCoord(const float &screenCoord, const float &maxDimension)
{
    return screenCoord / maxDimension * 2 - 1.0F;
}

float enpitsu::fromGLCoord(const float &GLCoord, const float &maxDimension)
{
    return (GLCoord + 1.0F) / 2.0F * maxDimension;
}

/**
 * Converts the mouse coordinates to gl world coordinates, based on data from the camera
 * @param mousePos the position of the mouse (x pixels by y pixels)
 * @param screenSize the resolution of the screen
 * @param cameraPosition where the camera is(default is 0, it's on you to get this info from the camera)
 * @param unitScale how many gl units are displayed vertically(it's on you to get this info from the camera)
 * @return world gl coordinates expressed as Vector2
 */
Vector2 enpitsu::mousePosToGLCoords(const Vector2 &mousePos, const Vector2 &screenSize,
                                             const Vector2 &cameraPosition, const float &unitScale)
{
    float x = toGLCoord(mousePos.x, screenSize.x) * unitScale * screenSize.x / screenSize.y + cameraPosition.x;
    float y = toGLCoord(mousePos.y, screenSize.y) * unitScale + cameraPosition.x;
    return {x, y};
}

std::pair<std::vector<GLfloat>, std::vector<GLfloat>>
enpitsu::generateFlatNormals(const std::vector<GLfloat> &points, const std::vector<GLuint> &indices)
{
    std::vector<GLfloat> normals;
    std::vector<GLfloat> vertices;
    normals.reserve(indices.size());
    vertices.reserve(indices.size() * 3);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        auto v1 = glm::make_vec3(&points[3 * indices[i++]]);
        vertices.emplace_back(v1[0]);
        vertices.emplace_back(v1[1]);
        vertices.emplace_back(v1[2]);
        auto v2 = glm::make_vec3(&points[3 * indices[i++]]);
        vertices.emplace_back(v2[0]);
        vertices.emplace_back(v2[1]);
        vertices.emplace_back(v2[2]);
        auto v3 = glm::make_vec3(&points[3 * indices[i]]);
        vertices.emplace_back(v3[0]);
        vertices.emplace_back(v3[1]);
        vertices.emplace_back(v3[2]);
        PLOGD << format("triangle with vertices {}, {}, {}", v1, v2, v3);
        PLOGD << format("vectors multiplied: {} x {}", v1 - v3, v1 - v2);
        auto normal = generateFlatNormal(v1, v2, v3);
        PLOGD << format("normal for triangle: {}", normal);
        int8_t n = 3;
        while(n)
        {
            normals.emplace_back(normal[0]);
            normals.emplace_back(normal[1]);
            normals.emplace_back(normal[2]);
            n--;
        }
    }
    return {normals, vertices};
}

Vector3 enpitsu::generateFlatNormal(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3)
{
    return glm::cross(v3 - v2, v3 - v1);
}
