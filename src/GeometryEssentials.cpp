//
// Created by weekendUM on 2/2/2023.
//

#include "GeometryEssentials.h"

float *enpitsu::Vector4::toArray(const enpitsu::Vector4 &obj)
{
    auto *res = new float [4];
    res[0] = obj.x;
    res[1] = obj.y;
    res[2] = obj.z;
    res[3] = obj.a;
    return res;
}
