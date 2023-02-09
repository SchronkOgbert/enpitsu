//
// Created by weekendUM on 2/8/2023.
//

#include "SolidColor.h"
#include "iostream"

namespace enpitsu
{
    SolidColor::SolidColor(const Vector4 &rgbaColor) :
    ShaderProgram("shaders/default.vert", "shaders/default.frag"), color(rgbaColor)
    {

    }

    void SolidColor::Create()
    {
        ShaderProgram::Create();
    }
} // enpitsu