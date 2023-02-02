//
// Created by weekendUM on 1/27/2023.
//

#include "VAO.h"
#include "VBO.h"

GLuint VAO::getId() const
{
    return ID;
}

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO vbo, const GLuint &layout)
{
    vbo.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(layout);
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
