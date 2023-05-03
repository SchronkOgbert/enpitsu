#ifndef ENPITSU_CUBE_H
#define ENPITSU_CUBE_H

#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/objects/Triangles3D.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"

namespace enpitsu
{
    class Cube : public Triangles3D
    {
    public:
        Cube() = delete;
        explicit Cube(Screen *screen, const Vector3 &origin = {0, 0, 0}, std::shared_ptr<ShaderProgram> &&shader =
                newShader<SolidColor>(Vector4{255, 255, 255, 255}, "default3D.vert"));
    };

} // enpitsu

#endif //ENPITSU_CUBE_H
