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

    Object3D::Object3D(Screen *screen, std::vector<Vector3> *points, const Vector3 &origin, const Vector3 &size,
                       ShaderProgram *shader, const bool &isStatic, std::vector<unsigned int> *drawOrder)
                       : Object(screen), isStatic(isStatic), origin(origin)
    {
        this->vertices = linearizePointsVector<Vector3>(*points);
        this->indices = {0};
        PLOGD << vertices.size();
        this->shader = std::shared_ptr<ShaderProgram> (shader);
        this->shader->Create(vertices, indices, 3, isStatic);
    }

    void Object3D::tick(const float &delta)
    {
        Object::tick(delta);
        this->draw();
        shaderProgram->Unbind();
    }

    void Object3D::draw()
    {
        shaderProgram->Bind();
    }
} // enpitsu