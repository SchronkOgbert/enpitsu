#include "enpitsu/helpers/GeometryEssentials.h"

float enpitsu::toGLCoord(const float &screenCoord, const float &maxDimension)
{
    return screenCoord / maxDimension * 2 - 1.0F;
}

float enpitsu::fromGLCoord(const float &GLCoord, const float &maxDimension)
{
    return (GLCoord + 1.0F) / 2.0F * maxDimension;
}

glm::vec3 enpitsu::toGLMVec3(const enpitsu::Vector3 &obj)
{
    return {obj.x, obj.y, obj.z};
}

/**
 * Converts the mouse coordinates to gl world coordinates, based on data from the camera
 * @param mousePos the position of the mouse (x pixels by y pixels)
 * @param screenSize the resolution of the screen
 * @param cameraPosition where the camera is(default is 0, it's on you to get this info from the camera)
 * @param unitScale how many gl units are displayed vertically(it's on you to get this info from the camera)
 * @return world gl coordinates expressed as Vector2
 */
enpitsu::Vector2 enpitsu::mousePosToGLCoords(const enpitsu::Vector2 &mousePos, const enpitsu::Vector2 &screenSize,
                                             const enpitsu::Vector2 &cameraPosition, const float &unitScale)
{
    float x = toGLCoord(mousePos.x, screenSize.x) * unitScale * screenSize.x / screenSize.y + cameraPosition.x;
    float y = toGLCoord(mousePos.y, screenSize.y) * unitScale + cameraPosition.x;
    return {x, y};
}
