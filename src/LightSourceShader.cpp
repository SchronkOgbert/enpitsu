#include "enpitsu/shading/LightSourceShader.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{
    LightSourceShader::LightSourceShader(const Vector3 &lightColor) :
            ShaderProgram("light.vert", "light.frag"),
            lightColor(lightColor)
    {
        PLOGD << format("Making light source with color {}", lightColor);
    }
} // enpitsu