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
