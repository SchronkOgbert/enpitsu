//
// Created by weekendUM on 1/27/2023.
//

#include "EBO.h"

GLuint EBO::getId() const
{
    return ID;
}

EBO::EBO(GLuint *indices, const GLsizeiptr &size, const bool &isStatic)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(0));
}

void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
