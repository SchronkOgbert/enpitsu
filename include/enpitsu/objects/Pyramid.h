#ifndef ENPITSU_CUBE_H
#define ENPITSU_CUBE_H

#include "Triangles3D.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/shading/ShaderProgram.h"

namespace enpitsu
{

    class Pyramid : public Triangles3D
    {
    public:
        using Triangles3D::Triangles3D;
        Pyramid(Screen* screen, Vector3 origin, std::shared_ptr<ShaderProgram> &&shader, const bool& isStatic = true);
    };

} // enpitsu

#endif //ENPITSU_CUBE_H
