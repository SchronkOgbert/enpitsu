#include "enpitsu/objects/Object3D.h"
#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/objects/Camera3D.h"
#include "enpitsu/shading/LitShaderBase.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

namespace enpitsu
{
    const std::shared_ptr<ShaderProgram> &Object3D::getShaderProgram() const
    {
        return shaderProgram;
    }

    Object3D::Object3D(Screen *screen, std::vector<Vector3> *points, const Vector3 &origin, const Vector3 &size,
                       const std::shared_ptr<ShaderProgram> &shader, const bool &isStatic,
                       std::vector<unsigned int> *drawOrder)
            : Object(screen), isStatic(isStatic), origin(origin), indices(*drawOrder),
              worldOriginOffset(origin - Vector3{0, 0, 0})
    {
        this->vertices = linearizePointsVector<Vector3>(*points);
        this->shaderProgram = shader;
        model = glm::translate(glm::mat4(1), origin);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));
        model = glm::scale(model, Vector3(1, 1, 1));
    }

    void Object3D::tick(const float &delta)
    {
        Object::tick(delta);
        this->draw();
    }

    void Object3D::draw()
    {
        shaderProgram->Bind();
        if (shouldUpdateCamera3D())
        {
            shaderProgram->updateMat4UniformF("cam3DMatrix", screen->getCam3DMatrix());
        }
        if (updateModel)
        {
            updateModel = false;
        }
        shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
    }

    void Object3D::init()
    {
        Object::init();
        shaderProgram->setVertices(&vertices);
        shaderProgram->setIndices(&indices);
        if(!(shaderProgram->isInitialized()))
        {
            auto litShader = dynamic_cast<LitShaderBase *>(shaderProgram.get());
            if (litShader)
            {
                litShader->setScreen(screen);
            }
            shaderProgram->Create(vertices, indices, 3, isStatic);
            if (!shaderProgram->getVao() || !shaderProgram->getVertexPosition() || !shaderProgram->getEbo())
            {
                throw BadGLObject();
            }
            shaderProgram->getVao()->LinkVBO(*shaderProgram->getVertexPosition());
            shaderProgram->getVao()->Unbind();
            shaderProgram->getVertexPosition()->Unbind();
            shaderProgram->getEbo()->Unbind();
            shaderProgram->updateMat4UniformF("cam3DMatrix", screen->getCam3DMatrix());
        }
        shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
    }

    void Object3D::setLocation(const Vector3 &newLocation)
    {
        if (isStatic) throw Exception("Cannot move static object");
        forceSetLocation(newLocation);
    }

    const Vector3 &Object3D::getOrigin() const
    {
        return origin;
    }

    void Object3D::setOrigin(const Vector3 &origin)
    {
        Object3D::origin = origin;
    }

    void Object3D::forceSetLocation(const Vector3 &newLocation)
    {
        model = glm::translate(model, newLocation - origin - worldOriginOffset);
        origin = worldOriginOffset + newLocation;
        updateModel = true;
    }

    void Object3D::setRotation(const Vector3 &newRotation)
    {
        if (isStatic) throw Exception("Cannot rotate static object");
        forceSetRotation(newRotation);
    }

    void Object3D::forceSetRotation(const Vector3 &newRotation)
    {
        model = glm::rotate(model, glm::radians(newRotation.x - rotation.x), Vector3(1, 0, 0));
        model = glm::rotate(model, glm::radians(newRotation.y - rotation.y), Vector3(0, 1, 0));
        model = glm::rotate(model, glm::radians(newRotation.z - rotation.z), Vector3(0, 0, 1));
        this->rotation = newRotation;
        updateModel = true;
    }

    void Object3D::setScale(const Vector3 &newScale)
    {
        if(isStatic) throw Exception("Cannot set scale of static object");
        forceSetScale(newScale);
    }

    void Object3D::forceSetScale(const Vector3 &newScale)
    {
        model = glm::scale(model, newScale / scale);
        scale = newScale;
        updateModel = true;
    }
} // enpitsu