#include "enpitsu/GL/EBO.h"

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

void EBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLuint>(0));
}

void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}

GLsizeiptr EBO::getSize() const
{
    return size;
}

void EBO::setSize(GLsizeiptr size)
{
    EBO::size = size;
}

void EBO::Update(GLuint *indices) const
{
    this->Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, indices);
}
