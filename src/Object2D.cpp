//
// Created by weekendUM on 1/27/2023.
//

#include "objects/Object2D.h"
#include "objects/Screen.h"
#include "shading/SolidColor.h"
#include "helpers/GeometryEssentials.h"

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, const Vector2 &origin,
                            ShaderProgram *shader,
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
    for (auto &point: points)
    {
        this->vertices.push_back(toGLCoord(origin.x + point.x, screen->getSize().x));
        this->vertices.push_back(toGLCoord(origin.y + point.y,
                                           screen->getSize().y));
    }
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
    shaderProgram = std::unique_ptr<ShaderProgram>(shader);
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
    if (scaleToScreen)
    {

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
    for (auto i = 0; i < vertices.size(); i += 2)
    {
        vertices[i] = toGLCoord(
                fromGLCoord(vertices[i], screen->getSize().x) + newLocation.x,
                screen->getSize().x
        );
        vertices[i + 1] = toGLCoord(
                fromGLCoord(vertices[i + 1], screen->getSize().y) +
                newLocation.y, // this is because y starts form the bottom in glfw
                screen->getSize().y
        );
    }
    shaderProgram->Create(vertices, indices, 2, isStatic);
}

void enpitsu::Object2D::tick(const float &delta)
{
    Object::tick(delta);
    this->draw();
    shaderProgram->Unbind();
}

void enpitsu::Object2D::setSize(const enpitsu::Vector2 &newSize)
{
    
}
