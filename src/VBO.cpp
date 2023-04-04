//
// Created by weekendUM on 1/27/2023.
//

#include "enpitsu/GL/VBO.h"

GLuint VBO::getId() const
{
    return ID;
}

VBO::VBO(GLfloat *vertices, const GLsizeiptr &size, const VBO::objectLayout &layout, const bool &isStatic) :
        layout(layout), size(size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices,
                 isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW); // NOLINT(clion-misra-cpp2008-5-0-4)
}

void VBO::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<GLuint>(0));
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

void VBO::Update(GLfloat *newVertices)
{
    this->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, newVertices);
    this->Unbind();
}
