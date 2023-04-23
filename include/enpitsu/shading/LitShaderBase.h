#ifndef ENPITSU_LITSHADERBASE_H
#define ENPITSU_LITSHADERBASE_H

#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    class LitShaderBase : public SolidColor
    {
    public:
        LitShaderBase(const Vector4 &color = {255, 255, 255, 255});
    };

} // enpitsu

#endif //ENPITSU_LITSHADERBASE_H
