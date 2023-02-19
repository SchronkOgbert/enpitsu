//
// Created by weekendUM on 2/2/2023.
//

#include "GeometryEssentials.h"

float enpitsu::toGLCoord(const float &screenCoord, const float &maxDimension)
{
    return screenCoord / maxDimension * 2 - 1.0F;
}

float enpitsu::fromGLCoord(const float &GLCoord, const float &maxDimension)
{
    return (GLCoord + 1.0F) / 2.0F * maxDimension;
}
