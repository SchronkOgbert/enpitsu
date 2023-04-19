#include "enpitsu/objects/Object3D.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Camera3D.h"

namespace enpitsu
{
    GLfloat *Object3D::camMatrix = nullptr;

    const std::shared_ptr<ShaderProgram> &Object3D::getShaderProgram() const
    {
        return shaderProgram;
    }

    Object3D::Object3D(Screen *screen, std::vector<Vector3> *points, const Vector3 &origin, const Vector3 &size,
                       const std::shared_ptr<ShaderProgram> &shader, const bool &isStatic,
                       std::vector<unsigned int> *drawOrder)
            : Object(screen), isStatic(isStatic), origin(origin), indices(*drawOrder)
    {
        this->vertices = linearizePointsVector<Vector3>
                (*points, screen->getSize().x, screen->getSize().y);
        this->shaderProgram = shader;
        model = glm::translate(glm::mat4(1), origin);
        model = glm::rotate(model,glm::radians(0.0f),glm::vec3(1,0,0));
        model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0,1,0));
        model = glm::rotate(model,glm::radians(0.0f),glm::vec3(0,0,1));
        model = glm::scale(model,Vector3(1,1,1));
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
        shaderProgram->updateVec3Uniform("cameraPosition", glm::value_ptr(screen->getCamera3D()->getPosition()));
    }
} // enpitsu