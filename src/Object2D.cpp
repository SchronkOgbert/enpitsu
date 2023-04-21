#include "enpitsu/objects/Object2D.h"
#include "enpitsu/helpers/defines.h"
#include "enpitsu/objects/Screen.h"
#include "enpitsu/shading/ShaderProgram.h"
#include "enpitsu/shading/SolidColor.h"
#include "enpitsu/helpers/GeometryEssentials.h"
#include "glm/gtx/transform.hpp"

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, const Vector2 &origin,
                            std::shared_ptr<ShaderProgram> &&shader,
                            const bool &isStatic, const std::vector<unsigned int> &drawOrder) :
        Object(screen),
        isStatic(isStatic),
        origin(origin)
{
    if (!shader)
    {
        throw BadShaderObject();
    }
    this->vertices.reserve(points.size() * 2U);
    this->vertices = linearizePointsVector(points);
//    vertices = linearizePointsVector(points, screen->getSize().x, screen->getSize().y);
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
    model = glm::translate(model, Vector3(origin, 1));
    shaderProgram = std::move(shader);
}

void enpitsu::Object2D::init()
{
    Object::init();
//    forceSetLocation(origin); // this also compiles the shader
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
    shaderProgram->updateMat4UniformF("modelMatrix", glm::value_ptr(model));
}

void enpitsu::Object2D::onDestroy()
{
    Object::onDestroy();
    shaderProgram->getVao()->Delete();
    shaderProgram->getVertexPosition()->Delete();
    shaderProgram->getEbo()->Delete();
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
    Vector2 distance = newLocation - origin;
    origin = newLocation;
    for (auto i = 0; i < vertices.size(); i += 2)
    {
        vertices[i] = toGLCoord(
                fromGLCoord(vertices[i], screen->getSize().x) + distance.x,
                screen->getSize().x
        );
        vertices[i + 1] = toGLCoord(
                fromGLCoord(vertices[i + 1], screen->getSize().y) +
                distance.y, // this is because y starts form the bottom in glfw
                screen->getSize().y
        );
    }
    shaderProgram->getVertexPosition()->Update(&vertices[0]);
}

void enpitsu::Object2D::tick(const float &delta)
{
    Object::tick(delta);
    this->draw();
    shaderProgram->Unbind();
}

void enpitsu::Object2D::setSize(const enpitsu::Vector2 &newSize)
{

    size = newSize;
    shaderProgram->getVertexPosition()->UpdateScale({newSize.x, newSize.y, 1}, shaderProgram.get());
}
