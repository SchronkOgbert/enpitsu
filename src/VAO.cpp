//
// Created by weekendUM on 1/27/2023.
//

#include "enpitsu/GL/VAO.h"
#include "enpitsu/GL/VBO.h"

using namespace enpitsu;

GLuint VAO::getId() const
{
    return ID;
}

VAO::VAO(const GLint &vertexSize) : vertexSize(vertexSize)
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO vbo)
{
    vbo.Bind();
    auto layout = vbo.getLayout();
    switch (vbo.getLayout())
    {
        case VBO::objectLayout::VERTEX2D:
        case VBO::objectLayout::TEXTURE2D: // these are both vec2, so we only need 1 branch for both
            glVertexAttribPointer(static_cast<GLuint>(layout), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::VERTEX3D:
        case VBO::objectLayout::NORMAL: // these are both vec3, so we only need 1 branch for both
            glVertexAttribPointer(static_cast<GLuint>(layout), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::RGBA:
            glVertexAttribPointer(static_cast<GLuint>(layout), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
    }
    glEnableVertexAttribArray(static_cast<GLuint>(layout));
    vbo.Unbind();
}

void VAO::Bind() const
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0U);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
