//
// Created by weekendUM on 1/27/2023.
//

#include "VAO.h"
#include "VBO.h"

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
            glVertexAttribPointer(static_cast<GLuint>(layout), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::TEXTURE2D:
            glVertexAttribPointer(static_cast<GLuint>(layout), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::VERTEX3D:
            glVertexAttribPointer(static_cast<GLuint>(layout), 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
        case VBO::objectLayout::RGBA:
            glVertexAttribPointer(static_cast<GLuint>(layout), 4, GL_FLOAT, GL_FALSE, 0, nullptr);
            break;
    }
    glEnableVertexAttribArray(static_cast<GLuint>(layout));
    vbo.Unbind();
}

void VAO::Bind()
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
