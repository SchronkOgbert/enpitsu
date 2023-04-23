#include "enpitsu/shading/LitShaderBase.h"
#include "enpitsu/helpers/GeometryEssentials.h"

namespace enpitsu
{
    LitShaderBase::LitShaderBase(const Vector4 &color) :
            SolidColor(color, "default3D.vert", "default3D.frag")
    {

    }
} // enpitsu