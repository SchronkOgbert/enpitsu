#ifndef ENPITSU_LIGHTSOURCESHADER_H
#define ENPITSU_LIGHTSOURCESHADER_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    class LightSourceShader : public ShaderProgram
    {
        Vector3 lightColor{255, 255, 255};

    public:
        LightSourceShader(const Vector3 &lightColor);
    };

} // enpitsu

#endif //ENPITSU_LIGHTSOURCESHADER_H
