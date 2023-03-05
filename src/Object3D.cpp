//
// Created by weekendUM on 2/18/2023.
//

#include "Object3D.h"

namespace enpitsu
{
    const std::unique_ptr<ShaderProgram> &Object3D::getShaderProgram() const
    {
        return shaderProgram;
    }

    Object3D::Object3D(Screen *screen, const std::vector<Vector3> points, const Vector3 &origin, const Vector3 &size,
                       ShaderProgram *shader, const bool &isStatic, const std::vector<unsigned int> drawOrder)
                       : Object(screen), isStatic(isStatic), origin(origin)
    {
        this->shader = std::shared_ptr<ShaderProgram> (shader);
    }
} // enpitsu