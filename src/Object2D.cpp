//
// Created by weekendUM on 1/27/2023.
//

#include "Object2D.h"
#include "Screen.h"
#include "Bell/Core.h"
#include "SolidColor.h"

using bell::core::print;

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, ShaderProgram *shader,
                                     const bool &isStatic,
                                     const std::vector<unsigned int> &drawOrder) : Object(screen)
{
    if(!shader)
    {
        throw BadShaderObject();
    }
    println("received ", points.size(), " points");
    this->vertices.reserve(points.size() * 2U);
    for (auto &point: points)
    {
        this->vertices.push_back(static_cast<float>(point.x / screen->getSize().first) * 2 - 1.0F);
        this->vertices.push_back(static_cast<float>(point.y / screen->getSize().second) * 2 - 1.0F);
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
    println(sizeof(&indices[0]) * indices.size());
    shaderProgram->Create(vertices, indices, 2, isStatic);
    if (!shaderProgram->getVao() || !shaderProgram->getVertexPosition() || !shaderProgram->getEbo())
    {
        throw BadGLObject();
    }
    shaderProgram->getVao()->LinkVBO(*shaderProgram->getVertexPosition());
}

void enpitsu::Object2D::init()
{
    Object::init();
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
