//
// Created by weekendUM on 1/27/2023.
//

#include "Object2D.h"
#include "Screen.h"

void enpitsu::Object2D::draw()
{
    shaderProgram->Create();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
}

enpitsu::Object2D::Object2D(Screen *screen, const std::vector<Vector2> &points, const bool &isStatic,
                            const std::vector<unsigned int> &drawOrder) : Object(screen)
{
    this->vertices = std::vector<GLfloat>(points.size() * 2U);
    if (drawOrder.empty())
    {
        this->indices = std::vector<GLuint>(this->vertices.size());
        for(unsigned int i = 0U; i < this->indices.size(); i++)
        {
            this->indices[i] = i;
        }
    }
    vao->Bind();
    vbo = std::make_unique<VBO>(&vertices[0U], static_cast<GLsizeiptr>(vertices.size()), isStatic);
    ebo = std::make_unique<EBO>(&indices[0U], static_cast<GLsizeiptr >(indices.size()), isStatic);
    shaderProgram = std::make_unique<ShaderProgram>("default.vert", "default.frag");
}

void enpitsu::Object2D::init()
{
    Object::init();
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
