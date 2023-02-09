//
// Created by weekendUM on 1/27/2023.
//

#include "Object2D.h"
#include "Screen.h"
#include "Bell/Core.h"
#include "SolidColor.h"
using bell::core::print;

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, const bool &isStatic,
                            const std::vector<unsigned int> &drawOrder) : Object(screen)
{
    println("received ", points.size(), " points");
    this->vertices.reserve(points.size() * 2U);
    for(auto &point : points)
    {
        this->vertices.push_back(static_cast<float>(point.x / screen->getSize().first) * 2 - 1.0F);
        this->vertices.push_back(static_cast<float>(point.y / screen->getSize().second) * 2 - 1.0F);
    }
    if (drawOrder.empty())
    {
        this->indices = std::vector<GLuint>(this->vertices.size());
        for(unsigned int i = 0U; i < this->indices.size(); i++)
        {
            this->indices[i] = i;
        }
    }
    else
    {
        this->indices = drawOrder;
    }
    vao = std::make_unique<VAO>(2);
    println(vao->getId());
    vao->Bind();
    vertexPosition = std::make_unique<VBO>(&vertices[0U], sizeof(&vertices[0]) * vertices.size(), isStatic);
    println(sizeof(&vertices[0]) * vertices.size());
    color = std::make_unique<VBO>(&colorValues[0], sizeof(float) * 4, isStatic);
    ebo = std::make_unique<EBO>(&indices[0U], sizeof(&indices[0]) * indices.size(), isStatic);
    println(sizeof(&indices[0]) * indices.size());
    shaderProgram = std::unique_ptr<ShaderProgram>(new SolidColor(Vector4(0.8f, 0.3f, 0.02f, 1.0f)));
    shaderProgram->Create();
    if(!vao || !vertexPosition || !ebo) throw BadGLObject();
    vao->LinkVBO(*vertexPosition, 0U);
    vao->LinkVBO(*color, 1U);
}

void enpitsu::Object2D::init()
{
    Object::init();
    vao->Unbind();
    vertexPosition->Unbind();
    ebo->Unbind();
}

void enpitsu::Object2D::onDestroy()
{
    Object::onDestroy();
    vao->Delete();
    vertexPosition->Delete();
    ebo->Delete();
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
    if(scaleToScreen)
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
