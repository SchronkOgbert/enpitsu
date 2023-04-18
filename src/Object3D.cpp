//
// Created by weekendUM on 2/18/2023.
//

#include "enpitsu/objects/Object3D.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Camera3D.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace enpitsu
{
    GLfloat *Object3D::camMatrix = nullptr;

    const std::shared_ptr<ShaderProgram> &Object3D::getShaderProgram() const
    {
        return shaderProgram;
    }

    Object3D::Object3D(Screen *screen, std::vector<Vector3> *points, const Vector3 &origin, const Vector3 &size,
                       std::shared_ptr<ShaderProgram> &&shader, const bool &isStatic,
                       std::vector<unsigned int> *drawOrder)
            : Object(screen), isStatic(isStatic), origin(origin), indices(*drawOrder)
    {
        this->vertices = linearizePointsVector<Vector3>
                (*points, screen->getSize().x, screen->getSize().y);
        PLOGD << "Vertices:";
        this->vertices = {
                -0.5f, 0, 0.5f,
                -0.5f, 0, -0.5f,
                0.5f, 0, -0.5f,
                0.5f, 0, 0.5f,
                0, 0.8f, 0
        };
        for (size_t i = 0; i < vertices.size(); i += 3)
        {
            PLOGD << std::format("vertex: ({}, {}, {})", vertices[i], vertices[i + 1], vertices[i + 2]);
        }
        PLOGD << "Draw order ";
        for (auto &index: indices)
        {
            PLOGD << index << ' ';
        }
        this->shaderProgram = std::shared_ptr<ShaderProgram>(shader);
        PLOGD << std::format("origin: {}", origin);
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
        if(shouldUpdateCamera())
        {
            shaderProgram->updateMat4UniformF("camMatrix", screen->getCamMatrix());
        }
    }

    void Object3D::init()
    {
        Object::init();
        shaderProgram->Create(vertices, indices, 3, isStatic);
        if (!shaderProgram->getVao() || !shaderProgram->getVertexPosition() || !shaderProgram->getEbo())
        {
            throw BadGLObject();
        }
        shaderProgram->getVao()->LinkVBO(*shaderProgram->getVertexPosition());
        shaderProgram->getVao()->Unbind();
        shaderProgram->getVertexPosition()->Unbind();
        shaderProgram->getEbo()->Unbind();
        shaderProgram->updateMat4UniformF("camMatrix", screen->getCamMatrix());
        shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
        shaderProgram->updateVec3Uniform("worldLocation", glm::value_ptr(origin));
    }
} // enpitsu