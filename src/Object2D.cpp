//
// Created by weekendUM on 1/27/2023.
//

#include "Object2D.h"
#include "Screen.h"
#include "Bell/Core.h"
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
    vbo = std::make_unique<VBO>(&vertices[0U], sizeof(&vertices[0]) * vertices.size(), isStatic);
    println(sizeof(&vertices[0]) * vertices.size());
    ebo = std::make_unique<EBO>(&indices[0U], sizeof(&indices[0]) * indices.size(), isStatic);
    println(sizeof(&indices[0]) * indices.size());
    shaderProgram = std::make_unique<ShaderProgram>("shaders/default.vert", "shaders/default.frag");
    for(auto &point : this->vertices)
    {
        print(point, ' ');
    }
    println('\n');
    for(auto &index : this->indices)
    {
        print(index, ' ');
    }
    println('\n');
    shaderProgram->Create();
}

void enpitsu::Object2D::init()
{
    Object::init();
    if(!vao || !vbo || !ebo) throw BadGLObject();
    vao->LinkVBO(*vbo, 0U);
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

void enpitsu::Object2D::onDestroy()
{
    Object::onDestroy();
    vao->Delete();
    vbo->Delete();
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
