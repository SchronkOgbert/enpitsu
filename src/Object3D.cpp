//
// Created by weekendUM on 2/18/2023.
//

#include "enpitsu/objects/Object3D.h"
#include "enpitsu/objects/Screen.h"

namespace enpitsu
{
    const std::shared_ptr<ShaderProgram> & Object3D::getShaderProgram() const
    {
        return shaderProgram;
    }

    Object3D::Object3D(Screen *screen, std::vector<Vector3> *points, const Vector3 &origin, const Vector3 &size,
                       ShaderProgram *shader, const bool &isStatic, std::vector<unsigned int> *drawOrder)
                       : Object(screen), isStatic(isStatic), origin(origin), indices(*drawOrder)
    {
        this->vertices = linearizePointsVector<Vector3>
                (*points, screen->getSize().x, screen->getSize().y);
//        this->vertices = {
//                -0.5f, 0, 0.5f,
//                -0.5f, 0, -0.5f,
//                0.5f, 0, -0.5f,
//                0.5f, 0, 0.5f,
//                0, 0.8f, 0
//        };
        PLOGD << "Vertices count: " << vertices.size();
        for(auto& vertex : vertices)
        {
            PLOGD << vertex;
        }
        PLOGD << "Draw order ";
        for(auto& index : indices)
        {
            PLOGD << index << ' ';
        }
        this->shaderProgram = std::shared_ptr<ShaderProgram> (shader);
        this->shaderProgram->Create(vertices, indices, 3, isStatic);
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