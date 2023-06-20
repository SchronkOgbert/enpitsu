#include "enpitsu/objects/Object2D.h"
#include "enpitsu/helpers/Exception.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "glm/gtx/transform.hpp"
#include <memory>

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, const Vector2 &origin,
                            std::shared_ptr<ShaderProgram> &&shader,
                            const bool &isStatic, const std::vector<unsigned int> &drawOrder) :
        Object(screen),
        isStatic(isStatic),
        origin(origin)
{
    if (!shader.get())
    {
        throw BadShaderObject();
    }
    this->vertices.reserve(points.size() * 2U);
    this->vertices = linearizePointsVector(points);
    PLOGD << "Origin: " << origin.x << ' ' << origin.y;
    if (drawOrder.empty())
    {
        this->indices = std::vector<GLuint>(this->vertices.size());
        for (unsigned int i = 0U; i < this->indices.size(); i++)
        {
            this->indices[i] = i;
        }
    } else
    {
        this->indices = drawOrder;
    }
    model = glm::translate(model, Vector3(origin, 0));
    shaderProgram = shader;
}

void enpitsu::Object2D::init()
{
    Object::init();
    if (!(shaderProgram->isInitialized()))
    {
        shaderProgram->Create(vertices, indices, 2, isStatic);
        if (!shaderProgram->getVao() || !shaderProgram->getVertexPosition() || !shaderProgram->getEbo())
        {
            throw BadGLObject();
        }
        shaderProgram->getVao()->LinkVBO(*shaderProgram->getVertexPosition());
        shaderProgram->getVao()->Unbind();
        shaderProgram->getVertexPosition()->Unbind();
        shaderProgram->getEbo()->Unbind();
        shaderProgram->updateMat4UniformF("camMatrix", screen->getCam2DMatrix());
    }
    shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
}

void enpitsu::Object2D::onDestroy()
{
    Object::onDestroy();
    shaderProgram->Delete();
}

bool enpitsu::Object2D::isScaleToScreen() const
{
    return scaleToScreen;
}

void enpitsu::Object2D::setScaleToScreen(const bool &scaleToScreen)
{
    this->scaleToScreen = scaleToScreen;
}

void enpitsu::Object2D::draw()
{
    shaderProgram->Bind();
    if(shouldUpdateCamera2D())
    {
        shaderProgram->updateMat4UniformF("camMatrix", screen->getCam2DMatrix());
    }
    if(!isStatic && updateModel)
    {
        updateModel = false;
    }
    shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
}

const enpitsu::Vector2 &enpitsu::Object2D::getOrigin() const
{
    return origin;
}

void enpitsu::Object2D::setOrigin(const enpitsu::Vector2 &origin)
{
    this->origin = origin;
}

void enpitsu::Object2D::setLocation(const enpitsu::Vector2 &newLocation)
{
    if (isStatic) throw Exception("Cannot move static object");
    forceSetLocation(newLocation);
}

void enpitsu::Object2D::forceSetLocation(const enpitsu::Vector2 &newLocation) noexcept
{
    model = glm::translate(model, Vector3(newLocation - origin, 0));
    origin = newLocation;
    updateModel = true;
}

void enpitsu::Object2D::tick(const float &delta)
{
    Object::tick(delta);
    this->draw();
    shaderProgram->Unbind();
}

void enpitsu::Object2D::setScale(const Vector2 &newScale)
{
    if(isStatic) throw Exception("Cannot scale static object");
    forceSetScale(newScale);
}

void enpitsu::Object2D::forceSetScale(const enpitsu::Vector2 &newScale)
{
    model = glm::scale(model, Vector3(newScale / size, 1));
    size = newScale;
    updateModel = true;
}

void enpitsu::Object2D::forceSetRotation(const float &rotation)
{
    model = glm::rotate(model, glm::radians(rotation), Vector3(0, 0, 1));
}
